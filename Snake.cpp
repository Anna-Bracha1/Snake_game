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
  tail.index=((head.y*cols)+((head.x-Slength+1)/8));
  tail.poSition=(head.x-Slength+1) % 8;
  tail2.index=tail.index+(tail.poSition+1)/8;
  tail2.poSition=(tail.poSition+1) % 8;
}

/*int Snake::pickName(const std::string & nm)
{
	name = nm;
	return name;
}*/

int Snake::lengthUp(unsigned char num)
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

void Snake::setHead(DIRECTIONS directionH)
{	
  if((directionH == UP) && (head.x == head2.x) && (((head.y > head2.y) && (head.y != maximumY)) || ((head2.y-head.y) == mapH)))
    directionH = DOWN;
  else if((directionH == DOWN) && (head.x == head2.x) && (((head.y < head2.y) && (head.y != 0)) || ((head.y-head2.y) == mapH)))
    directionH = UP;
  else if((directionH == RIGHT) && (head.y == head2.y) && (((head.x < head2.x) && (head.x != 0)) || ((head.x-head2.x) == mapW)))
    directionH = LEFT;
  else if((directionH == LEFT) && (head.y == head2.y) && (((head.x > head2.x) && (head.x != maximumX)) || ((head2.x-head.x) == mapW)))
    directionH = RIGHT;
  
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
      if(head2.x != head.x)
        head2.y-=1;
      else
        head2.y-=2;
    }
    if(head2.x != head.x)
      head2.x=head.x;
	}
 
	if(directionH == DOWN)
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
      if(head2.x != head.x)
        head2.y+=1;
      else
        head2.y+=2;
    }
    if(head2.x != head.x)
      head2.x=head.x;
	}
	
	if(directionH == RIGHT)
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
      if(head2.y != head.y)
        head2.x+=1;
      else
        head2.x+=2;
    }
    if(head2.y != head.y)
      head2.y=head.y;
      
	}
	
	if(directionH == LEFT)
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
      if(head2.y != head.y)
        head2.x-=1;
      else
        head2.x-=2;
    }
    if(head2.y != head.y)
      head2.y=head.y;
	}
}
