#include <MIDI.h>
/*
  MIDI Input tutorial
  by Franky
  28/07/2009
*/

#define LED 13   		// LED pin on Arduino board

void BlinkLedPC(byte num) { 	// Basic blink function
  for (byte i=0;i<num;i++) {
    digitalWrite(LED,HIGH);
    delay(50);
    digitalWrite(LED,LOW);
    delay(50);
  }
}

void BlinkLedNoteOn(byte num) { 	// Basic blink function
  for (byte i=0;i<num;i++) {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(50);
  }
}


void setup() {
  pinMode(LED, OUTPUT);
  MIDI.begin();            	// Launch MIDI with default options
				// (input channel is default set to 1)
}

void loop() {
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    switch(MIDI.getType()) {		// Get the type of the message we caught
      case PC:                          // If it is a Program Change
	BlinkLedPC(MIDI.getData1());	// Blink the LED a number of times 
					// correponding to the program number 
					// (0 to 127, it can last a while..)
        break;
        
       case NoteOn:
         BlinkLedNoteOn(MIDI.getData1());
         break;
      
      default:
        break;
    }
  }
}
