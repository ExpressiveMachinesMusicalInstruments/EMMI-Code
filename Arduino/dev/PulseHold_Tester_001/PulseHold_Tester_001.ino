/*
Copyright 2012 Expressive Machines Musical Instruments

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
*/

/*
PulseHold_Tester_001
v. 001
Using Arduino 1.0
STK 9/12/12
Tester sketch for MIDI control of dual voltage circuit
*/
//#include <Compatibility_v2.5.h>
#ifndef cbi //This allows us to enable pin 1 for use
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#include <MIDI.h>
#include "TimerOne.h"

int AllNotesOff = 123;

int testSolenoidPULSE = 8; //Assign solenoid pins, 24V
int testSolenoidHOLD = 9; // 12V
  
int solenoidVel = 0; //Integers to store solenoid velocities

int solenoidVelCounter = 0;  //Counter for delayed off times
  
boolean solenoidState = 0 //is the solenoid on or off?

void setup() {
  //  Serial.begin(9600); 	
    pinMode(testSolenoidPULSE, OUTPUT);
    pinMode(testSolenoidHOLD, OUTPUT);
    digitalWrite(testSolenoidPULSE, LOW);
    digitalWrite(testSolenoidHOLD, LOW);

  Timer1.initialize(100);  // value in microseconds
  Timer1.attachInterrupt(noteOffInterrupt);  // attaches callback() as a timer overflow interrupt

  MIDI.begin(1); //set MIDI in to Channel 3 
  cbi(UCSR0B, TXEN0);  	//Disables pin 1 so we can use it as an output
}

void noteOffInterrupt() //The Interrupt
{
    if (solenoidState) {   //If the solenoid is on
       solenoid_interrupt();  //Run solenoid_interrupt
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

                digitalWrite(testSolenoidPULSE, LOW);
                digitalWrite(testSolenoidHOLD, LOW);
             } 
          }
           
           break;
           
           //NoteOn messages //DAMPERS: 2,5,9
           case NoteOn: {
             int tNoteNum = (MIDI.getData1()); //Get Note Number, scale for our arrays
             int tNoteVel = MIDI.getData2(); //Get Velocity
             //Lowest note number = 1 
             
             if (tNoteNum == 1) 
               if (tNoteVel > 0) {
                 set_solenoid(tNoteVel);  //Array number
               }

           }
         break;
             
         default:  
         break;
        }
     
  }
}

void set_solenoid(int velocity) {

     if( velocity > 0) {
       digitalWrite(testSolenoidHOLD, LOW);
       digitalWrite(testSolenoidPULSE, HIGH); //turn it on 
       solenoidVel = velocity;
       solenoidState = 1;
     }
     else {
       digitalWrite(testSolenoidHOLD, LOW);
       digitalWrite(testSolenoidPULSE, LOW); //turn it off
       solenoidState = 0;
     }   
 }
 
 //Function to keep solenoids on until they are supposed to get turned off
void solenoid_interrupt() {
  if (solenoidVelCounter < solenoidVel) {
       solenoidVelCounter++;
      }
      else {
       solenoidVelCounter = 0;
       digitalWrite(testSolenoidPULSE, LOW);
       digitalWrite(testSolenoidHOLD, HIGH);
       solenoidState = 0;
       
      }
}

