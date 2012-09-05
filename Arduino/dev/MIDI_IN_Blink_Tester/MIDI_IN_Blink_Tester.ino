#include <MIDI.h>
/*
  MIDI Input tutorial
  by Franky
  28/07/2009
*/

#define LED 13   		// LED pin on Arduino board


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
  MIDI.begin(3);            	// Launch MIDI with default options
				// (input channel is default set to 1)
                                // MIDI.begin(chanNumber)
}

void loop() {
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
//    if (MIDI.getChannel() == 3) {
    switch(MIDI.getType()) {		// Get the type of the message we caught
      
        
       case NoteOn:
         BlinkLedNoteOn(MIDI.getData1());
         break;
      
      default:
        break;
    }
  }
//  }
}
