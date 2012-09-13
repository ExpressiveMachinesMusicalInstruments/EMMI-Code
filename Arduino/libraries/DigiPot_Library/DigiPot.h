/*
  DigiPot.h - Library for communicating with the MCP4251 digital potentiometer via SPI.
  Created by Stephen Jones, April 22, 2010.
  Special thanks to Osgeld from the Arduino forums.
  Released into the public domain.
*/

#ifndef DigiPot_h
#define DigiPot_h

#include "WProgram.h"

class DigiPot
{
  public:
    DigiPot(int cs, int sck, int sdi);
	void write(int pot, int value);
	void clear(int clearPot);
  private:
    int _cs;
	int _sck;
	int _sdi;
	byte _commandData;
};

#endif