/*****************************************************************************
 * TCL.h
 *
 * Copyright 2011 Christpher De Vries
 * This program is distributed under the Artistic License 2.0, a copy of which
 * is included in the file LICENSE.txt
 ****************************************************************************/
#ifndef TCL2_h
#define TCL2_h
#include <Wprogram.h>
#include <SPI.h>
#include <Color.h>

class TCL2 {
  public:
    TCL2(int length);
    TCL2();
    static void begin();
    static void end();

    void setColor(int position, Color color);
    Color getColor(int position);
    
    void clearFrame();
    void setBackground(Color color);
    void displayNextFrame();

    int getLength();
    
    static boolean direction_clockwise;
	static boolean direction_counterclockwise;
	static boolean CW;
	static boolean CC;
    
  private:
    int _length;
    Color nextFrame[];
    static void sendEmptyByteSet();
    static byte makeFlag(byte red, byte green, byte blue);
    static void sendByteSet(byte flag, byte red, byte green, byte blue);
    static void sendColor(Color color);
};

extern TCL2 TCLX;
#endif
