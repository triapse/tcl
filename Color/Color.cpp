/*****************************************************************************
 * Color.cpp
 *
 * Copyright 2011 Seamus Malone
 ****************************************************************************/

#include "WProgram.h"
#include "Color.h"
#include <SoftwareSerial.h>

// primary and secondary colors
Color Color::BLACK = Color(0x00,0x00,0x00);
Color Color::WHITE = Color(0xff,0xff,0xff);

Color Color::RED = Color(0xff,0x00,0x00);
Color Color::GREEN = Color(0x00,0xff,0x00);
Color Color::BLUE = Color(0x00,0x00,0xff);

Color Color::YELLOW = Color(0xff,0xff,0x00);
Color Color::PURPLE = Color(0xa0,0x20,0xf0);
Color Color::ORANGE = Color(0xff,0xa5,0x00);

Color::Color()
{
   _redByte = random(256);
   _greenByte = random(256);
   _blueByte = random(256);
}

Color::Color(Color color1, Color color2)
{
//	this = color1;
   _redByte = random(color1.getRedByte());
   _greenByte = random(color1.getGreenByte());
   _blueByte = random(color1.getBlueByte());
	tint(color2,random(100));
   
}

Color::Color(byte redByte, byte greenByte, byte blueByte)
{
   _redByte = redByte;
   _greenByte = greenByte;
   _blueByte = blueByte;
}

Color::Color(String colorName)
{
	if (colorName=="White") Color(0xff,0xff,0xff);   	
	if (colorName=="Black") Color(0x00,0x00,0x00);
	if (colorName=="Orange") Color(0xff,0xa5,0x00);
}

byte Color::getRedByte() 
{
	return _redByte;
}

byte Color::getGreenByte() 
{
	return _greenByte;
}

byte Color::getBlueByte() 
{
	return _blueByte;
}

void Color::fade(int percent)
{
	_redByte = _redByte*(((float)percent/100));
	_greenByte = _greenByte*(((float)percent/100));
	_blueByte = _blueByte*(((float)percent/100));
}

Color Color::faded(int percent)
{
	byte redByte = _redByte*(((float)percent/100));
	byte greenByte = _greenByte*(((float)percent/100));
	byte blueByte = _blueByte*(((float)percent/100));
	
	return Color(redByte,greenByte,blueByte);
}

void Color::tint(Color tintColor, int percent)
{
	int lessPercent = 100 - percent;
    _redByte = (_redByte * lessPercent) + (tintColor.getRedByte() * percent);
    _greenByte = (_greenByte * lessPercent) + (tintColor.getGreenByte() * percent);
    _blueByte = (_blueByte * lessPercent) + (tintColor.getBlueByte() * percent);
}

Color Color::blend(Color color1, Color color2, int percent)
{
	Color blendColor = color1;
	blendColor.tint(color2, percent);
	return blendColor;
}

Color Color::colorFromGrid(int redInt, int greenInt, int blueInt, int divider) {
	int multiplier = 256/divider;
	return Color(redInt*multiplier, greenInt*multiplier, blueInt*multiplier);
}

Color Color::colorFromGrid(int colorNumber, int divider) {
	int redInt = colorNumber / (divider*divider);
	int greenInt = (colorNumber % (divider*divider)) / divider;
	int blueInt = (colorNumber % (divider*divider)) % divider;
	
	return colorFromGrid(redInt, greenInt, blueInt, divider);
}

void Color::serialPrint() {
      Serial.print(_redByte,HEX);
      Serial.print(" ");
      Serial.print(_greenByte,HEX);
      Serial.print(" ");
      Serial.print(_blueByte,HEX);
      Serial.println();
}


