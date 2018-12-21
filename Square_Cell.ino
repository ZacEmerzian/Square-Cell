/*
GAME 235 Final Project
Goal: A puzzle game about a square with a face
by Zac Emerzian
11-26-18 to 12-14-18
Copyleft Zac Emerzian 2018
*/

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Classes.h";

#define WF_BUFFER 5
#define GRID_SIZE 8

PROGMEM const uint8_t titleBitMap[] = {
0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x1F, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xBF, 0xF8, 
0x20, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x10, 0x06, 0x00, 0xC8, 0x98, 0x03, 0x00, 0xE0, 0x08, 
0x20, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x10, 0x06, 0x00, 0xC8, 0x98, 0x03, 0x00, 0x60, 0x08, 
0x20, 0x00, 0x00, 0x00, 0x38, 0x40, 0x00, 0x10, 0x06, 0x00, 0xC8, 0x98, 0x03, 0x00, 0x60, 0x08, 
0x20, 0x00, 0x00, 0x01, 0xFC, 0x40, 0x00, 0x13, 0xFE, 0x7C, 0xC8, 0x99, 0xF3, 0x3E, 0x67, 0xF8, 
0x20, 0x00, 0x00, 0x07, 0x17, 0x40, 0x00, 0x13, 0xFE, 0x7C, 0xC8, 0x99, 0xF3, 0x3E, 0x67, 0xF8, 
0x20, 0x00, 0x00, 0x1C, 0x11, 0xC0, 0x00, 0x12, 0x02, 0x44, 0xC8, 0x99, 0x13, 0x22, 0x64, 0x00, 
0x20, 0x00, 0x00, 0x30, 0x18, 0x78, 0x00, 0x13, 0xFE, 0x44, 0xC8, 0x99, 0xF3, 0x3E, 0x67, 0xC0, 
0x20, 0x00, 0x00, 0xE0, 0x08, 0x0E, 0x00, 0x10, 0x06, 0x44, 0xC8, 0x98, 0x03, 0x00, 0x60, 0x40, 
0x20, 0x00, 0x03, 0x80, 0x08, 0x03, 0x00, 0x10, 0x06, 0x44, 0xC8, 0x98, 0x03, 0x00, 0xE0, 0x40, 
0x10, 0x00, 0x0E, 0x02, 0x08, 0x00, 0x80, 0x10, 0x06, 0x44, 0xC8, 0x98, 0x03, 0x00, 0x60, 0x40, 
0x10, 0x00, 0x18, 0x02, 0x08, 0x00, 0x80, 0x1F, 0xE6, 0x44, 0xC8, 0x99, 0xF3, 0x3E, 0x67, 0xC0, 
0x10, 0x00, 0x10, 0x02, 0x08, 0x00, 0x80, 0x1F, 0xE6, 0x5C, 0xC8, 0x99, 0xF3, 0x3E, 0x67, 0xC0, 
0x10, 0x00, 0x10, 0x02, 0x0C, 0x00, 0x80, 0x00, 0x26, 0x50, 0xC8, 0x99, 0x13, 0x22, 0x64, 0x00, 
0x10, 0x00, 0x11, 0x02, 0x04, 0x00, 0x80, 0x1F, 0xE6, 0x70, 0xCF, 0x99, 0x13, 0x22, 0x67, 0xF8, 
0x10, 0x00, 0x11, 0x02, 0x04, 0x00, 0x80, 0x10, 0x06, 0x00, 0xC0, 0x19, 0x13, 0x22, 0x60, 0x08, 
0x10, 0x00, 0x11, 0x00, 0x04, 0x00, 0x80, 0x10, 0x06, 0x00, 0xC0, 0x19, 0x13, 0x22, 0x60, 0x08, 
0x10, 0x00, 0x11, 0x00, 0x04, 0x00, 0x80, 0x10, 0x06, 0x00, 0xC0, 0x19, 0x13, 0x22, 0x60, 0x08, 
0x10, 0x00, 0x11, 0x00, 0x04, 0x00, 0x80, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xE3, 0xFF, 0xF8, 
0x10, 0x00, 0x11, 0x03, 0x04, 0x00, 0x80, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xE3, 0xFF, 0xF8, 
0x10, 0x00, 0x10, 0x04, 0x04, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x10, 0x00, 0x10, 0x08, 0x04, 0x00, 0x80, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xE0, 0x3C, 0x00, 
0x10, 0x00, 0x10, 0x10, 0x04, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x18, 0x03, 0x20, 0x24, 0x00, 
0x10, 0x00, 0x10, 0x60, 0x1E, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x18, 0x03, 0x20, 0x24, 0x00, 
0x10, 0x00, 0x10, 0x00, 0xF3, 0x81, 0x80, 0x00, 0x00, 0x00, 0x40, 0x18, 0x03, 0x20, 0x24, 0x00, 
0x10, 0x00, 0x18, 0x03, 0x80, 0xE1, 0x00, 0x00, 0x00, 0x00, 0x4F, 0x99, 0xFF, 0x20, 0x24, 0x00, 
0x10, 0x00, 0x08, 0x0E, 0x00, 0x39, 0x00, 0x00, 0x00, 0x00, 0x4F, 0x99, 0xFF, 0x20, 0x24, 0x00, 
0x30, 0x00, 0x08, 0x38, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x48, 0xF9, 0x01, 0x20, 0x24, 0x00, 
0x20, 0x00, 0x09, 0xE0, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x48, 0xF9, 0xF1, 0x20, 0x24, 0x00, 
0x78, 0x00, 0x0F, 0x80, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x48, 0x08, 0x11, 0x20, 0x24, 0x00, 
0x8F, 0x00, 0x00, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x08, 0x11, 0x20, 0x24, 0x00, 
0x01, 0xC0, 0x00, 0x1E, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x08, 0x11, 0x20, 0x24, 0x00, 
0x00, 0x30, 0x00, 0x01, 0xE1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x09, 0xF1, 0x20, 0x24, 0x00, 
0x00, 0x0E, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xF9, 0xF1, 0x20, 0x24, 0x00, 
0x00, 0x03, 0xC0, 0x00, 0x03, 0x00, 0x1D, 0xC9, 0xDC, 0x00, 0x48, 0x99, 0x01, 0x20, 0x24, 0x00, 
0x00, 0x00, 0x70, 0x00, 0x02, 0x00, 0x10, 0x95, 0x48, 0x00, 0x4F, 0x99, 0xFF, 0x3F, 0xE7, 0xF8, 
0x00, 0x00, 0x0F, 0x00, 0x06, 0x00, 0x1C, 0x9D, 0xC8, 0x00, 0x40, 0x18, 0x03, 0x00, 0x60, 0x08, 
0x00, 0x00, 0x01, 0xC0, 0x04, 0x00, 0x04, 0x95, 0x88, 0x00, 0x40, 0x18, 0x03, 0x00, 0x60, 0x08, 
0x00, 0x00, 0x00, 0x78, 0x04, 0x00, 0x1C, 0x95, 0x48, 0x00, 0x40, 0x18, 0x03, 0x00, 0x60, 0x08, 
0x00, 0x00, 0x00, 0x07, 0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 
0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 
0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0xE0, 0x00, 0x08, 0x93, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x0D, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x0A, 0xAA, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x08, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x08, 0x93, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0xD4, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x14, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x88, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x14, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x14, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

enum menuCursor {
  START,
  MODE,
  SFX
} titleCursor = START;


void drawScreen();


int wireFrameList[WF_BUFFER][5] = { };
Player player(wireFrameList); 
Switch button(11*GRID_SIZE - 4, 5*GRID_SIZE + 6, true, false, true, true);
Door exitDoor(10*GRID_SIZE, 2*GRID_SIZE - 5, false);

bool sounds = true;
bool dayMode = true;
bool bPressed = false;
uint8_t menuMoveTime = 0;
uint8_t menuMin = 1;
uint8_t menuMax = 5;
uint8_t menuCap = 6;
uint8_t cubeSide = 6;

void setup() {
  arduboy.begin();
  Serial.begin(9600);
  //arduboy.on();
  arduboy.setFrameRate(30);
  arduboy.clear();

  changeScreen();
  arduboy.display();

}

void loop() {
  // manage framerate
  if (!arduboy.nextFrame()) {
    return;
  }
  // update
  player.doUpdate( &arduboy );
  // render
  arduboy.clear(); // resets the screen
  arduboy.setCursor(0, 0);
  
  drawScreen();
  player.render(&arduboy);

  arduboy.invert(dayMode);
  Serial.write( arduboy.getBuffer(), 128 * 64 / 8 );
  arduboy.display(); // shows the world what happened
}


void changeScreen() {
  switch(currentScreen) {
    case TITLE:
      player.setPosition(WIDTH, HEIGHT); 
      break;
    case LVL1:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 3*GRID_SIZE;  wireFrameList[0][1] = 5*GRID_SIZE; wireFrameList[0][2] = 2*GRID_SIZE + 1; wireFrameList[0][3] = 2*GRID_SIZE + 1; wireFrameList[0][4] = 0;
      wireFrameList[1][0] = 9*GRID_SIZE;  wireFrameList[1][1] = 5*GRID_SIZE; wireFrameList[1][2] = 2*GRID_SIZE + 1; wireFrameList[1][3] = 2*GRID_SIZE + 1; wireFrameList[1][4] = 0;
      wireFrameList[2][0] = 0;            wireFrameList[2][1] = 0;           wireFrameList[2][2] = 0;               wireFrameList[2][3] = 0;               wireFrameList[2][4] = 0;
      wireFrameList[3][0] = 0;            wireFrameList[3][1] = 0;           wireFrameList[3][2] = 0;               wireFrameList[3][3] = 0;               wireFrameList[3][4] = 0;
      wireFrameList[4][0] = 0;            wireFrameList[4][1] = 0;           wireFrameList[4][2] = 0;               wireFrameList[4][3] = 0;               wireFrameList[4][4] = 0;
      player.setPosition(24, 46); 
      button = Switch(11*GRID_SIZE - 4, 5*GRID_SIZE + 6, true, false, true, true);
      exitDoor = Door(10*GRID_SIZE, 2*GRID_SIZE - 5, false);
      break;
    case LVL2:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 3*GRID_SIZE;  wireFrameList[0][1] = 5*GRID_SIZE; wireFrameList[0][2] = 2*GRID_SIZE + 1; wireFrameList[0][3] = 2*GRID_SIZE + 1; wireFrameList[0][4] = 0;
      wireFrameList[1][0] = 9*GRID_SIZE;  wireFrameList[1][1] = 5*GRID_SIZE; wireFrameList[1][2] = 2*GRID_SIZE + 1; wireFrameList[1][3] = 2*GRID_SIZE + 1; wireFrameList[1][4] = 0;
      wireFrameList[2][0] = 0;            wireFrameList[2][1] = 0;           wireFrameList[2][2] = 0;               wireFrameList[2][3] = 0;               wireFrameList[2][4] = 0;
      wireFrameList[3][0] = 0;            wireFrameList[3][1] = 0;           wireFrameList[3][2] = 0;               wireFrameList[3][3] = 0;               wireFrameList[3][4] = 0;
      player.setPosition(35, 46); 
      button = Switch(11*GRID_SIZE - 4, 5*GRID_SIZE + 6, true, true, true, true);
      exitDoor = Door(10*GRID_SIZE, 2*GRID_SIZE - 5, false);
      break;
    case LVL3:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 3*GRID_SIZE;  wireFrameList[0][1] = 5*GRID_SIZE; wireFrameList[0][2] = 2*GRID_SIZE + 1; wireFrameList[0][3] = 2*GRID_SIZE + 1; wireFrameList[0][4] = 0;
      wireFrameList[1][0] = 9*GRID_SIZE;  wireFrameList[1][1] = 5*GRID_SIZE; wireFrameList[1][2] = 2*GRID_SIZE + 1; wireFrameList[1][3] = 2*GRID_SIZE + 1; wireFrameList[1][4] = 0;
      wireFrameList[2][0] = 3*GRID_SIZE;  wireFrameList[2][1] = 2*GRID_SIZE; wireFrameList[2][2] = 2*GRID_SIZE + 1; wireFrameList[2][3] = 0;               wireFrameList[2][4] = 0;
      wireFrameList[3][0] = 0;            wireFrameList[3][1] = 0;           wireFrameList[3][2] = 0;               wireFrameList[3][3] = 0;               wireFrameList[3][4] = 0;
      player.setPosition(40, 46); 
      button = Switch(11*GRID_SIZE - 4, 5*GRID_SIZE + 6, true, true, true, true);
      exitDoor = Door(10*GRID_SIZE, 2*GRID_SIZE - 5, false);
      break;
    case LVL4:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 3*GRID_SIZE;  wireFrameList[0][1] = 3*GRID_SIZE; wireFrameList[0][2] = 2*GRID_SIZE + 1; wireFrameList[0][3] = 2*GRID_SIZE + 1; wireFrameList[0][4] = 0;
      wireFrameList[1][0] = 7*GRID_SIZE;  wireFrameList[1][1] = 3*GRID_SIZE; wireFrameList[1][2] = 2*GRID_SIZE + 1; wireFrameList[1][3] = 2*GRID_SIZE + 1; wireFrameList[1][4] = 1;
      wireFrameList[2][0] = 11*GRID_SIZE; wireFrameList[2][1] = 3*GRID_SIZE; wireFrameList[2][2] = 2*GRID_SIZE + 1; wireFrameList[2][3] = 2*GRID_SIZE + 1; wireFrameList[2][4] = 0;
      wireFrameList[3][0] = 0;            wireFrameList[3][1] = 0;           wireFrameList[3][2] = 0;               wireFrameList[3][3] = 0;               wireFrameList[3][4] = 0;
      player.setPosition(40, 30); 
      button = Switch(13*GRID_SIZE + 0, 3*GRID_SIZE + 6, true, false, true, true);
      exitDoor = Door(11*GRID_SIZE, 1*GRID_SIZE - 5, false);
      break;
    case LVL5:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 3*GRID_SIZE;  wireFrameList[0][1] = 4*GRID_SIZE; wireFrameList[0][2] = 2*GRID_SIZE + 1; wireFrameList[0][3] = 2*GRID_SIZE + 1; wireFrameList[0][4] = 0;
      wireFrameList[1][0] = 10*GRID_SIZE; wireFrameList[1][1] = 5*GRID_SIZE; wireFrameList[1][2] = 2*GRID_SIZE + 1; wireFrameList[1][3] = 1*GRID_SIZE + 1; wireFrameList[1][4] = 1;
      wireFrameList[2][0] = 11*GRID_SIZE; wireFrameList[2][1] = 4*GRID_SIZE; wireFrameList[2][2] = 1*GRID_SIZE + 1; wireFrameList[2][3] = 2*GRID_SIZE + 1; wireFrameList[2][4] = 1;
      wireFrameList[3][0] = 0;            wireFrameList[3][1] = 0;           wireFrameList[3][2] = 0;               wireFrameList[3][3] = 0;               wireFrameList[3][4] = 0;
      player.setPosition(35, 40); 
      button = Switch(12*GRID_SIZE + 0, 4*GRID_SIZE + 6, true, false, true, true);
      exitDoor = Door(10*GRID_SIZE, 1*GRID_SIZE - 5, false);
      break;
    case LVL6:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 1*GRID_SIZE;  wireFrameList[0][1] = 3*GRID_SIZE; wireFrameList[0][2] = 3*GRID_SIZE + 1; wireFrameList[0][3] = 3*GRID_SIZE + 1; wireFrameList[0][4] = 1;
      wireFrameList[1][0] = 6*GRID_SIZE;  wireFrameList[1][1] = 4*GRID_SIZE; wireFrameList[1][2] = 2*GRID_SIZE + 1; wireFrameList[1][3] = 2*GRID_SIZE + 1; wireFrameList[1][4] = 1;
      wireFrameList[2][0] = 7*GRID_SIZE;  wireFrameList[2][1] = 3*GRID_SIZE; wireFrameList[2][2] = 2*GRID_SIZE + 1; wireFrameList[2][3] = 2*GRID_SIZE + 1; wireFrameList[2][4] = 1;
      wireFrameList[3][0] = 11*GRID_SIZE; wireFrameList[3][1] = 3*GRID_SIZE; wireFrameList[3][2] = 2*GRID_SIZE + 1; wireFrameList[3][3] = 3*GRID_SIZE + 1; wireFrameList[3][4] = 0;
      player.setPosition(32, 30); 
      button = Switch(13*GRID_SIZE + 0, 3*GRID_SIZE + 6, false, true, true, true);
      exitDoor = Door(11*GRID_SIZE, 1*GRID_SIZE - 5, false); // 15, 5?
      break;
    case LVL7:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 1*GRID_SIZE; wireFrameList[0][1] = 2*GRID_SIZE; wireFrameList[0][2] = 2*GRID_SIZE + 1; wireFrameList[0][3] = 1*GRID_SIZE + 1; wireFrameList[0][4] = 1;
      wireFrameList[1][0] = 1*GRID_SIZE; wireFrameList[1][1] = 2*GRID_SIZE; wireFrameList[1][2] = 1*GRID_SIZE + 1; wireFrameList[1][3] = 2*GRID_SIZE + 1; wireFrameList[1][4] = 1;
      wireFrameList[2][0] = 7*GRID_SIZE; wireFrameList[2][1] = 3*GRID_SIZE; wireFrameList[2][2] = 2*GRID_SIZE + 1; wireFrameList[2][3] = 2*GRID_SIZE + 1; wireFrameList[2][4] = 0;
      wireFrameList[3][0] = 6*GRID_SIZE; wireFrameList[3][1] = 7*GRID_SIZE; wireFrameList[3][2] = 3*GRID_SIZE + 1; wireFrameList[3][3] = 0;               wireFrameList[3][4] = 0;
      player.setPosition(10, 11); 
      button = Switch(9*GRID_SIZE + 0, 3*GRID_SIZE + 6, false, true, true, true);
      exitDoor = Door(6*GRID_SIZE, 1*GRID_SIZE - 5, false);
      break;
    case LVL8:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 1*GRID_SIZE; wireFrameList[0][1] = 2*GRID_SIZE; wireFrameList[0][2] = 2*GRID_SIZE + 1; wireFrameList[0][3] = 1*GRID_SIZE + 1; wireFrameList[0][4] = 1;
      wireFrameList[1][0] = 1*GRID_SIZE; wireFrameList[1][1] = 2*GRID_SIZE; wireFrameList[1][2] = 1*GRID_SIZE + 1; wireFrameList[1][3] = 2*GRID_SIZE + 1; wireFrameList[1][4] = 1;
      wireFrameList[2][0] = 7*GRID_SIZE; wireFrameList[2][1] = 3*GRID_SIZE; wireFrameList[2][2] = 2*GRID_SIZE + 1; wireFrameList[2][3] = 2*GRID_SIZE + 1; wireFrameList[2][4] = 0;
      wireFrameList[3][0] = 6*GRID_SIZE; wireFrameList[3][1] = 7*GRID_SIZE; wireFrameList[3][2] = 3*GRID_SIZE + 1; wireFrameList[3][3] = 0;               wireFrameList[3][4] = 0;
      player.setPosition(10, 11); 
      button = Switch(9*GRID_SIZE - 4, 3*GRID_SIZE + 6, true, true, true, true);
      exitDoor = Door(13*GRID_SIZE, 2*GRID_SIZE - 2, false);
      break;
    case LVL9:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 2*GRID_SIZE;  wireFrameList[0][1] = 2*GRID_SIZE; wireFrameList[0][2] = 2*GRID_SIZE + 1; wireFrameList[0][3] = 3*GRID_SIZE + 1; wireFrameList[0][4] = 0;
      wireFrameList[1][0] = 9*GRID_SIZE;  wireFrameList[1][1] = 2*GRID_SIZE; wireFrameList[1][2] = 2*GRID_SIZE + 1; wireFrameList[1][3] = 2*GRID_SIZE + 1; wireFrameList[1][4] = 1;
      wireFrameList[2][0] = 10*GRID_SIZE; wireFrameList[2][1] = 3*GRID_SIZE; wireFrameList[2][2] = 2*GRID_SIZE + 1; wireFrameList[2][3] = 2*GRID_SIZE + 1; wireFrameList[2][4] = 1;
      wireFrameList[3][0] = 7*GRID_SIZE;  wireFrameList[3][1] = 3*GRID_SIZE; wireFrameList[3][2] = 0;               wireFrameList[3][3] = 2*GRID_SIZE + 1; wireFrameList[3][4] = 0;
      wireFrameList[4][0] = 14*GRID_SIZE; wireFrameList[4][1] = 2*GRID_SIZE; wireFrameList[4][2] = 0;               wireFrameList[4][3] = 1*GRID_SIZE + 1; wireFrameList[4][4] = 0;
      player.setPosition(20, 35); 
      button = Switch(14*GRID_SIZE, 2*GRID_SIZE + 1, false, true, true, true);
      exitDoor = Door(3*GRID_SIZE, 7*GRID_SIZE - 5, false);
      break;
    case CREDITS:
      //                    x Position                          y Position                         Width                                  Height                          Filled
      wireFrameList[0][0] = 1*GRID_SIZE;  wireFrameList[0][1] = 5*GRID_SIZE; wireFrameList[0][2] = 2*GRID_SIZE + 1; wireFrameList[0][3] = 2*GRID_SIZE + 1; wireFrameList[0][4] = 0;
      wireFrameList[1][0] = 13*GRID_SIZE; wireFrameList[1][1] = 5*GRID_SIZE; wireFrameList[1][2] = 2*GRID_SIZE + 1; wireFrameList[1][3] = 2*GRID_SIZE + 1; wireFrameList[1][4] = 0;
      wireFrameList[2][0] = 0;            wireFrameList[2][1] = 0;           wireFrameList[2][2] = 0;               wireFrameList[2][3] = 0;               wireFrameList[2][4] = 0;
      wireFrameList[3][0] = 0;            wireFrameList[3][1] = 0;           wireFrameList[3][2] = 0;               wireFrameList[3][3] = 0;               wireFrameList[3][4] = 0;
      wireFrameList[4][0] = 0;            wireFrameList[4][1] = 0;           wireFrameList[4][2] = 0;               wireFrameList[4][3] = 0;               wireFrameList[4][4] = 0;
      player.setPosition(99, 46); 
      button = Switch(3*GRID_SIZE, 5*GRID_SIZE + 6, false, false, true, true);
      exitDoor = Door(8*GRID_SIZE, 6*GRID_SIZE - 5, false);
      break;
    }
}

void drawScreen() {
  switch(currentScreen) {
    case TITLE:
      arduboy.drawSlowXYBitmap(0, 0, titleBitMap, WIDTH, HEIGHT, 1);
      uint8_t yOffSet;
      switch(titleCursor) {
        case START:
          if ( (arduboy.pressed(UP_BUTTON)) && (!arduboy.pressed(B_BUTTON)) ) {
            if ( (menuMoveTime < menuMin) || (menuMoveTime > menuMax) ) {
              titleCursor = SFX;
            }
            if (menuMoveTime < menuCap) {
              menuMoveTime++;
            }
          }
          else if ( (arduboy.pressed(DOWN_BUTTON)) && (!arduboy.pressed(B_BUTTON)) ) {
            if ( (menuMoveTime < menuMin) || (menuMoveTime > menuMax) ) {
              titleCursor = MODE;
            }
            if (menuMoveTime < menuCap) {
              menuMoveTime++;
            }
          }
          else if ( (arduboy.pressed(B_BUTTON)) && (!bPressed) ) {
            currentScreen = LVL1;
            changeScreen();
            bPressed = true;
            sound.tone(659, 60, 698, 60, 880, 80);
          }
          yOffSet = 0;
          
          break;
        case MODE:
          if ( (arduboy.pressed(UP_BUTTON)) && (!arduboy.pressed(B_BUTTON)) ) {
            if ( (menuMoveTime < menuMin) || (menuMoveTime > menuMax) ) {
              titleCursor = START;
            }
            if (menuMoveTime < menuCap) {
              menuMoveTime++;
            }
          }
          else if ( (arduboy.pressed(DOWN_BUTTON) ) && (!arduboy.pressed(B_BUTTON)) ) {
            if ( (menuMoveTime < menuMin) || (menuMoveTime > menuMax) ) {
              titleCursor = SFX;
            }
            if (menuMoveTime < menuCap) {
              menuMoveTime++;
            }
          }
          else if ( (arduboy.pressed(B_BUTTON)) && (!bPressed) ) {
            dayMode = !dayMode;
            bPressed = true;
            sound.tone(523, 60, 587, 80);
            
          }
          yOffSet = 8;
          break;
        case SFX:
          if ( (arduboy.pressed(UP_BUTTON)) && (!arduboy.pressed(B_BUTTON)) ) {
            if ( (menuMoveTime < menuMin) || (menuMoveTime > menuMax) ) {
              titleCursor = MODE;
            }
            if (menuMoveTime < menuCap) {
              menuMoveTime++;
            }
          }
          else if ( (arduboy.pressed(DOWN_BUTTON)) && (!arduboy.pressed(B_BUTTON)) ) {
            if ( (menuMoveTime < menuMin) || (menuMoveTime > menuMax) ) {
              titleCursor = START;
            }
            if (menuMoveTime < menuCap) {
              menuMoveTime++;
            }
          }
          else if ( (arduboy.pressed(B_BUTTON)) && (!bPressed) ) {
            sounds = !sounds;
            sounds ? (arduboy.audio.on()) : (arduboy.audio.off());
            bPressed = true;
          }
          yOffSet = 16;
          break;
      }

      if ( (bPressed) && (!arduboy.pressed(B_BUTTON)) ) { // when released
        bPressed = false;
      }
      if ( (!arduboy.pressed(UP_BUTTON)) && (!arduboy.pressed(DOWN_BUTTON)) ) {
        menuMoveTime = 0;
      }
      
      // Left Cursor
      arduboy.fillTriangle(46, 38 + yOffSet, 44, 40 + yOffSet, 48, 40 + yOffSet, 1);
      arduboy.fillTriangle(46, 42 + yOffSet, 44, 40 + yOffSet, 48, 40 + yOffSet, 1);
      arduboy.drawLine(45, 40 + yOffSet, 46, 39 + yOffSet, 0);
      // Right Cursor
      arduboy.fillTriangle(74, 38 + yOffSet, 72, 40 + yOffSet, 76, 40 + yOffSet, 1);
      arduboy.fillTriangle(74, 42 + yOffSet, 72, 40 + yOffSet, 76, 40 + yOffSet, 1);
      arduboy.drawLine(73, 40 + yOffSet, 74, 39 + yOffSet, 0);
      // Sound Icon
      if (sounds) {
        arduboy.drawPixel(67, 56, 1);
        arduboy.drawLine(69, 55, 69, 57, 1);
      }
      else {
        arduboy.drawLine(67, 55, 69, 57, 1);
        arduboy.drawLine(69, 55, 67, 57, 1);
      }
      break;
    case LVL1:
      drawWireFrames();
      arduboy.setCursor(111, 56); 
      arduboy.println("Lv1");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    case LVL2:
      drawWireFrames();
      arduboy.setCursor(110, 56); 
      arduboy.println("Lv2");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    case LVL3:
      drawWireFrames();
      arduboy.setCursor(110, 56); 
      arduboy.println("Lv3");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    case LVL4:
      drawWireFrames();
      arduboy.setCursor(110, 56); 
      arduboy.println("Lv4");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    case LVL5:
      drawWireFrames();
      arduboy.setCursor(110, 56); 
      arduboy.println("Lv5");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    case LVL6:
      drawWireFrames();
      arduboy.setCursor(110, 56); 
      arduboy.println("Lv6");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    case LVL7:
      drawWireFrames();
      arduboy.setCursor(110, 56); 
      arduboy.println("Lv7");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    case LVL8:
      drawWireFrames();
      arduboy.setCursor(110, 56); 
      arduboy.println("Lv8");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    case LVL9:
      drawWireFrames();
      arduboy.setCursor(110, 56); 
      arduboy.println("Lv9");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    case CREDITS:
      drawWireFrames();
      arduboy.setCursor(9, 2); 
      arduboy.println("Thanks for Playing!");
      arduboy.setCursor(35, 12); 
      arduboy.println("Created by");
      arduboy.setCursor(29, 22); 
      arduboy.println("Zac Emerzian");
      button.render(&arduboy);
      exitDoor.render(&arduboy);
      break;
    }
}

void drawWireFrames() {
  for (int i = 0; i < WF_BUFFER; i++) {
    uint8_t WFX;
    uint8_t WFY;
    uint8_t WFW;
    uint8_t WFH;
    uint8_t WFF;
    for(int j = 0; j < 5; j++) {
      switch (j) {
        case 0:
          WFX = wireFrameList[i][j];
          break;
        case 1:
          WFY = wireFrameList[i][j];
          break;
        case 2:
          WFW = wireFrameList[i][j];
          break;
        case 3:
          WFH = wireFrameList[i][j];
          break;
        case 4:
          WFF = wireFrameList[i][j];
          break;
      }
    }
    if (WFW == 0) { // Horizontal Line
      arduboy.drawLine(WFX, WFY, WFX, WFY + WFH - 1, 1);
    }
    else if (WFH == 0) { // Vertical Line
      arduboy.drawLine(WFX, WFY, WFX + WFW - 1, WFY, 1);
    }
    else { // Rectangle
      if (WFF == 0) {
        arduboy.drawRect(WFX, WFY, WFW, WFH, 1);
      }
      else {
        arduboy.fillRect(WFX, WFY, WFW, WFH, 1);
      }
      
    }
  }
}
