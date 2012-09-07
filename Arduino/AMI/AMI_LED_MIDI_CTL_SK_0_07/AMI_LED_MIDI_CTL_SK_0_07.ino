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

// Example code for fast-PWM control of HL1606 LEDs
// public domain, enjoy!
#include <MIDI.h>
#include "HL1606stripPWM.h"

// This library uses Timer 2 for PWM counting and 3 * numLEDs bytes of RAM
// and Arduino pins 11 & 13 (Mega, 51 & 52)

// First value passed is how many LEDs are in your HL1606 strand
// fewer LEDs means less work
// This library uses hardware SPI so pins 11 and 13 are used 
// for Data and Clock output (for the Mega, pins 51 and 52)
// The latch pin (L) can be any pin but pin 10 (Arduino) or 53 (Mega)
// MUST BE AN OUTPUT!
int AllNotesOff = 123;
int latchPin = 10;
HL1606stripPWM strip = HL1606stripPWM(28, latchPin); 


void setup() {
  MIDI.begin();
  // You can customize/control the pulse width modulation and color 
  // resolution by setting how many bits of PWM you want per LED
  // For example, 3 bits is 8 different PWM values per LED and 9 bits, 512
  // values for full color. 4 bits is 16 PWM per LED, 12 bit color with
  // 4096 different colors available.
  // Increasing the PWMbits by 1 means you need *TWICE* as much CPU !!!
  // We suggest starting with 3 and tweaking the other variables to get
  // the fastest SPI and maximum CPU. Then try upping this to 4. For short
  // strips (like 1 meter) that are ok with SPIdiv of 16, you can try 5
  strip.setPWMbits(6);

  // We use the built-in hardware SPI module. We can change the speed
  // of the module to push data out faster. In theory, HL1606's should work with
  // the SPI divider set to 16 but we found that this makes some strips
  // spaz out. Start with 32 and once it works try reducing it to 16
  // If you're lucky, you can even try 8 
  // Valid divider values are: 2, 4, 8, 16, 32, 64, and 128, dont try others!
  strip.setSPIdivider(8);

  // all the hard work of running the strip is done in an interrupt
  // we can configure the interrupt so that we spend more or less
  // time running the strip, letting you do other stuff like sensors
  // or an LED or whatever. Set it between 0 and 100, where 100 means
  // higher quality colorstrip display but no time for anything else.
  strip.setCPUmax(75);    // 70% is what we start at

  // For Arduinos, pin 10 MUST be an output before you begin!
  // (if using a Mega, pin 53 must be an output (instead of 10) )
  // We suggest using pin 10 for the latchPin
  strip.begin();

  // Try to keep the color frequency above 60 Hz (flickery). 100 Hz or higher looks good to most people
}

int r; //R= MIDI values 20-47
int g; //G= MIDI values 72-99
int b; //B= MIDI values 100-127
void loop() {
  if (MIDI.read()) {    // Is there a MIDI message incoming ?
    if (MIDI.getChannel() == 1) {    //filter so we only get messages coming on MIDI channel 1

        switch(MIDI.getType()) {		// Get the type of the message we caught

      case ControlChange: 
        {
          int tCtlNum = MIDI.getData1(); //Get Controller Number
          int tCtlVal = MIDI.getData2(); //Get Value

          if( tCtlNum == AllNotesOff && tCtlVal == 0 ) { //Controller 123 sends AllOff
            for (int i = 0; i < strip.numLEDs(); i++) {
              strip.setLEDcolorPWM(i, 0, 0, 0);
            } 
      //      strip.setLEDcolorPWM(24, 0, 0, 0);
          }

        }

        break;
        
        
      case NoteOn:
        int tNoteNum = MIDI.getData1(); //Get Note Number
        int tNoteVel = MIDI.getData2(); //Get Velocity
        //    BlinkLedNoteOn(MIDI.getData1());
        //STK will streamline this code
        for (int i=0; i< strip.numLEDs(); i++){

          if( tNoteNum == (69) ) {
            r = tNoteVel;
            for (int j=0; j< strip.numLEDs(); j++) {
              strip.setLEDcolorPWM(j, r, g, b);
            }
          }

          if( tNoteNum == (70) ) {
            g = tNoteVel;
            for (int j=0; j< strip.numLEDs(); j++) {
              strip.setLEDcolorPWM(j, r, g, b);
            }
          }

          if( tNoteNum == (71) ) {
            b = tNoteVel;
            for (int j=0; j< strip.numLEDs(); j++) {
              strip.setLEDcolorPWM(j, r, g, b);
            }
          }

          if( tNoteNum == (i+20) ) {
            r = tNoteVel;
            strip.setLEDcolorPWM(i, r, g, b);
          }

          if( tNoteNum == (i+72) ) {
            g = tNoteVel;
            strip.setLEDcolorPWM(i, r, g, b);
          }

          if( tNoteNum == (i+100) ) {
            b = tNoteVel;
            strip.setLEDcolorPWM(i, r, g, b);
          }


        } 


        break;


        //    default:
        break;
      }
    }
  }
}



/************************** Pixel routine */
// this code is from http://www.bliptronics.com Ben Moyes's example code for LEDs, check them out!

// Create a 15 bit color value from R,G,B
unsigned int Color(byte r, byte g, byte b)
{
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F); 

}





