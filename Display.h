#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Snake.h"

//SPRAWDZIC GDZIE TE FUNKCJE UMIESCIC - METODY KLASY, FUNKCJE KLASY???!!!
void decToBin(unsigned char * tab, unsigned char value); // decimal notation to binary notation
unsigned char binToDec(unsigned char * tab); // binary notation to decimal notation
unsigned char expBaseTwo(unsigned char exponent);

class Display
{
	private:
		//unsigned char bitMap[(mapW*mapH)/8]; // XBM bitmap for a display
	public:
    unsigned char bitMap[(mapW*mapH)/8]; // XBM bitmap for a display
		Snake player1;
		Snake player2;
		Display(/*const string & nm1, const string & nm2,*/ unsigned char ln1, unsigned char ln2, unsigned char th1, unsigned char th2, unsigned char headX1, unsigned char headX2, unsigned char headY1, unsigned char headY2);
		~Display() {}
		void setPixel(XY coordinates); // set pixel on the display that represents one pixel of the snake's body
    void clearPixel(IndPos parameters); // clear pixel on the display that represents one pixel of the snake's body
    void setBody(unsigned char playerNum, DIRECTIONS directionH);
		//const unsigned char * getDisplay() { return bitMap; }
};

#endif
