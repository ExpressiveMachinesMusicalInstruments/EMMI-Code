/*
v. 001
Using Arduino 1.0
STK 7/5/12
LED Control
Uses 1 pin for entire back lighting
*/


#include <MIDI.h>


int AllNotesOff = 123;
int LED[4] = {3,5,6,9};


void setup() {
  //  Serial.begin(9600); 	
//  3, 5, 6, 9, 10, and 11. 
for (int i=0; i<4; i++) {
 pinMode(LED[i], OUTPUT); 
 digitalWrite(LED[i], LOW);
}

  

  MIDI.begin(3); //set MIDI in to Channel 3 
}



void loop() {
  if (MIDI.read()) {    // Is there a MIDI message incoming ?
    
        switch(MIDI.getType()) {		// Get the type of the message we caught
         
          //Control Change Messages
          case ControlChange: {
             int tCtlNum = MIDI.getData1(); //Get Controller Number
             int tCtlVal = MIDI.getData2(); //Get Value
             
             if( tCtlNum == AllNotesOff && tCtlVal == 0 ) { //Controller 123 sends AllOff
               for (int i = 0; i <4; i++) {
                  digitalWrite(LED[i], LOW);
               }
             }
             if (tCtlNum == 64) {
               //Backlight 
               int tScaledVal = map(tCtlVal, 0, 127, 0, 255);
               analogWrite(LED[0], tScaledVal); //PWM write 
             }
             
             
             if (tCtlNum == 65) {
               //Spotlight 1 
               int tScaledVal = map(tCtlVal, 0, 127, 0, 255);
               analogWrite(LED[1], tScaledVal); //PWM write 
             }
             
             if (tCtlNum == 66) {
               //Spotlight 1 
               int tScaledVal = map(tCtlVal, 0, 127, 0, 255);
               analogWrite(LED[2], tScaledVal); //PWM write 
             }
             
             if (tCtlNum == 67) {
               //Spotlight 1 
               int tScaledVal = map(tCtlVal, 0, 127, 0, 255);
               analogWrite(LED[3], tScaledVal); //PWM write 
             }
             
                  
            
          }
           
 //          break;
           
           //NoteOn messages 
         
             
         default:  
         break;
        }
     
  }
}

