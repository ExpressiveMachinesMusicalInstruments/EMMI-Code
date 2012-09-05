/*
  Digital Pot Control--WITH MIDI_STK
 
 This example controls an Analog Devices AD5206 digital potentiometer.
 The AD5206 has 6 potentiometer channels. Each channel's pins are labeled
 A - connect this to voltage
 W - this is the pot's wiper, which changes when you set it
 B - connect this to ground.
 
 The AD5206 is SPI-compatible,and to command it, you send two bytes, 
 one with the channel number (0 - 5) and one with the resistance value for the
 channel (0 - 255).  
 
 The circuit:
 * All A pins  of AD5206 connected to +5V
 * All B pins of AD5206 connected to ground
 * An LED and a 220-ohm resisor in series connected from each W pin to ground
 * CS - to digital pin 10  (SS pin)
 * SDI - to digital pin 11 (MOSI pin)
 * CLK - to digital pin 13 (SCK pin)
 
 created 10 Aug 2010 
 by Tom Igoe
 
 Thanks to Heather Dewey-Hagborg for the original tutorial, 2005
 ` 
 */

//cc 1 = mic 1
//cc 2 = mic 2
//cc 8 = feedback
// cc 9 = AMI in
// cc 17 = AMI out
// cc 18 = line out

// inslude the SPI library:
#include <SPI.h>
#include <MIDI.h>

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
int AllNotesOff = 123;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  // initialize SPI:
  MIDI.begin(3);            	// Launch MIDI with default options--number is input channel number
  SPI.begin(); 

  //Initialize digiPot so it starts at 0
  for (int i=0; i<6; i++) {
    digitalPotWrite(i, 0);
  }


}


void loop() {
  if (MIDI.read()) {    // Is there a MIDI message incoming ?

        switch(MIDI.getType()) {		// Get the type of the message we caught

      case ControlChange:
        int tCCnum = MIDI.getData1(); //Get CC number
        int tCCval = MIDI.getData2(); //Get CC value

        if( tCCnum == AllNotesOff && tCCval == 0 ) { //Controller 123 sends AllOff
          for (int i=0; i<6; i++) {
            digitalPotWrite(i, 0);
          }

        } 

        if( tCCnum == 1 ) {
          digitalPotWrite(0, (tCCval*2));
        } 
        if( tCCnum == 2 ) {
          digitalPotWrite(1, (tCCval*2));
        } 
        if( tCCnum == 8 ) {
          digitalPotWrite(2, (tCCval*2));
        }
        if( tCCnum == 9 ) {
          digitalPotWrite(3, (tCCval*2));
        }
        if( tCCnum == 17 ) {
          digitalPotWrite(4, (tCCval*2));
        }
        if( tCCnum == 18 ) {
          digitalPotWrite(5, (tCCval*2));
        }
        break;


        //    default:
        break;
      }
    
  }
}

int digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin,LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH); 
}

