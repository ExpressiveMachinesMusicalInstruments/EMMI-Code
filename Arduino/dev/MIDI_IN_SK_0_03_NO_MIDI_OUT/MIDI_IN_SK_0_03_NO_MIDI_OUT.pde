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

