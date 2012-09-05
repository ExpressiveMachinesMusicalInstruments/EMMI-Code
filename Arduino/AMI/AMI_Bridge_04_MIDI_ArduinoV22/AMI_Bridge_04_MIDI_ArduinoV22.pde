//STK Make motor go CW if softpot is above 511, CCW if below
#include <Compatibility_v2.5.h>
#include <MIDI.h>
#include "TimerOne.h"
//Much of this code is from Alex
int AllNotesOff = 123;

const int NUM_STATES = 8;
const int NUM_MOTOR_PINS = 4;

const unsigned int STATES[] = { 
  0x0001, 0x0011, 0x0010, 0x0110, 0x0100, 0x1100, 0x1000, 0x1001};
const int MOTOR_PINS[] = { 
  10, 11, 12, 13 }; // or whatever

const int SOFT_POT_PIN = A0; // 
const int EPSILON = 5; // "close enough"

int MOVE_TO_VALUE = 600; //Just to test
int WAIT = 1000; //microseconds


int SENSOR_VAL = 0;        // value read from the pot

void setup() {
  digitalWrite(SOFT_POT_PIN, HIGH); //Enables pull up resistor

  for (int i = 0; i < 4; i++) {
    pinMode(MOTOR_PINS[i], OUTPUT);
    digitalWrite(MOTOR_PINS[i], LOW); 
  }

  //**** Timer1 Initialize **************************
  Timer1.initialize(100000);         // initialize timer1, and set ??? second period
  Timer1.attachInterrupt(movingBridgeInterrupt);  // attaches callback() as a timer overflow interrupt
  Timer1.setPeriod(2440); //Timer ticks set to ???
  //**** End Timer1 Initialize **************************

  MIDI.begin(); 
}

void movingBridgeInterrupt() {

  drive_to(MOVE_TO_VALUE);

}

void loop() {
  if (MIDI.read()) {    // Is there a MIDI message incoming ?
      if (MIDI.getChannel() == 1) {    //filter so we only get messages coming on MIDI channel 1
    
        switch(MIDI.getType()) {		// Get the type of the message we caught
         
          //Control Change Messages
          case ControlChange: {
             int tCtlNum = MIDI.getData1(); //Get Controller Number
             int tCtlVal = MIDI.getData2(); //Get Value
             
             if( tCtlNum == AllNotesOff && tCtlVal == 0 ) { //Controller 123 sends AllOff
                   
//               digitalWrite(pick1, LOW);
//               digitalWrite(pick2, LOW);
//               digitalWrite(damper, LOW);  
                   
             } 
          }
          
          break;
          
          case PitchBend: {
            int tPitchBendVal1 = MIDI.getData1();
            int tPitchBendVal2 = MIDI.getData2(); //Get Value
            
            int tPitchBendValue = ((tPitchBendVal2 << 7) + tPitchBendVal1); //get 14 bits of Pitch Bend data
            
            if (tPitchBendValue < 1024) {
              MOVE_TO_VALUE = tPitchBendValue; 
            }

             //Code to parse pitch bend data and send to interrupt goes here
          }  
           
           break;
           
           //NoteOn messages 
           case NoteOn: {
             int tNoteNum = MIDI.getData1(); //Get Note Number
             int tNoteVel = MIDI.getData2(); //Get Velocity
             
             //Picker stuff will go here eventually   

           }
         break;
             
         default:  
         break;
        }
      }
  }
}


void drive_to(int target) {
  int motor_state = 0, dir = 0;
  while ((dir = direction_to(target)) != 0) {
    motor_state = cycle_motor(motor_state, dir);
    delayMicroseconds(WAIT);
  }
}

int direction_to(int target) {
  int d = target - analogRead(SOFT_POT_PIN);
  if (analogRead(SOFT_POT_PIN) > 1000)
    return 0;
  if (abs(d) < EPSILON) {
    //   Serial.println("STOP");
    return 0;
  } 
  else if (d > 0) {
    //    Serial.println("Clockwise"); 
    return 1;
  }
  else {
    //    Serial.println("CounterClockwise");
    return -1; 
  }
}

// parameters: state -- current state (0 - NUM_STATES-1)
//             dir -- 1: clockwise, -1: counter-clockwise
// return value: next state value
int cycle_motor(int state, int dir) {
  int next_state = (state + dir + NUM_STATES) % NUM_STATES;
  //  Serial.println(next_state);
  set_motor(STATES[next_state]);
  return next_state;
}

void set_motor(int values) {
  for (int i = 0; i < NUM_MOTOR_PINS; i++) {
    digitalWrite(MOTOR_PINS[i], (values >> (i*4)) & 1 ? HIGH : LOW);
  }
}








