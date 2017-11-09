#ifndef SNAKE_H_
#define SNAKE_H_

//#include <string>
//#include <iostream>
#include "math.h"
//using std::cout;
//using std::endl;
//using std::string;

#define maximumX 127 //the maximum X coordinate on the display
#define maximumY 63 //the maximum Y coordinate on the display
enum MoveHead {UP, DOWN, RIGHT, LEFT};

struct XY
{
	unsigned char x;
	unsigned char y;
};

struct IndPos
{
  int index;
  int poSition;
};

class Snake
{
	private:
		//std::string name; //name picked by a player
		int score; // points gained by a player
	public:
		int Slength; //number of pixels difining how long snake is
		unsigned char thickness; //how may lines snake consists of
		XY head;
    XY head2;
    IndPos tail; //index of the byte in the bitMap where the last pixel of the Snake's body is(0-1023) and the exact position of this pixel(0-7)
    IndPos tail2;
		Snake(/*const std::string & nm,*/ unsigned char ln, unsigned char th, unsigned char headX, unsigned char headY); //SPRAWDZIC CZY TU TEZ SIE DAJE WSTEPNE PRZYPISANIA!!!!
		~Snake() {}
		//int pickName(const std::string & nm);
		int lengthUp(unsigned char num); // add num pixels to the end of the snake
		int lengthDown(unsigned char num); // take num pixels from the end of the snake
		unsigned char thicker(unsigned char num);
		unsigned char thinner(unsigned char num);
		int addToScore(int num);
		//string viewName() { return name; }
		int viewScore() { return score; }
		void setHead(MoveHead directionH);
};

#endif
