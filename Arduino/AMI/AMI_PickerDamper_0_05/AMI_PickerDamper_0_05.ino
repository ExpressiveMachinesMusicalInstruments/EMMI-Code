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
  STK 6/25/2012
  Picker/Damper 0.05, 
 Implements note 18 for picking, re-pick with note off
 */
#include <MIDI.h>
int pick1 = 7;
int pick2 = 8;
int damper = 9;
int AllNotesOff = 123;
int RESET = 121; //used for resetting controllers
boolean pickSelect = true; //True=pick1

void setup() {

  pinMode(pick1, OUTPUT);
  pinMode(pick2, OUTPUT);
  pinMode(damper, OUTPUT);

  digitalWrite(pick2, HIGH); //pulse pick2 at setup to initialize 
  delay(82);
  digitalWrite(pick1, LOW);
  digitalWrite(pick2, LOW);
  digitalWrite(damper, LOW);

  MIDI.begin();            	
}


void loop() {
  if (MIDI.read()) {    // Is there a MIDI message incoming ?
    if (MIDI.getChannel() == 1) {    //filter so we only get messages coming on MIDI channel 1

        switch(MIDI.getType()) {		// Get the type of the message we caught

        //Control Change Messages
      case ControlChange: 
        {
          int tCtlNum = MIDI.getData1(); //Get Controller Number
          int tCtlVal = MIDI.getData2(); //Get Value

          if( tCtlNum == RESET && tCtlVal == 0 ) { //Controller 121 sends AllOff

            digitalWrite(pick1, LOW);//Make sure solenoids are off
            digitalWrite(pick2, LOW);
            
            digitalWrite(pick2, HIGH); //pulse pick2 to get it out of the way 
            delay(82);
            digitalWrite(pick1, LOW);
            digitalWrite(pick2, LOW);
            digitalWrite(damper, LOW);

          } 

          if( tCtlNum == AllNotesOff && tCtlVal == 0 ) { //Controller 123 sends AllOff

            digitalWrite(pick1, LOW);
            digitalWrite(pick2, LOW);
            digitalWrite(damper, LOW);  

          } 
        }

        break;

        //NoteOn messages 
      case NoteOn: 
        {
          int tNoteNum = MIDI.getData1(); //Get Note Number
          int tNoteVel = MIDI.getData2(); //Get Velocity


          if( tNoteNum == 0 ) {
            if( tNoteVel > 0) {
              digitalWrite(damper, HIGH); //turn it on 
            }
            else {
              digitalWrite(damper, LOW);
            }
          }

          if( tNoteNum == 18 ) {
            //if pickselect = true, pick1
            if (tNoteVel > 0) {
              if (pickSelect) {
                digitalWrite(pick2, LOW);
                digitalWrite(pick1, HIGH); //turn it on 
                pickSelect = false;
              }
              else {
                digitalWrite(pick1, LOW);
                digitalWrite(pick2, HIGH); //turn it on 
                pickSelect = true;
              }
              
            }
            if (tNoteVel == 0) {
              if(pickSelect) {
                digitalWrite(pick2, LOW);
              }
              else if (!pickSelect) {  
                digitalWrite(pick1, LOW);
              }
            }
           
          }



        }
        break;

      default:  
        break;
      }
    }
  }
}




