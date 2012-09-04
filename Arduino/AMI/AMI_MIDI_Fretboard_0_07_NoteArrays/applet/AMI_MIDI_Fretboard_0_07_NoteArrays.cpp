/*
  AMI-MIDI code v. 0.07 STK
 For Fretboard (motor control) 
 Implemented control to turn MIDI notes on and off
 */
#include <MIDI.h>
#include "WProgram.h"
void setup();
void loop();
int fretSolenoid[17] = {
  18,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};


int midiNote48[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote49[] = {
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote50[] = {
  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote51[] = {
  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote52[] = {
  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote53[] = {
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote54[] = {
  0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote55[] = {
  0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote56[] = {
  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote57[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int midiNote58[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
int midiNote59[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
int midiNote60[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
int midiNote61[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
int midiNote62[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
int midiNote63[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
int midiNote64[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
int midiNote65[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};


int AllNotesOff = 123;

void setup() {
  //  Serial.begin(9600); 	
  for (int i =0;i < 18; i++) {
    pinMode(fretSolenoid[i], OUTPUT);
    digitalWrite(fretSolenoid[i], LOW);
  }


  //  pinMode(pick1, OUTPUT);
  //  pinMode(pick2, OUTPUT);
  //  digitalWrite(pick1, HIGH); //pulse pick1 at setup to initialize 
  //  delay(82);
  //  digitalWrite(pick1, LOW);
  //  digitalWrite(pick2, LOW);

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

          if( tCtlNum == AllNotesOff && tCtlVal == 0 ) { //Controller 123 sends AllOff
            for (int i = 0; i < 18; i++) {
              digitalWrite((fretSolenoid[i-1]), LOW);
            }      

            //               digitalWrite(pick1, LOW);
            //               digitalWrite(pick2, LOW);  

          } 
        }

        break;

        //NoteOn messages 
      case NoteOn: 
        {
          int tNoteNum = MIDI.getData1(); //Get Note Number
          int tNoteVel = MIDI.getData2(); //Get Velocity

          for (int i = 0; i < 18; i++) {  //Loop gets data from MIDI input
            if( tNoteNum == i ) {
              if( tNoteVel > 0) {
                digitalWrite((fretSolenoid[i-1]), HIGH); //turn it on 
              }
              else {
                digitalWrite((fretSolenoid[i-1]), LOW); //turn it off
              }
            }    

            if( tNoteNum == 48 ) {
              for (int j=0; j<17; j++){
                if(midiNote48[j] == 0){
                  digitalWrite(fretSolenoid[j], LOW);
                }
                else {
                  digitalWrite(fretSolenoid[j], HIGH);
                }
              }  
            }
            if( tNoteNum == 49 ) {
              for (int j=0; j<18; j++){
                if(midiNote49[j] == 0){
                  digitalWrite(fretSolenoid[j], LOW);
                }
                else {
                  digitalWrite(fretSolenoid[j], HIGH);
                }
              }  
            }
            if( tNoteNum == 50 ) {
              for (int j=0; j<18; j++){
                if(midiNote50[j] == 0){
                  digitalWrite(fretSolenoid[j], LOW);
                }
                else {
                  digitalWrite(fretSolenoid[j], HIGH);
                }
              }  
            }   
          if( tNoteNum == 51 ) {
             for (int j=0; j<18; j++){
               if(midiNote51[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 52 ) {
             for (int j=0; j<18; j++){
               if(midiNote52[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 53 ) {
             for (int j=0; j<18; j++){
               if(midiNote53[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 54 ) {
             for (int j=0; j<18; j++){
               if(midiNote54[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 55 ) {
             for (int j=0; j<18; j++){
               if(midiNote55[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 56 ) {
             for (int j=0; j<18; j++){
               if(midiNote56[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 57 ) {
             for (int j=0; j<18; j++){
               if(midiNote57[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 58 ) {
             for (int j=0; j<18; j++){
               if(midiNote58[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 59 ) {
             for (int j=0; j<18; j++){
               if(midiNote59[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 60 ) {
             for (int j=0; j<18; j++){
               if(midiNote60[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
         if( tNoteNum == 61 ) {
             for (int j=0; j<18; j++){
               if(midiNote61[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
          if( tNoteNum == 62 ) {
             for (int j=0; j<18; j++){
               if(midiNote62[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
          if( tNoteNum == 63 ) {
             for (int j=0; j<18; j++){
               if(midiNote63[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
          if( tNoteNum == 64 ) {
             for (int j=0; j<18; j++){
               if(midiNote64[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
             }  
           }
          if( tNoteNum == 65 ) {
             for (int j=0; j<18; j++){
               if(midiNote65[j] == 0){
                 digitalWrite(fretSolenoid[j], LOW);
               }
               else {
                 digitalWrite(fretSolenoid[j], HIGH);
               }
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




int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

