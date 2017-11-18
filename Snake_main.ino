//#include <string>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "Display.h"
#include "TimerOne.h"
#define mapX 0 // X-position (left position of the bitmap)
#define mapY 0 // Y-position (upper position of the bitmap)

//using namespace std;

U8G2_ST7920_128X64_2_SW_SPI game(U8G2_R2 /*rotate 180 degree*/, 13 /*clock*/, 11 /*data*/, 10 /*CS*/, 8 /*RST*/);
Display display1 = Display(8, 8, 1, 1, 25, 100, 55, 33);
unsigned char d=0;
DIRECTIONS directionH = UP;

void setup() {
  game.begin(U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);
  randomSeed(analogRead(0));
  Timer1.initialize(5000000);
  Timer1.attachInterrupt(timerISR);
  pinMode(4, INPUT);  // set pin to input
  //digitalWrite(4, HIGH);  // turn on pullup resistors
}

void timerISR()
{
  display1.setBody(display1.player1, directionH);
  display1.setBody(display1.player1, directionH);
  display1.setBody(display1.player2, directionH);
  display1.setBody(display1.player2, directionH);
  game.firstPage();
  do {
    game.drawXBM(mapX, mapY, mapW, mapH, display1.bitMap);
  } while (game.nextPage());
  directionH = RIGHT;
}

void loop() {
  //if(digitalRead(4) == HIGH)
    directionH = UP;
}
