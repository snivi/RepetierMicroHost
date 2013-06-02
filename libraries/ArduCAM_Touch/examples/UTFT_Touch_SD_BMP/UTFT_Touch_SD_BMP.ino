// UTFT_Read_BMP (C)2012 uCtronics
// web: http://www.uctronics.com
//
// This program is a demo for modified UTFT.library
// and illustrate how to read bmp file from SD card.
//
// This program requires the UTFT library (8bit mode)
// and the code is compatible with both UNO and Mega board.
// No code modification required.
//
// This program requires the modified UTFT library by electronics.lee
// The orignal UTFT library is written by Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//

#include <UTFT.h>
#include <SD.h>
#include <Wire.h>
#include <ArduCAM_Touch.h>
#include <SPI.h>

#define SD_CS 8 
#define BMPIMAGEOFFSET 54

// Declare which fonts we will be using
extern uint8_t SmallFont[];

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

  if (!SD.begin(SD_CS)) 
  {
    //while (1);
  }
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
  waitForTouch();
  myGLCD.clrScr();
}



void loop()
{
  char VH,VL;
  File inFile;
  inFile = SD.open("input.bmp",FILE_READ);
  if (! inFile) 
  {
    //while (1);  //if file does not exsit, stop here.
  }
  
  //startup();
  
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


  myGLCD.InitLCD(PORTRAIT);
  myGLCD.clrScr();
  
  myGLCD.dispBitmap(inFile);
  inFile.close();
  while(1);
}

