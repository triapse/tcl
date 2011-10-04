/*****************************************************************************
 * Tcl.cpp
 *
 * Copyright 2011 Christpher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt
 
     if (debugFrameOutput) {
      Serial.print(nextFrame[pixel].getRedByte(),HEX);
      Serial.print(" ");
      Serial.print(nextFrame[pixel].getGreenByte(),HEX);
      Serial.print(" ");
      Serial.print(nextFrame[pixel].getBlueByte(),HEX);
      Serial.println();
    }
 
 ****************************************************************************/

#include "Wprogram.h"
#include "SPI.h"
#include "TCL2.h"
#include "Color.h"

// todo figure out how to dynamically assign
Color nextFrame[150];


// move clockwise etc to TCL
boolean TCL2::direction_clockwise = true;
boolean TCL2::direction_counterclockwise = false;
boolean TCL2::CW = true; // just shortcut for clock-wise
boolean TCL2::CC = false; // just short for counter-clock

TCL2::TCL2() 
{
	_length = 150;
}

TCL2::TCL2(int length)
{
	_length = length;
}

void TCL2::begin() {
// TODO move to constructor...

  // Set the SPI parameters
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
}

void TCL2::end() {
  SPI.end();
}

byte TCL2::makeFlag(byte red, byte green, byte blue) {
  byte flag = 0;

  flag = (red&0xC0)>>6;
  flag |= ((green&0xC0)>>4);
  flag |= ((blue&0xC0)>>2);
  return ~flag;
}

void TCL2::sendByteSet(byte flag, byte red, byte green, byte blue) {
  SPI.transfer(flag);
  SPI.transfer(blue);
  SPI.transfer(green);
  SPI.transfer(red);
}

void TCL2::sendColor(Color color) {
  byte flag = makeFlag(color.getRedByte(),color.getGreenByte(),color.getBlueByte());
  sendByteSet(flag,color.getRedByte(),color.getGreenByte(),color.getBlueByte());
}

void TCL2::sendEmptyByteSet() {
  sendByteSet(0x00,0x00,0x00,0x00);
}

void TCL2::clearFrame() {
	setBackground(Colors.BLACK);
}

void TCL2::setBackground(Color color) {
    int pixel;
    for(pixel=0;pixel<_length;pixel++) {
      setColor(pixel, color);
    }
}

void TCL2::displayNextFrame() {
  sendEmptyByteSet();
  int pixel;
  for(pixel=0;pixel<_length;pixel++) {
    sendColor(nextFrame[pixel]);
  }
  sendEmptyByteSet();
}

 
void TCL2::setColor(int position, Color color) {
  nextFrame[position] = color;
}

Color TCL2::getColor(int position) {
  return nextFrame[position];
}

int TCL2::getLength() {
  return _length;
}



