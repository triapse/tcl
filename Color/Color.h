/*
  Color.h
  
  wrapper Object holds 3bytes of rgb and utilities for manipulating them.

// fade and tint . opacity 

*/

#ifndef Color_h
#define Color_h

#include "WProgram.h"

class Color
{
  public:
    Color();
    Color(Color color1, Color color2);
    Color(byte redByte, byte greenByte, byte blueByte);
	Color(String colorName);

	byte getRedByte();
	byte getGreenByte();
	byte getBlueByte();

	void tint(Color tintColor, int percent);
	void fade(int percent);
	Color faded(int percent);
	static Color blend(Color color1, Color color2, int percent);
	Color colorFromGrid(int redInt, int greenInt, int blueInt, int divider);
	Color colorFromGrid(int colorNumber, int divider);

	void serialPrint();

    static Color BLACK;
    static Color WHITE;
    static Color RED;
    static Color GREEN;
    static Color BLUE;
    static Color YELLOW;
    static Color PURPLE;
    static Color ORANGE;

  private:
	byte _redByte;
	byte _greenByte;
	byte _blueByte;
};


extern Color Colors;

#endif