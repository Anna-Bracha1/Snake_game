#include "Display.h"
#include <SPI.h>

Display::Display(/*const string & nm1, const string & nm2,*/ unsigned char ln1, unsigned char ln2, unsigned char th1, unsigned char th2, unsigned char headX1, unsigned char headX2, unsigned char headY1, unsigned char headY2)
: player1(/*nm1*/ln1, th1, headX1, headY1), player2(/*nm1*/ln2, th2, headX2, headY2)
//SPRAWDZIC JAK TO JEST Z TYMI KONSTRUKTORAMI (KIEDY WYWOLUJA SIE KONSTRUKTORY ZMIENNYCH WEWNATRZ KLASY!!!!
{
	for(int i=0; i<(maxIndex+1); i++)
		bitMap[i]=0;
	
	XY temp=player1.head;
	for(int i=0; i<player1.Slength; i++)
	{
		setPixel(temp);
		temp.x-=1;
	}
  
	temp=player2.head;
	for(int i=0; i<player2.Slength; i++)
	{
		setPixel(temp);
		temp.x-=1;
	}
}

void Display::setPixel(XY coordinates)
{
	unsigned char bin[8]; // table to store binary notation of the currently processed byte
	int index=((coordinates.y*cols)+(coordinates.x/8)); // index in the XBM bitmap
	unsigned char poSition=coordinates.x % 8;
	decToBin(bin, bitMap[index]);
	bin[poSition]=1;
	bitMap[index]=binToDec(bin);
}

void Display::clearPixel(IndPos parameters)
{
  unsigned char bin[8]; // table to store binary notation of the currently processed byte
  
  decToBin(bin, bitMap[parameters.index]);
  //Serial.print("Index: ");
  //Serial.print(parameters.index);
  //Serial.print("Position: ");
  //Serial.print(parameters.poSition);
  //Serial.print("\nbins:\n");
  //Serial.print(binToDec(bin));
  //Serial.print("\n");
  bin[parameters.poSition]=0;
  //Serial.print(binToDec(bin));
  //Serial.print("\n");
  bitMap[parameters.index]=binToDec(bin);
}

void Display::setBody(unsigned char playerNum, DIRECTIONS directionH)
{
  unsigned char bin[8]; // table to store binary notation of the currently processed byte
  DIRECTIONS directionT;
  
  if(playerNum == 1)
  {
    player1.setHead(directionH);
    setPixel(player1.head);
    setPixel(player1.head2);
    
    clearPixel(player1.tail);
    clearPixel(player1.tail2);

    int nextIndex;
    
    if(player1.tail2.index < cols)
      nextIndex=maxIndex-(cols-1-player1.tail2.index);
    else
      nextIndex=player1.tail2.index-cols;
    
    decToBin(bin, bitMap[nextIndex]);
    while(1)
    {
      if(bin[player1.tail2.poSition] == 1)
      {
        player1.tail.index=nextIndex;
        player1.tail.poSition=player1.tail2.poSition;
        directionT=UP;
        break;
      }

      if(player1.tail2.index > (maxIndex-cols))
        nextIndex=(cols-1)-(maxIndex-player1.tail2.index);
      else
        nextIndex=player1.tail2.index+cols;
      
      decToBin(bin, bitMap[nextIndex]);
      if(bin[player1.tail2.poSition] == 1)
      {
        player1.tail.index=nextIndex;
        player1.tail.poSition=player1.tail2.poSition;
        directionT=DOWN;
        break;
      }

      if((player1.tail2.index+(player1.tail2.poSition+1)/8) == (maxIndex+1))
        nextIndex=maxIndex-cols+1;
      else
        nextIndex=player1.tail2.index+(player1.tail2.poSition+1)/8;
      
      decToBin(bin, bitMap[nextIndex]);
      if(bin[(player1.tail2.poSition+1)%8] == 1)
      {
        player1.tail.index=nextIndex;
        player1.tail.poSition=(player1.tail2.poSition+1)%8;
        directionT=RIGHT;
        break;
      }

      if(player1.tail2.poSition == 0)
      {
        if(player1.tail2.index == 0)
          player1.tail.index=cols-1;
        else
          player1.tail.index-=1;
        
        player1.tail.poSition=7;
      }
      else
      {
        player1.tail.index=player1.tail2.index;
        player1.tail.poSition=player1.tail2.poSition-1;
      }
      directionT=LEFT;
      break;
    }
    
    if(directionT == UP)
    {
      if(player1.tail.index < cols)
        player1.tail2.index=maxIndex-(cols-1-player1.tail.index);
      else
        player1.tail2.index=player1.tail.index-cols;
      
      player1.tail2.poSition=player1.tail.poSition;
    }  
    
    else if(directionT == DOWN)
    {
      if(player1.tail.index > (maxIndex-cols))
        player1.tail2.index=maxIndex-(cols-1-player1.tail.index);
      else
        player1.tail2.index=player1.tail.index+cols;
      
      player1.tail2.poSition=player1.tail.poSition;
    }
    
    else if(directionT == RIGHT)
    {
      if((player1.tail.index+(player1.tail.poSition+1)/8) == (maxIndex+1))
      {
        player1.tail2.index=maxIndex-cols+1;
        player1.tail2.poSition=0;
      }
      else
      {
        player1.tail2.index=player1.tail.index+(player1.tail.poSition+1)/8;
        player1.tail2.poSition=(player1.tail.poSition+1) % 8;
      }
    }
    
    else
    {
      if(player1.tail.poSition == 0)
      {
        if(player1.tail.index == 0)
          player1.tail2.index=cols-1;
        else
          player1.tail2.index-=1;
          
        player1.tail2.poSition=7;
      }
      else
      {
        player1.tail2.index=player1.tail.index;
        player1.tail2.poSition=player1.tail.poSition-1;
      }
    }
  }

  else if(playerNum == 2)
  {
    player2.setHead(directionH);
    setPixel(player2.head);
    setPixel(player2.head2);
    
    clearPixel(player2.tail);
    clearPixel(player2.tail2);

    int nextIndex;
    
    if(player2.tail2.index < cols)
      nextIndex=maxIndex-(cols-1-player2.tail2.index);
    else
      nextIndex=player2.tail2.index-cols;
    
    decToBin(bin, bitMap[nextIndex]);
    while(1)
    {
      if(bin[player2.tail2.poSition] == 1)
      {
        player2.tail.index=nextIndex;
        player2.tail.poSition=player2.tail2.poSition;
        directionT=UP;
        break;
      }

      if(player2.tail2.index > (maxIndex-cols))
        nextIndex=(cols-1)-(maxIndex-player2.tail2.index);
      else
        nextIndex=player2.tail2.index+cols;
      
      decToBin(bin, bitMap[nextIndex]);
      if(bin[player2.tail2.poSition] == 1)
      {
        player2.tail.index=nextIndex;
        player2.tail.poSition=player2.tail2.poSition;
        directionT=DOWN;
        break;
      }

      if((player2.tail2.index+(player2.tail2.poSition+1)/8) == (maxIndex+1))
        nextIndex=maxIndex-cols+1;
      else
        nextIndex=player2.tail2.index+(player2.tail2.poSition+1)/8;
      
      decToBin(bin, bitMap[nextIndex]);
      if(bin[(player2.tail2.poSition+1)%8] == 1)
      {
        player2.tail.index=nextIndex;
        player2.tail.poSition=(player2.tail2.poSition+1)%8;
        directionT=RIGHT;
        break;
      }

      if(player2.tail2.poSition == 0)
      {
        if(player2.tail2.index == 0)
          player2.tail.index=cols-1;
        else
          player2.tail.index-=1;
        
        player2.tail.poSition=7;
      }
      else
      {
        player2.tail.index=player2.tail2.index;
        player2.tail.poSition=player2.tail2.poSition-1;
      }
      directionT=LEFT;
      break;
    }
    
    if(directionT == UP)
    {
      if(player2.tail.index < cols)
        player2.tail2.index=maxIndex-(cols-1-player2.tail.index);
      else
        player2.tail2.index=player2.tail.index-cols;
      
      player2.tail2.poSition=player2.tail.poSition;
    }  
    
    else if(directionT == DOWN)
    {
      if(player2.tail.index > (maxIndex-cols))
        player2.tail2.index=maxIndex-(cols-1-player2.tail.index);
      else
        player2.tail2.index=player2.tail.index+cols;
      
      player2.tail2.poSition=player2.tail.poSition;
    }
    
    else if(directionT == RIGHT)
    {
      if((player2.tail.index+(player2.tail.poSition+1)/8) == (maxIndex+1))
      {
        player2.tail2.index=maxIndex-cols+1;
        player2.tail2.poSition=0;
      }
      else
      {
        player2.tail2.index=player2.tail.index+(player2.tail.poSition+1)/8;
        player2.tail2.poSition=(player2.tail.poSition+1) % 8;
      }
    }
    
    else
    {
      if(player2.tail.poSition == 0)
      {
        if(player2.tail.index == 0)
          player2.tail2.index=cols-1;
        else
          player2.tail2.index-=1;
          
        player2.tail2.poSition=7;
      }
      else
      {
        player2.tail2.index=player2.tail.index;
        player2.tail2.poSition=player2.tail.poSition-1;
      }
    }
  }
}

void decToBin(unsigned char * tab, unsigned char value)
{
  unsigned char temp1=value;
  char temp2;
  
  for(char i=8; i!=0; i--)
  {
    temp2=(temp1-expBaseTwo(i-1));
    if(temp2>0)
    {
      tab[i-1]=1;
      temp1=temp2;
    }
    else if(temp2<0)
      tab[i-1]=0;
    else
    {
      tab[i-1]=1;
      for(i=(i-1); i!=0; i--)
      {
        tab[i-1]=0;
      }
    break;
    }
  }
}

unsigned char binToDec(unsigned char * tab)
{
  unsigned char temp=0;
  for(char i=0; i!=8; i++)
    temp=temp+tab[i]*expBaseTwo(i);
  return temp;
}

unsigned char expBaseTwo(unsigned char exponent)
{
  unsigned char temp=1;
  for(unsigned char i=0; i<exponent; i++)
    temp*=2;
  return temp;
}
