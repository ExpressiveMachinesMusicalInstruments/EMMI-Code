/*
v. 009
Using Arduino 1.0
STK 7/10/12
Solenoid Control:
Code to take MIDI data in, implement velocity control
Using 13 solenoids
3 dampers
Changed Arduino pin 9 to pin 13, pin 13 to pin 14
*/
//#include <Compatibility_v2.5.h>
#ifndef cbi //This allows us to enable pin 1 for use
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#include <MIDI.h>
#include "TimerOne.h"

int AllNotesOff = 123;
int numOfVelSolenoids = 10; //Number ofsolenoids we're using w/velocity control
int numOfDamperSolenoids = 3; //Number of dampers (on/off)

int damperSolenoid[3] = {2,5,13};

int briefcaseSolenoid[10] = 
  {1,3,4,6,7,8,10,11,12,14}; //Assign solenoid pins
  
int solenoidVel[10] = 
  {0,0,0,0,0,0,0,0,0,0}; //Integers to store solenoid velocities

int solenoidVelCounter[10] = 
  {0,0,0,0,0,0,0,0,0,0}; //Counter for delayed off times
  
boolean solenoidState[10] = 
  {0,0,0,0,0,0,0,0,0,0}; //is the solenoid on or off?

void setup() {
  //  Serial.begin(9600); 	
  for (int i =0;i < numOfVelSolenoids; i++) {
    pinMode(briefcaseSolenoid[i], OUTPUT);
    digitalWrite(briefcaseSolenoid[i], LOW);
  }
  for (int i =0;i < numOfDamperSolenoids; i++) {
    pinMode(damperSolenoid[i], OUTPUT);
    digitalWrite(damperSolenoid[i], LOW);
  }
  Timer1.initialize(100);  // value in microseconds
  Timer1.attachInterrupt(noteOffInterrupt);  // attaches callback() as a timer overflow interrupt

  MIDI.begin(3); //set MIDI in to Channel 3 
  cbi(UCSR0B, TXEN0);  	//Disables pin 1 so we can use it as an output
}

void noteOffInterrupt() //The Interrupt
{
    if (solenoidState[0]) {   //If the solenoid is on
       solenoid_interrupt(0);  //Run solenoid_interrupt
    }
    else if (solenoidState[1]) {
       solenoid_interrupt(1);
    }
    else if (solenoidState[2]) {
       solenoid_interrupt(2);
    }
    else if (solenoidState[3]) {
       solenoid_interrupt(3);
    }
    else if (solenoidState[4]) {
       solenoid_interrupt(4);
    }
    else if (solenoidState[5]) {
       solenoid_interrupt(5);
    }
    else if (solenoidState[6]) {
       solenoid_interrupt(6);
    }
    else if (solenoidState[7]) {
       solenoid_interrupt(7);
    }
    else if (solenoidState[8]) {
       solenoid_interrupt(8);
    }
    else if (solenoidState[9]) {
       solenoid_interrupt(9);
    }
    else if (solenoidState[10]) {
       solenoid_interrupt(10);
    }
  
}

void loop() {
  if (MIDI.read()) {    // Is there a MIDI message incoming ?
    
        switch(MIDI.getType()) {		// Get the type of the message we caught
         
          //Control Change Messages
          case ControlChange: {
             int tCtlNum = MIDI.getData1(); //Get Controller Number
             int tCtlVal = MIDI.getData2(); //Get Value
             
             if( tCtlNum == AllNotesOff && tCtlVal == 0 ) { //Controller 123 sends AllOff
             
                for (int i =0;i < numOfVelSolenoids; i++) {
                    digitalWrite(briefcaseSolenoid[i], LOW);
                }
                for (int i =0;i < numOfDamperSolenoids; i++) {
                    digitalWrite(damperSolenoid[i], LOW);
                }     
                   
             } 
          }
           
           break;
           
           //NoteOn messages //DAMPERS: 2,5,9
           case NoteOn: {
             int tNoteNum = (MIDI.getData1()); //Get Note Number, scale for our arrays
             int tNoteVel = MIDI.getData2(); //Get Velocity
             //Lowest note number = 1 
             
             if (tNoteNum == 1) 
               set_solenoid(0, tNoteVel);  //Array number
             
             if (tNoteNum == 2) { //DAMPER
                 if( tNoteVel > 0) {
                     digitalWrite(damperSolenoid[0], HIGH); //turn it on 
                   }
                   else {
                     digitalWrite(damperSolenoid[0], LOW); //turn it off
                   }
             }
             
             if (tNoteNum == 3) 
               set_solenoid(1, tNoteVel); 
             
             if (tNoteNum == 4) 
               set_solenoid(2, tNoteVel); 
               
             if (tNoteNum == 5) { //DAMPER
                 if( tNoteVel > 0) {
                     digitalWrite(damperSolenoid[1], HIGH); //turn it on 
                   }
                   else {
                     digitalWrite(damperSolenoid[1], LOW); //turn it off
                   }
             }
               
             if (tNoteNum == 6) 
               set_solenoid(3, tNoteVel); 
               
             if (tNoteNum == 7) 
               set_solenoid(4, tNoteVel); 
               
             if (tNoteNum == 8) 
               set_solenoid(5, tNoteVel); 
               
             if (tNoteNum == 9) { //DAMPER
                 if( tNoteVel > 0) {
                     digitalWrite(damperSolenoid[2], HIGH); //turn it on 
                   }
                   else {
                     digitalWrite(damperSolenoid[2], LOW); //turn it off
                   }
             }

               
             if (tNoteNum == 10) 
               set_solenoid(6, tNoteVel); 
               
             if (tNoteNum == 11) 
               set_solenoid(7, tNoteVel); 
               
             if (tNoteNum == 12) 
               set_solenoid(8, tNoteVel); 
               
             if (tNoteNum == 13) 
               set_solenoid(9, tNoteVel); 
  
             
             
           }
         break;
             
         default:  
         break;
        }
     
  }
}

void set_solenoid(int solenoidNumber, int velocity) {

     if( velocity > 0) {
       digitalWrite((briefcaseSolenoid[solenoidNumber]), HIGH); //turn it on 
       solenoidVel[solenoidNumber] = velocity;
       solenoidState[solenoidNumber] = 1;
     }
     else {
       digitalWrite((briefcaseSolenoid[solenoidNumber]), LOW); //turn it off
       solenoidState[solenoidNumber] = 0;
     }   
 }
 
 //Function to keep solenoids on until they are supposed to get turned off
void solenoid_interrupt(int solenoidNumber) {
  if (solenoidVelCounter[solenoidNumber] < solenoidVel[solenoidNumber]) {
       solenoidVelCounter[solenoidNumber]++;
      }
      else {
       solenoidVelCounter[solenoidNumber] = 0;
       digitalWrite(briefcaseSolenoid[solenoidNumber], LOW);
       solenoidState[solenoidNumber] = 0;
       
      }
}

