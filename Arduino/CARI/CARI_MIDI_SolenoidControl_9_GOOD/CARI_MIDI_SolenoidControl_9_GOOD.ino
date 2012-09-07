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

///DOES NOT WORK!!!******************

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#include <MIDI.h>


int midiNote40[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int midiNote41[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
int midiNote42[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
int midiNote43[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0};
int midiNote44[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
int midiNote45[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
int midiNote46[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
int midiNote47[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
int midiNote48[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote49[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote50[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote51[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote52[] = {
  1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote53[] = {
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote54[] = {
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote55[] = {
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote56[] = {
  1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote57[] = {
  1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote58[] = {
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote59[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


int AllNotesOff = 123;

void setup() {
  MIDI.begin();            	// Launch MIDI with default options--number is input channel number
  cbi(UCSR0B, TXEN0);
  for (int i =0;i < 20; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }


}

void loop() {
  if (MIDI.read()) {    // Is there a MIDI message incoming ?
    if (MIDI.getChannel() == 1) {    //filter so we only get messages coming on MIDI channel 1

        switch(MIDI.getType()){

      case ControlChange: 
        {
          int tCtlNum = MIDI.getData1(); //Get Controller Number
          int tCtlVal = MIDI.getData2(); //Get Value

          if( tCtlNum == AllNotesOff && tCtlVal == 0 ) { //Controller 123 sends AllOff
            for (int i = 1; i < 20; i++) {
              digitalWrite(i, LOW);
            }      

            //               digitalWrite(pick1, LOW);
            //               digitalWrite(pick2, LOW);  

          } 
        }

        break;

      case NoteOn: 
        {
          int tNoteNum = MIDI.getData1(); //Get Note Number
          int tNoteVel = MIDI.getData2(); //Get Velocity

          //****************** BEGIN DIRECT CONTROL *******************************

          if (tNoteNum == 1 && tNoteVel > 0) {
            digitalWrite(1, HIGH);
          }
          else if (tNoteNum == 1 && tNoteVel == 0) {
            digitalWrite(1, LOW);
          }

          if (tNoteNum == 2 && tNoteVel > 0) {
            digitalWrite(2, HIGH);
          }
          else if (tNoteNum == 2 && tNoteVel == 0)  {
            digitalWrite(2, LOW);
          }
          if (tNoteNum == 3 && tNoteVel > 0) {
            digitalWrite(3, HIGH);
          }
          else if (tNoteNum == 3 && tNoteVel == 0)  {
            digitalWrite(3, LOW);
          }
          if (tNoteNum == 4 && tNoteVel > 0) {
            digitalWrite(4, HIGH);
          }
          else if (tNoteNum == 4 && tNoteVel == 0)  {
            digitalWrite(4, LOW);
          }
          if (tNoteNum == 5 && tNoteVel > 0) {
            digitalWrite(5, HIGH);
          }
          else if (tNoteNum == 5 && tNoteVel == 0)  {
            digitalWrite(5, LOW);
          }
          if (tNoteNum == 6 && tNoteVel > 0) {
            digitalWrite(6, HIGH);
          }
          else if (tNoteNum == 6 && tNoteVel == 0)  {
            digitalWrite(6, LOW);
          }
          if (tNoteNum == 7 && tNoteVel > 0) {
            digitalWrite(7, HIGH);
          }
          else if (tNoteNum == 7 && tNoteVel == 0)  {
            digitalWrite(7, LOW);
          }
          if (tNoteNum == 8 && tNoteVel > 0) {
            digitalWrite(8, HIGH);
          }
          else if (tNoteNum == 8 && tNoteVel == 0)  {
            digitalWrite(8, LOW);
          }
          if (tNoteNum == 9 && tNoteVel > 0) {
            digitalWrite(9, HIGH);
          }
          else if (tNoteNum == 9 && tNoteVel == 0)  {
            digitalWrite(9, LOW);
          }
          if (tNoteNum == 10 && tNoteVel > 0) {
            digitalWrite(10, HIGH);
          }
          else if (tNoteNum == 10 && tNoteVel == 0)  {
            digitalWrite(10, LOW);
          }
          if (tNoteNum == 11 && tNoteVel > 0) {
            digitalWrite(11, HIGH);
          }
          else if (tNoteNum == 11 && tNoteVel == 0)  {
            digitalWrite(11, LOW);
          }
          if (tNoteNum == 12 && tNoteVel > 0) {
            digitalWrite(12, HIGH);
          }
          else if (tNoteNum == 12 && tNoteVel == 0)  {
            digitalWrite(12, LOW);
          }
          if (tNoteNum == 13 && tNoteVel > 0) {
            digitalWrite(13, HIGH);
          }
          else if (tNoteNum == 13 && tNoteVel == 0)  {
            digitalWrite(13, LOW);
          }
          if (tNoteNum == 14 && tNoteVel > 0) {
            digitalWrite(14, HIGH);
          }
          else if (tNoteNum == 14 && tNoteVel == 0)  {
            digitalWrite(14, LOW);
          }
          if (tNoteNum == 15 && tNoteVel > 0) {
            digitalWrite(15, HIGH);
          }
          else if (tNoteNum == 15 && tNoteVel == 0)  {
            digitalWrite(15, LOW);
          }
          if (tNoteNum == 16 && tNoteVel > 0) {
            digitalWrite(16, HIGH);
          }
          else if (tNoteNum == 16 && tNoteVel == 0)  {
            digitalWrite(16, LOW);
          }
          if (tNoteNum == 17 && tNoteVel > 0) {
            digitalWrite(17, HIGH);
          }
          else if (tNoteNum == 17 && tNoteVel == 0)  {
            digitalWrite(17, LOW);
          }
          if (tNoteNum == 18 && tNoteVel > 0) {
            digitalWrite(18, HIGH);
          }
          else if (tNoteNum == 18 && tNoteVel == 0)  {
            digitalWrite(18, LOW);
          }
          if (tNoteNum == 19 && tNoteVel > 0) {
            digitalWrite(19, HIGH);
          }
          else if (tNoteNum == 19 && tNoteVel == 0)  {
            digitalWrite(19, LOW);
          }

          //****************** END DIRECT CONTROL *******************************

          //****************** BEGIN NOTE COLLECTIONS ***************************
          if( tNoteNum == 40 ) {
     //       digitalWrite(1, HIGH); //FOR TESTING PURPOSES
            for (int j=0; j<20; j++){
              if(midiNote40[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote40[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
         if( tNoteNum == 41 ) {
            for (int j=0; j<20; j++){
              if(midiNote41[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote41[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
         
         if( tNoteNum == 42 ) {
            for (int j=0; j<20; j++){
              if(midiNote42[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote42[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 43 ) {
            for (int j=0; j<20; j++){
              if(midiNote43[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote43[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 44 ) {
            for (int j=0; j<20; j++){
              if(midiNote44[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote44[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 45 ) {
            for (int j=0; j<20; j++){
              if(midiNote45[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote45[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 46 ) {
            for (int j=0; j<20; j++){
              if(midiNote46[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote46[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 47 ) {
            for (int j=0; j<20; j++){
              if(midiNote47[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote47[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 48 ) {
            for (int j=0; j<20; j++){
              if(midiNote48[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote48[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 49 ) {
            for (int j=0; j<20; j++){
              if(midiNote49[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote49[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
         if( tNoteNum == 50 ) {
            for (int j=0; j<20; j++){
              if(midiNote50[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote50[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
         
         if( tNoteNum == 51 ) {
            for (int j=0; j<20; j++){
              if(midiNote51[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote51[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 52 ) {
            for (int j=0; j<20; j++){
              if(midiNote52[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote52[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 53 ) {
            for (int j=0; j<20; j++){
              if(midiNote53[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote53[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 54 ) {
            for (int j=0; j<20; j++){
              if(midiNote54[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote54[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 55 ) {
            for (int j=0; j<20; j++){
              if(midiNote55[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote55[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 56 ) {
            for (int j=0; j<20; j++){
              if(midiNote56[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote56[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 57 ) {
            for (int j=0; j<20; j++){
              if(midiNote57[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote57[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          }
          
          if( tNoteNum == 58 ) {
            for (int j=0; j<20; j++){
              if(midiNote58[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote58[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          } 
          
          if( tNoteNum == 59 ) {
            for (int j=0; j<20; j++){
              if(midiNote59[j] == 1){
                digitalWrite((j+1), HIGH);
              }
              else if (midiNote59[j] == 0){
                digitalWrite((j+1), LOW);
              }
            }  
          } 
          
          
          
        }
        //****************** END NOTE COLLECTIONS ***************************



        break;

      default:
        break;
      }
    }
  }
}




