#include <Arduboy2.h>
#include <ArduboyTones.h>
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
#define WF_BUFFER 5
#define GRID_SIZE 8

enum screen {
  TITLE,
  LVL1, LVL2, LVL3,
  LVL4, LVL5, LVL6,
  LVL7, LVL8, LVL9,
  CREDITS
} currentScreen = TITLE; 

void changeScreen();

class Door {
  public:
  uint8_t xPos;
  uint8_t yPos;
  uint8_t hei;
  uint8_t wid;
  bool active;
  Door (uint8_t tempX, uint8_t tempY, bool tempActive) {
    xPos = tempX;
    yPos = tempY;
    wid = 7;
    hei = 9;
    active = tempActive;
  }

  void render(Arduboy2 *myArduboy) {
    if (active) {
      myArduboy->drawRect(xPos, yPos, wid, hei, 1);
      myArduboy->drawPixel(xPos + 2, yPos + 4, 1);
    }
  }
  
}
;
extern Door exitDoor;


class Switch {
  public:
  uint8_t xPos;
  uint8_t yPos;
  bool above;
  bool onWall;
  bool canFlip;
  uint8_t hei;
  uint8_t wid;
  bool active;
  
  Switch (uint8_t tempX, uint8_t tempY, bool tempAbove, bool tempCanFlip, bool tempOnWall, bool tempActive) {
    xPos = tempX;
    yPos = tempY;
    above = tempAbove;
    onWall = tempOnWall;
    canFlip = tempCanFlip;
    hei = 6 - (!onWall);
    wid = 6 - (onWall);
    active = tempActive;
  }

  void doUpdate(Arduboy2 *myArduboy) {
    
  }

  void render(Arduboy2 *myArduboy) {
    if (active){
      if (canFlip) {
        myArduboy->drawRoundRect(xPos, yPos, wid, hei, 1, 1);
      }
      else {
        myArduboy->fillRoundRect(xPos, yPos, wid, hei, 1, 1);
      }
    }
  }

  void flip() {
    if (canFlip) {
      if (onWall) { // horizontal flip
        if (above) { // right to left
          xPos += wid - 1;
        }
        else { // left to right
          xPos -= wid - 1;
        }
      }
      else { // vertical flip
        if (above) { // up to down
          yPos += hei - 1;
        }
        else { // down to up
          yPos -= hei - 1;
        }
      }
      above = !above;
    }
  }

  void hit(){
    active = false;
    exitDoor.active = true;
    sound.tone(523, 60, 587, 80);
  }

}
;
extern Switch button;



class Player {
  uint8_t xPos;
  uint8_t yPos;
  bool upAccess;
  bool downAccess;
  bool leftAccess;
  bool rightAccess;
  bool above;
  bool aPressed;
  bool canFlip;
  uint8_t side;
  int wfListStart;

  enum direct {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
  } launchDirection = NONE;
  
  enum condition {
    GROUNDED,
    FLYING
  } playerState = GROUNDED;

  public:
  Player( int temp[][5] ) {
    xPos = 0; // 64
    yPos = 0; // 58
    upAccess = false;
    downAccess = false;
    leftAccess = false;
    rightAccess = false;
    above = false;
    aPressed = false;
    canFlip = true;
    side = 6;
    wfListStart = temp;
  }

  void doUpdate(Arduboy2 *myArduboy) {
    switch(playerState) {
      case GROUNDED:
        updateGrounded(myArduboy);
        break;
      case FLYING:
        updateFlying();
        break;
    }
  }
    
  void updateGrounded(Arduboy2 *inputArduboy) {
    //  *^* COLLECT INPUT *^*
    // Movement
    if ( (inputArduboy->pressed(UP_BUTTON)) && (yPos > 0) && (upAccess) ) {
      yPos --;
    }
    else if ( (inputArduboy->pressed(DOWN_BUTTON)) && (yPos < HEIGHT - side) && (downAccess) ) {
      yPos ++;
    }
    else if ( (inputArduboy->pressed(LEFT_BUTTON)) && (xPos > 0) && (leftAccess) ) {
      xPos --;
    }
    else if ( (inputArduboy->pressed(RIGHT_BUTTON)) && (xPos < WIDTH - side) && (rightAccess) ) {
      xPos ++;
    }

    // Flipping
    else if ( (inputArduboy->pressed(A_BUTTON)) && (!aPressed) && (canFlip) ) {
      if ( upAccess + downAccess != leftAccess + rightAccess ) { // if not in a corner
        // Vertical
        if (leftAccess || rightAccess) {
          // Up to down
          if (above) {
            yPos += side - 1;
            button.flip();
          }
          // Down to up
          else {
            yPos -= side - 1;
            button.flip();
          }
        }
        // Horizontal
        if (upAccess || downAccess) {
          // Left to right
          if (above) {
            xPos += side - 1;
            button.flip();
          }
          // Right to left
          else {
            xPos -= side - 1;
            button.flip();
          }
        }
      }
      else { // If in a corner
        if (upAccess && leftAccess) {
          if (inputArduboy->pressed(DOWN_BUTTON)) {
            yPos += side - 1;
            button.flip();
          }
          else if (inputArduboy->pressed(RIGHT_BUTTON)) {
            xPos += side - 1;
            button.flip();
          }
        }
        if (upAccess && rightAccess) {
          if (inputArduboy->pressed(DOWN_BUTTON)) {
            yPos += side - 1;
            button.flip();
          }
          else if (inputArduboy->pressed(LEFT_BUTTON)) {
            xPos -= side - 1;
            button.flip();
          }
        }
        if (downAccess && rightAccess) {
          if (inputArduboy->pressed(UP_BUTTON)) {
            yPos -= side - 1;
            button.flip();
          }
          else if (inputArduboy->pressed(LEFT_BUTTON)) {
            xPos -= side - 1;
            button.flip();
          }
        }
        if (downAccess && leftAccess) {
          if (inputArduboy->pressed(UP_BUTTON)) {
            yPos -= side - 1;
            button.flip();
          }
          else if (inputArduboy->pressed(RIGHT_BUTTON)) {
            xPos += side - 1;
            button.flip();
          }
        }
      }
      aPressed = true;
    }

    // Launching
    if ( inputArduboy->pressed(B_BUTTON) ) {
      if ( upAccess + downAccess != leftAccess + rightAccess ) { // if not in a corner
        playerState = FLYING;
        if (leftAccess || rightAccess) {
          // Launch Up
          if (above) {
            launchDirection = UP;
          }
          // Launch Down
          else {
            launchDirection = DOWN;
          }
        }
        // Horizontal
        if (upAccess || downAccess) {
          // Launch Left
          if (above) {
            launchDirection = LEFT;
          }
          // Launch Right
          else {
            launchDirection = RIGHT;
          }
        }
      }
    }
    
    // Flip Reset
    if ( (aPressed) && (!inputArduboy->pressed(A_BUTTON)) ) { // when released
      aPressed = false;
    }
    // Collisions
    findAccess(wfListStart);
  }
    

  void updateFlying() {
    // Flying
    if (launchDirection == UP) {
      yPos --;
    }
    else if (launchDirection == DOWN) {
      yPos ++;
    }
    else if (launchDirection == LEFT) {
      xPos --;
    }
    else if (launchDirection == RIGHT) {
      xPos ++;
    }

    // Screen Wrapping
    // Right
    if ( (xPos + side > WIDTH) && (xPos < 255 - 10) ) {
      xPos = 0;
    }
    // Left
    else if (xPos > 255 - 10) {
      xPos = WIDTH - side;
    }
    // Down
    if ( (yPos + side > HEIGHT) && (yPos < 255 - 10) ) {
      yPos = 0;
    }
    // Up
    else if (yPos > 255 - 10) {
      yPos = HEIGHT - side;
    }

    // Collisions
    findAccess(wfListStart);
    

    // Landing
    if ( upAccess || downAccess || leftAccess || rightAccess ) {
      playerState = GROUNDED;
    }

    // Hit the button
    if ( (button.active) && (xPos + side/2 >= button.xPos) && (xPos + side/2 <= button.xPos + button.wid)
                         && (yPos + side/2 >= button.yPos) && (yPos + side/2 <= button.yPos + button.hei) ) {
      //button.active = false;
      button.hit();
    }

    // Go through the Exit Door
    exitScreen();
    
  }

  void render(Arduboy2 *myArduboy) {
      myArduboy->drawPixel(0, 0, 0);

      myArduboy->drawRect(xPos, yPos, side, side, 1);
      myArduboy->drawPixel(xPos + 2, yPos + 1, 1); // Left eye
      myArduboy->drawPixel(xPos + 2, yPos + 2, 1);
      myArduboy->drawPixel(xPos + 4, yPos + 1, 1); // Right eye
      myArduboy->drawPixel(xPos + 4, yPos + 2, 1);
      myArduboy->drawPixel(xPos + 2, yPos + 4, 1); // Mouth
      myArduboy->drawPixel(xPos + 3, yPos + 4, 1);
  }


  void findAccess(int blocks[][5]) {
    bool uFlag = false;
    bool dFlag = false;
    bool lFlag = false;
    bool rFlag = false;
    bool aboveFlag = false;
    for (int i = 0; i < WF_BUFFER; i++) {
      // Squares
      if ( (blocks[i][2] != 0) && (blocks[i][3] != 0) ) {
        // Horizontal
        if ( (yPos + side == blocks[i][1]+1)              || (yPos == blocks[i][1]) || 
             (yPos + side == blocks[i][1] + blocks[i][3]) || (yPos == blocks[i][1] + blocks[i][3] - 1) ) { 
          // Right
          if ( (xPos + side - 1 >= blocks[i][0]) && (xPos + side < blocks[i][0] + blocks[i][2]) ) { // dangling left
            rFlag = true;
            canFlip = filledCheck(blocks[i][4]);
            for (int j = 0; j < WF_BUFFER; j++) {
              if ( (xPos + side == blocks[j][0]+1) && (yPos >= blocks[j][1]) && (yPos + side <= blocks[j][1] + blocks[j][3]) ) {
                rFlag = false;
              }
            }
          }
          // Left
          if ( (xPos < blocks[i][0] + blocks[i][2]) && (xPos > blocks[i][0]) ) { // dangling right
            lFlag = true;
            canFlip = filledCheck(blocks[i][4]);
            for (int j = 0; j < WF_BUFFER; j++) {
              if ( (xPos == blocks[j][0] + blocks[j][2] - 1) && (yPos >= blocks[j][1]) && (yPos + side <= blocks[j][1] + blocks[j][3]) ) {
                lFlag = false;
              }
            }
          }
        }
        // Vertical
        if ( (xPos + side == blocks[i][0]+1)              || (xPos == blocks[i][0]) || 
             (xPos + side == blocks[i][0] + blocks[i][2]) || (xPos == blocks[i][0] + blocks[i][2] - 1) ) { 
          // Up
          if ( (yPos < blocks[i][1] + blocks[i][3]) && (yPos > blocks[i][1]) ) { // dangling below
            uFlag = true;
            canFlip = filledCheck(blocks[i][4]);
            for (int j = 0; j < WF_BUFFER; j++) {
              if ( (yPos == blocks[j][1] + blocks[j][3] - 1) && (xPos >= blocks[j][0]) && (xPos + side <= blocks[j][0] + blocks[j][2]) ) {
                uFlag = false;
              }
            }
          }
          // Down
          if ( (yPos + side - 1 >= blocks[i][1]) && (yPos + side < blocks[i][1] + blocks[i][3]) ) { // dangling above
            dFlag = true;
            canFlip = filledCheck(blocks[i][4]);
            for (int j = 0; j < WF_BUFFER; j++) {
              if ( (yPos + side == blocks[j][1]+1) && (xPos >= blocks[j][0]) && (xPos + side <= blocks[j][0] + blocks[j][2])) {
                dFlag = false;
              }
            }
          }
        }
        
        // Flip Checker
        if ( ( ( (yPos + side == blocks[i][1]+1) || (yPos + side == blocks[i][1] + blocks[i][3]) ) && (xPos + side - 1 >= blocks[i][0]) && (xPos < blocks[i][0] + blocks[i][2] - 1) ) || 
             ( ( (xPos + side == blocks[i][0]+1) || (xPos + side == blocks[i][0] + blocks[i][2]) ) && (yPos + side - 1 >= blocks[i][1]) && (yPos < blocks[i][1] + blocks[i][3] - 1) ) ) {
          aboveFlag = true;
        }
      }
      // Vertical Lines
      else if (blocks[i][2] == 0) { 
        if ( (xPos + side == blocks[i][0]+1) || (xPos == blocks[i][0]) ) { 
          // Up
          if ( (yPos - 1 >= blocks[i][1]) && (yPos + side <= blocks[i][1] + blocks[i][3]) ) {
            uFlag = true;
            canFlip = filledCheck(blocks[i][4]);
          }
          // Down
          if ( (yPos + side + 1 <= blocks[i][1] + blocks[i][3]) && (yPos >= blocks[i][1]) ) {
            dFlag = true;
            canFlip = filledCheck(blocks[i][4]);
          }
        }
        // Flip Checker
        if ( xPos + side == blocks[i][0]+1 ) {
          aboveFlag = true;
        }
      }
      // Horizontal Lines
      else if (blocks[i][3] == 0) { // Horizontal Line
        if ( (yPos + side == blocks[i][1]+1) || (yPos == blocks[i][1]) ) { 
          // Right
          if ( (xPos + side + 1 <= blocks[i][0] + blocks[i][2]) && (xPos >= blocks[i][0]) ) {
            rFlag = true;
            canFlip = filledCheck(blocks[i][4]);
          }
          // Left
          if ( (xPos - 1 >= blocks[i][0]) && (xPos + side <= blocks[i][0] + blocks[i][2]) ) {
            lFlag = true;
            canFlip = filledCheck(blocks[i][4]);
          }
        }
        // Flip Checker
        if ( yPos + side == blocks[i][1]+1 ) {
          aboveFlag = true;
        }
      }
    }

    // Collision Results
    upAccess = uFlag;
    downAccess = dFlag;
    leftAccess = lFlag;
    rightAccess = rFlag;
    above = aboveFlag;
  }

  bool filledCheck(uint8_t filled) {
    if (filled == 1) {
      return false;
    }
    else {
      return true;
    }
  }

  void setPosition(uint8_t tempX, uint8_t tempY) {
    xPos = tempX;
    yPos = tempY;
  }

  void exitScreen() {
    if ( (xPos + side/2 >= exitDoor.xPos) && (xPos + side/2 <= exitDoor.xPos + exitDoor.wid) &&
         (yPos + side/2 >= exitDoor.yPos) && (yPos + side/2 <= exitDoor.yPos + exitDoor.hei) && (exitDoor.active) ) {
      exitDoor.active = false;
      playerState = GROUNDED;
      sound.tone(659, 60, 698, 60, 880, 80);
      switch(currentScreen) {
        case LVL1:
          currentScreen = LVL2;
          break;
        case LVL2:
          currentScreen = LVL3;
          break;
        case LVL3:
          currentScreen = LVL4;
          break;
        case LVL4:
          currentScreen = LVL5;
          break;
        case LVL5:
          currentScreen = LVL6;
          break;
        case LVL6:
          currentScreen = LVL7;
          break;
        case LVL7:
          currentScreen = LVL8;
          break;
        case LVL8:
          currentScreen = LVL9;
          break;
        case LVL9:
          currentScreen = CREDITS;
          break;
        case CREDITS:
          currentScreen = TITLE;
          break;
      }
      changeScreen();
    }
  }
  
}
;
