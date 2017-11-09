//#include <string>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "Display.h"
#define mapX 0 // X-position (left position of the bitmap)
#define mapY 0 // Y-position (upper position of the bitmap)

//using namespace std;

U8G2_ST7920_128X64_2_SW_SPI game(U8G2_R2 /*rotate 180 degree*/, 13 /*clock*/, 11 /*data*/, 10 /*CS*/, 8 /*RST*/);
Display display1 = Display(6, 6, 1, 1, 15, 7, 55, 33);

void setup() {
  game.begin(U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);
  Serial.begin(9600);
}

void loop() {
  display1.setBody(1, RIGHT);
  display1.setBody(2, RIGHT);
  game.firstPage();
  do {
    game.drawXBM(mapX, mapY, mapW, mapH, display1.bitMap);
  } while (game.nextPage());
  delay(100);
}
