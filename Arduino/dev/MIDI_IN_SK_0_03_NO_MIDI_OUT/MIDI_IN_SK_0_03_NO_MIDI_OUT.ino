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

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#include <MIDI.h>
/*
  5/6/2011--STK has disabled the MIDI Output 
 and is successfully using pin 1 as a digital out
 
 Based on MIDI Input tutorial
 by Franky
 28/07/2009
 */




#define PIN 13   		// LED pin on Arduino board

void BlinkLedPC(byte num) { 	// Basic blink function
  for (byte i=0;i<num;i++) {
    digitalWrite(PIN,HIGH);
    delay(50);
    digitalWrite(PIN,LOW);
    delay(50);
  }
}

void BlinkLedNoteOn(byte num) { 	// Basic blink function
  for (byte i=0;i<num;i++) {
    digitalWrite(PIN,HIGH);
    delay(100);
    digitalWrite(PIN,LOW);
    delay(100);
  }
}


void setup() {

//  MIDI.begin(MIDI_CHANNEL_OMNI); //THIS works with all channels
  MIDI.begin(2);
  cbi(UCSR0B, TXEN0);
  pinMode(PIN, OUTPUT);
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);			
}

void loop() {
  if (MIDI.read()) { 
//    if (MIDI.getChannel() == 10) {    // Is there a MIDI message incoming ?
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
//  }
}

