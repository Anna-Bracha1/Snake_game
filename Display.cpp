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

void Display::setBody(Snake & player, DIRECTIONS directionH)
{
  unsigned char bin[8]; // table to store binary notation of the currently processed byte
  unsigned char bin2[8]; // table to store binary notation of the currently processed byte
  
  player.setHead(directionH);
  unsigned char bin3[8];
  int index=((player.head.y*cols)+(player.head.x/8)); // index in the XBM bitmap
  unsigned char poSition=player.head.x % 8;
  decToBin(bin3, bitMap[index]);
  if(bin3[poSition] == 1)
    {
      player.lengthUp(2);
      setPixel(player.head2);
      return;
    }
  setPixel(player.head);
  setPixel(player.head2);
  
  clearPixel(player.tail);
  clearPixel(player.tail2);

  int nextIndex;
  int nextIndex2;

  //next tail - direction UP
  if(player.tail2.index < cols)
  {
    nextIndex=maxIndex-(cols-1-player.tail2.index);
    nextIndex2=nextIndex-cols;
  }
  else if(player.tail2.index < 2*cols)
  {
    nextIndex=player.tail2.index-cols;
    nextIndex2=maxIndex-(cols-1-nextIndex);
  }
  else
  {
    nextIndex=player.tail2.index-cols;
    nextIndex2=nextIndex-cols;
  }

  decToBin(bin, bitMap[nextIndex]);
  decToBin(bin2, bitMap[nextIndex2]);
  while(1)
  {
    if((bin[player.tail2.poSition] == 1) && (bin2[player.tail2.poSition] == 1))
    {
      player.tail.index=nextIndex;
      player.tail2.index=nextIndex2;
      player.tail.poSition=player.tail2.poSition;
      break;
    }

    //next tail - direction DOWN
    if(player.tail2.index > (maxIndex-cols))
    {
      nextIndex=(cols-1)-(maxIndex-player.tail2.index);
      nextIndex2=nextIndex+cols;
    }
    else if(player.tail2.index > (maxIndex-2*cols))
    {
      nextIndex=player.tail2.index+cols;
      nextIndex2=(cols-1)-(maxIndex-nextIndex);
    }
    else
    {
      nextIndex=player.tail2.index+cols;
      nextIndex2=nextIndex+cols;
    }
    
    decToBin(bin, bitMap[nextIndex]);
    decToBin(bin2, bitMap[nextIndex2]);
    if((bin[player.tail2.poSition] == 1) && (bin2[player.tail2.poSition] == 1))
    {
      player.tail.index=nextIndex;
      player.tail2.index=nextIndex2;
      player.tail.poSition=player.tail2.poSition;
      break;
    }

    //next tail - direction RIGHT
    if((((player.tail2.index+(player.tail2.poSition+1)/8) % cols) == 0) && ((player.tail2.index+(player.tail2.poSition+1)/8) != player.tail2.index))
    {
      nextIndex=player.tail2.index-(cols-1);
      nextIndex2=nextIndex;
    }
    else if((((player.tail2.index+(player.tail2.poSition+2)/8) % cols) == 0) && ((player.tail2.index+(player.tail2.poSition+2)/8) != player.tail2.index))
    {
      nextIndex=player.tail2.index;
      nextIndex2=player.tail2.index-(cols-1);
    }
    else
    {
      nextIndex=player.tail2.index+(player.tail2.poSition+1)/8;
      nextIndex2=player.tail2.index+(player.tail2.poSition+2)/8;
    }
    
    decToBin(bin, bitMap[nextIndex]);
    decToBin(bin2, bitMap[nextIndex2]);
    if((bin[(player.tail2.poSition+1) % 8] == 1) && (bin2[(player.tail2.poSition+2) % 8] == 1))
    {
      player.tail.index=nextIndex;
      player.tail2.index=nextIndex2;
      player.tail.poSition=(player.tail2.poSition+1) % 8;
      player.tail2.poSition=(player.tail2.poSition+2) % 8;
      break;
    }

    //next tail - direction LEFT
    if(player.tail2.poSition == 0)
    {
      if((player.tail2.index % cols) == 0)
        player.tail.index=player.tail2.index+(cols-1);
      else
        player.tail.index=player.tail2.index-1;

      player.tail2.index=player.tail.index;
      player.tail.poSition=7;
      player.tail2.poSition=6;
    }
    else if(player.tail2.poSition == 1)
    {
      player.tail.index=player.tail2.index;
      if((player.tail2.index % cols) == 0)
        player.tail2.index=player.tail2.index+(cols-1);
      else
        player.tail2.index-=1;

      player.tail.poSition=0;
      player.tail2.poSition=7;
    }
    else
    {
      player.tail.index=player.tail2.index;
      player.tail.poSition=player.tail2.poSition-1;
      player.tail2.poSition-=2;
    }
    break;
  }
}

void Display::setFood()
{
  XY coordinates;
  coordinates.x = random(0, maximumX);
  coordinates.y = random(0, maximumY);
  setPixel(coordinates);
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
