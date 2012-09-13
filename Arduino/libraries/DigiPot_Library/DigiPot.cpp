/*
  DigiPot.cpp - Library for communicating with the MCP4251 digital potentiometer via SPI.
  Created by Stephen Jones, April 22, 2010.
  Special thanks to Osgeld from the Arduino forums.
  Released into the public domain.
*/
#include "WProgram.h"
#include "DigiPot.h"

DigiPot::DigiPot(int cs, int sck, int sdi)
{
  pinMode(cs, OUTPUT);
  pinMode(sck, OUTPUT);
  pinMode(sdi, OUTPUT);
  _cs = cs;
  _sck = sck;
  _sdi = sdi;
}

void DigiPot::write(int pot, int value)
{
  if (pot == 0) {
    _commandData = B00000000;
  } else {
    _commandData = B00010000;
  }
  digitalWrite(_cs, LOW);
  shiftOut(_sdi, _sck, MSBFIRST, _commandData);
  shiftOut(_sdi, _sck, MSBFIRST, value);
  digitalWrite(_cs, HIGH);
}

void DigiPot::clear(int clearPot)
{
  if (clearPot == 0) {
    _commandData = B00000000;
  } else {
    _commandData = B00010000;
  }
  digitalWrite(_cs, LOW);
  shiftOut(_sdi, _sck, MSBFIRST, _commandData);
  shiftOut(_sdi, _sck, MSBFIRST, 0);
  digitalWrite(_cs, HIGH);
}