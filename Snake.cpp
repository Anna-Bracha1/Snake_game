#include "Snake.h"

Snake::Snake(/*const string & nm,*/ unsigned char ln, unsigned char th, unsigned char headX, unsigned char headY)
{
	//name = nm;
	Slength = ln;
	thickness = th;
	score = 0;
	head.x = headX;
	head.y = headY;
	head2.x = head.x-1;
  head2.y = head.y;
}

/*int Snake::pickName(const std::string & nm)
{
	name = nm;
	return name;
}*/

int Snake::lengthUp(unsigned char num) //// DO POPRAWKI !!! (uwzglednic kierunek ogona)
{
	Slength+=num;
	return Slength;
}

int Snake::lengthDown(unsigned char num)
{
	Slength-=num;
	return Slength;
}

unsigned char Snake::thicker(unsigned char num)
{
	thickness+=num;
	return thickness;
}

unsigned char Snake::thinner(unsigned char num)
{
	thickness-=num;
	return thickness;
}

int Snake::addToScore(int num)
{
	score+=num;
	return score;
}

void Snake::setHead(MoveHead directionH)
{	
	if(directionH == UP)
	{
		if(head.y == 0)
    {
			head.y=maximumY-1;
      head2.y=maximumY;
    }
    else if(head.y == 1)
    {
      head.y=maximumY;
      head2.y=0;
    }
    else if(head.y == maximumY)
    {
      head.y-=2;
      head2.y=maximumY-1;
    }
		else
    {
			head.y-=2;
      head2.y-=2;
    }
	}
	else if(directionH == DOWN)
	{
		if(head.y == maximumY)
    {
			head.y=1;
      head2.y=0;
    }
    else if(head.y == maximumY-1)
    {
      head.y=0;
      head2.y=maximumY;
    }
    else if(head.y == 0)
    {
      head.y+=2;
      head2.y=1;
    }
		else
    {
			head.y+=2;
      head2.y+=2;
    } 
	}
	else if(directionH == RIGHT)
	{
		if(head.x == maximumX)
    {
			head.x=1;
      head2.x=0;
    }
    else if(head.x == 0)
    {
      head.x+=2;
      head2.x=1;
    }
    else if(head.x == maximumX-1)
    {
      head.x=0;
      head2.x=maximumX;
    }
		else
    {
			head.x+=2;
      head2.x+=2;
    }
	}
	else if(directionH == LEFT)
	{
    if(head.x == 0)
    {
			head.x=maximumX-1;
      head2.x=maximumX;
    }
    else if(head.x == maximumX)
    {
      head.x-=2;
      head2.x=maximumX-1;
    }
    else if(head.x == 1)
    {
      head.x=maximumX;
      head2.x=0;
    }
		else
    {
			head.x-=2;
      head2.x-=2;;
    }
	}
}
