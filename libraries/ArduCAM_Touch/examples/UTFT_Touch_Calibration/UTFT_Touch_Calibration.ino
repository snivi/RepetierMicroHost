// UTFT_Touch_Calibration (C)2012 uCtronics
// web: http://www.uctronics.com
// UTFT_Touch_Calibration is derived from 
// ITDB02_Touch_Calibration (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
// to fit for our 3.2 inch TFT LCD shield for Arduino/Maple/Chipkit
// This program can be used to calibrate the touchscreen
// of the 3.2 inch TFT LCD shield.
//
// This program requires the UTFT library (8bit mode)
// and the code is compatible with both UNO and Mega board.
// No code modification required.
//
// Instructions will be given on the display.
//


#include <UTFT.h>
#include <ArduCAM_Touch.h>
#include <SD.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// 
//UTFT(byte model, int RS, int WR,int CS,int RD)
UTFT myGLCD(ITDB32S,A1,A2,A0,A3);
//myTouch(TCS,IRQ);
ArduCAM_Touch  myTouch(10,9);



int cx, cy;
int rx[10], ry[10];
float px, py;
int ox, oy;

void setup()
{
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_LOW);
}

void drawCrossHair(int x, int y)
{
  myGLCD.drawRect(x-10, y-10, x+10, y+10);
  myGLCD.drawLine(x-5, y, x+5, y);
  myGLCD.drawLine(x, y-5, x, y+5);
}

void readCoordinates()
{
  int iter = 2000;
  int cnt = 0;
  unsigned long tx=0;
  unsigned long ty=0;
  boolean OK = false;
  
  while (OK == false)
  {
    while (myTouch.dataAvailable() == false) {}
    while ((myTouch.dataAvailable() == true) && (cnt<iter))
    {
      myTouch.read();
      tx += myTouch.TP_X;
      ty += myTouch.TP_Y;
      cnt++;
    }
    if (cnt>=iter)
    {
      OK = true;
    }
    else
    {
      tx = 0;
      ty = 0;
      cnt = 0;
    }
  }

  cx = tx / iter;
  cy = ty / iter;

}

void calibrate(int x, int y, int i)
{
  myGLCD.setColor(255, 255, 255);
  drawCrossHair(x,y);
  readCoordinates();
  myGLCD.setColor(80, 80, 80);
  drawCrossHair(x,y);
  
  rx[i]=cx;
  ry[i]=cy;
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
  }
}

void waitForTouch()
{
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
  }
  while (myTouch.dataAvailable() == false) {}
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
  }
}

void startup()
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 239, 13);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.drawLine(0, 14, 239, 14);
  myGLCD.print("ITDB02 TOUCH CALIBRATION", CENTER, 1);
  myGLCD.setBackColor(0, 0, 0);
  
  myGLCD.print("INSTRUCTIONS", CENTER, 30);
  myGLCD.print("Use a stylus or something", LEFT, 50);
  myGLCD.print("similar to touch as close to", LEFT, 62);
  myGLCD.print("the center of the highlighted", LEFT, 74);
  myGLCD.print("crosshair as possible. Keep as", LEFT, 86);
  myGLCD.print("still as possible and keep", LEFT, 98);
  myGLCD.print("holding until the highlight is", LEFT, 110);
  myGLCD.print("removed. Repeat for all", LEFT, 122);
  myGLCD.print("crosshairs in sequence.", LEFT, 134);
  myGLCD.print("Further instructions will be", LEFT, 158);
  myGLCD.print("displayed when the calibration", LEFT, 170);
  myGLCD.print("is complete.", LEFT, 182);
  myGLCD.print("Do NOT use your finger as a", LEFT, 206);
  myGLCD.print("calibration stylus or the", LEFT, 218);
  myGLCD.print("result WILL BE very imprecise.", LEFT, 230);
  myGLCD.print("Touch screen to continue", CENTER, 305);

  waitForTouch();
  myGLCD.clrScr();
}

void done()
{
  myGLCD.clrScr();
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, 239, 13);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.drawLine(0, 14, 239, 14);
  myGLCD.print("ITDB02 TOUCH CALIBRATION", CENTER, 1);
  myGLCD.setBackColor(0, 0, 0);
  
  myGLCD.print("CALIBRATION COMPLETE", CENTER, 30);
  myGLCD.print("To use the new calibration", LEFT, 50);
  myGLCD.print("settings you must edit the", LEFT, 62);
  myGLCD.setColor(160, 160, 255);
  myGLCD.print("ITDB02_Touch.cpp", LEFT, 74);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("file and", 136, 74);
  myGLCD.print("change the following values.", LEFT, 86);
  myGLCD.print("The values are located right", LEFT, 98);
  myGLCD.print("below the opening comment in", LEFT, 110);
  myGLCD.print("the file.", LEFT, 122);
  myGLCD.print("PixSizeX", LEFT, 158);
  myGLCD.print("PixOffsX", LEFT, 170);
  myGLCD.print("PixSizeY", LEFT, 182);
  myGLCD.print("PixOffsY", LEFT, 194);
  myGLCD.print("Connected module:", LEFT, 250);
  myGLCD.drawLine(0, 155, 239, 155);
  myGLCD.drawLine(0, 209, 239, 209);

  myGLCD.printNumF(px, 2, 100, 158);
  myGLCD.printNumI(ox, 100, 170);
  myGLCD.printNumF(py, 2, 100, 182);
  myGLCD.printNumI(oy, 100, 194);
  if (px>=0)
    myGLCD.print("2.4\"", 144, 250);
  else
  {
    if (py>=0)
    {
      myGLCD.print("3.2\"", 144, 250);
      myGLCD.print("Negative numbers for PixSizeX", LEFT, 270);
      myGLCD.print("is expected :)", LEFT, 282);
    }
    else
    {
      myGLCD.print("3.2\" Wide", 144, 250);
      myGLCD.print("Negative numbers for PixSizeX", LEFT, 270);
      myGLCD.print("and PixSizeY are expected :)", LEFT, 282);
    }
  }
}

void loop()
{
  startup();
  
  myGLCD.setColor(80, 80, 80);
  drawCrossHair(10,10);
  drawCrossHair(10,160);
  drawCrossHair(10,309);
  drawCrossHair(120,10);
  drawCrossHair(120,160);
  drawCrossHair(120,309);
  drawCrossHair(229,10);
  drawCrossHair(229,160);
  drawCrossHair(229,309);
  
  calibrate(10, 10, 0);
  calibrate(10, 160, 1);
  calibrate(10, 309, 2);
  calibrate(120, 10, 3);
  calibrate(120, 160, 4);
  calibrate(120, 309, 5);
  calibrate(229, 10, 6);
  calibrate(229, 160, 7);
  calibrate(229, 309, 8);
  
  px = ((float(rx[0]+rx[1]+rx[2])/3)-(float(rx[6]+rx[7]+rx[8])/3))/220;
  if (px>=0)
    ox = (((rx[6]+rx[7]+rx[8])/3))-(px*10);
  else
    ox = (((rx[0]+rx[1]+rx[2])/3))+(px*10);

  py = ((float(ry[0]+ry[3]+ry[6])/3)-(float(ry[2]+ry[5]+ry[8])/3))/300;
  if (py>=0)
    oy = (((ry[2]+ry[5]+ry[8])/3))-(py*10);
  else
    oy = (((ry[0]+ry[3]+ry[6])/3))+(py*10);
    

  done();
  while(true) {}
}
