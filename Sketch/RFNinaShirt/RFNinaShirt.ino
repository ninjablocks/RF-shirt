// Wireless Nina's eyes in a T_Shirt by @justy
// OK, there's nothing shirt-specific in the code- you just need 2 RGB LEDs
// 433 MHz RF receiver plus RGB LEDs

// Full PWM support

// Simple wireless protocol
// Each colour component is sent separately.   You send an arm code, then the colour value.
// For example, to make purple you would:
// 1. Send CODE_ArmR
// 2. Send CODE_Base + 255 (40255)
// 3. Send CODE_ArmB
// 4. Send CODE_Base + 255 (40255)

// You can add these codes as custom commands on your Dashsboard.  

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

// Set this to true to check your LEDs are wired up properly
#define TESTMODE false

#define ENABLE_SERIAL true

#define CODE_ArmR 35000 // Hex 88B8
#define CODE_ArmG 35001 // Hex 88B9
#define CODE_ArmB 35002 // Hex 88BA

#define CODE_Base 40000 // Hex 9C40
// Highest value code will be 40255

// Pins

// Receiver
#define PIN_Data 0 // Actually pin 2!

// LEDs  (Check!)
#define PIN_Eye1_R 3
#define PIN_Eye1_G 5
#define PIN_Eye1_B 6

#define PIN_Eye2_R 9
#define PIN_Eye2_G 10
#define PIN_Eye2_B 11

int arm_state;

#define STATE_Idle 0
#define STATE_ArmR 1
#define STATE_ArmG 2
#define STATE_ArmB 3

void setup() {
  
  #if ENABLE_SERIAL
  Serial.begin(9600);
  #endif

  pinMode(PIN_Data, INPUT);
  mySwitch.enableReceive(PIN_Data);  // Receiver on inerrupt 0 => that is pin #2

  pinMode(PIN_Eye1_R, OUTPUT);
  pinMode(PIN_Eye1_G, OUTPUT);
  pinMode(PIN_Eye1_B, OUTPUT);

  pinMode(PIN_Eye2_R, OUTPUT);
  pinMode(PIN_Eye2_G, OUTPUT);
  pinMode(PIN_Eye2_B, OUTPUT);
  
  setEyesR(0);
  setEyesG(0);
  setEyesB(0);
  

  // Use pin 13 as status
  pinMode(13,OUTPUT);
  digitalWrite(13, HIGH);
  delay(100);
  
  showBootDisplay();
  
  arm_state = STATE_Idle;
  
  #if ENABLE_SERIAL
  Serial.println("Booting..");
  #endif


}

void loop() {
  
     #if TESTMODE
       showBootDisplay();
     #endif
 

  if (mySwitch.available()) {

    long value = mySwitch.getReceivedValue();
    
    #if ENABLE_SERIAL
    Serial.print("Code: ");
    Serial.println(value, DEC);
    #endif

    if (value == 0) {
      Serial.print("Unknown encoding");
    } 
    else {

       int v = 0;
      switch(arm_state) {

      case STATE_Idle:
        // Accept arm codes
     

        switch(value) {
        case CODE_ArmR:
        arm_state = STATE_ArmR;
          break;
        case CODE_ArmG:
        arm_state = STATE_ArmG;
          break;
        case CODE_ArmB:
        arm_state = STATE_ArmB;
          break;

        }

        break;

      case STATE_ArmR:
        // Set the red to value-CODE_Base
        // But only if not receiving Arm_R!!
        if (value != CODE_ArmR) {
        v = constrain(value-CODE_Base,0,255);
        setEyesR(v);
        arm_state = STATE_Idle;
        }
        break;

      case STATE_ArmG:
        // Set the grn to value-CODE_Base
         // But only if not receiving Arm_G!!
        if (value != CODE_ArmG) {
        v = constrain(value-CODE_Base,0,255);
        setEyesG(v);
        arm_state = STATE_Idle;
        }
        break;

      case STATE_ArmB:
        // Set the blu to value-CODE_Base
         // But only if not receiving Arm_B!!
        if (value != CODE_ArmB) {
        v = constrain(value-CODE_Base,0,255);
        setEyesB(v);
        arm_state = STATE_Idle;
        }
        break;



      }


    }

    mySwitch.resetAvailable();
    
     #if ENABLE_SERIAL
      Serial.print("State: ");
      Serial.println(arm_state, DEC);
     #endif
     
    // Wait a bit
    delay(100);
    


  }

}

void showBootDisplay() {
  
  digitalWrite(13, HIGH);
  
  for (int d = 1000; d>100; d/=1.5) {

  // It wouldn't be a @justy thang without this:
  setEyesR(255);
  delay(d);
  setEyesR(0);
  setEyesG(255);
  delay(d);
  setEyesG(0);
  setEyesB(255);
  delay(d);
  setEyesB(0);
  delay(d);
  
  setEyesR(0);
  setEyesG(0);
  setEyesB(0);
  
  digitalWrite(13, LOW);
  
  }
  /*
  for (int i=255; i>0; i--) {
    setEyesR(i);
    setEyesG(i);
    setEyesB(i);
    delay(10);
  }
  
  setEyesR(0);
  setEyesG(0);
  setEyesB(0);
  */
  
 }

void setEyesR(int l) {
  analogWrite(PIN_Eye1_R, 255-l);
  analogWrite(PIN_Eye2_R, 255-l);
}

void setEyesG(int l) {
  analogWrite(PIN_Eye1_G, 255-l);
  analogWrite(PIN_Eye2_G, 255-l);
}

void setEyesB(int l) {
  analogWrite(PIN_Eye1_B, 255-l);
  analogWrite(PIN_Eye2_B, 255-l);
}


