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
