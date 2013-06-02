
#include <UTFT.h>
#include <SD.h>
#include <SPI.h>
#include <ArduCAM_Touch.h>

#include "Z:\reprap\Windows\Pronterface\printrun-win\dist\images\homeX.c"

#include "Z:\reprap\32lcd\revB\examples\Arduino\Host\gui.h"

// Declare which fonts we will be using
extern uint8_t SmallFont[];

UTFT myGLCD(ITDB32S,A1,A2,A0,A3);    // Remember to change the model parameter to suit your display module!
ArduCAM_Touch  myTouch(10,9);

unsigned long tx=0;
unsigned long ty=0;

int x,y,z,e;

char n_tab;

void setup()
{
  x=200;
  // Setup the LCD
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.setFont(SmallFont);
  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_HI);
  myGLCD.setBackColor(R_FOND,V_FOND,B_FOND);
  myGLCD.setColor(R_FOND,V_FOND,B_FOND); 
  show_tab(TAB_JOG);
}

void drawPie(int x, int y, int r, int startAngle, int endAngle)
{
	int px, py, cx, cy;

	startAngle -= 90;
	endAngle   -= 90;
	if (startAngle>endAngle)
		startAngle -= 360;
	
	px = x + cos((startAngle*3.14)/180) * r;
	py = y + sin((startAngle*3.14)/180) * r;
	myGLCD.drawLine(x, y, px, py);
	for (int d=startAngle+1; d<endAngle+1; d++)
	{
		cx = x + cos((d*3.14)/180) * r;
		cy = y + sin((d*3.14)/180) * r;
		myGLCD.drawLine(px, py, cx, cy);
		px = cx;
		py = cy;
	}
	myGLCD.drawLine(x, y, px, py);
}

void draw_value_int(int value, int x , int y, char* label)
{
  myGLCD.setColor(R_FOND,V_FOND,B_FOND);
  myGLCD.fillRect(x-2,y-2,x+18,x+8*5);
  myGLCD.setColor(R_TEXT_BOX,V_TEXT_BOX,B_TEXT_BOX);
  myGLCD.setColor(R_INTERNAL,V_INTERNAL,B_INTERNAL);
  myGLCD.drawRoundRect(x-2,y-2,x+8*6,y+18);
  myGLCD.setColor(R_TEXT,V_TEXT,B_TEXT);
  myGLCD.print(label,x+2,y+2);
  myGLCD.printNumI(value,x+2+2*8+4,y+2,3);
}

int length(char *chaine)
{
  int i;
  i=0;
  while(chaine[i] != 0 ) i++;
  return(i);
}

void draw_button(int x,int y,char validate,char *label)
{
  myGLCD.setColor(R_FOND,V_FOND,B_FOND);
  myGLCD.fillRect(x,y,x+(16*10),y+22);
  myGLCD.setColor(R_BUTTON,V_BUTTON,B_BUTTON); 
  myGLCD.drawRoundRect(x,y,x+(8*10),y+22);
  myGLCD.setColor(R_TEXT_BUTTON,V_TEXT_BUTTON,B_TEXT_BUTTON); 
  myGLCD.print(label,x+41-((length(label)/2)*8),y+6);
}

void draw_check(int x,int y,char validate,char *text)
{
  myGLCD.setColor(R_FOND,V_FOND,B_FOND);
  myGLCD.fillRect(x,y,x+16,y+16);
  myGLCD.setColor(R_CHECK,V_CHECK,B_CHECK);
  myGLCD.drawRect(x+3,y+3,x+16-3,y+16-3);
  if ( validate )
  {
    myGLCD.setColor(R_CHECK_CROSS,V_CHECK_CROSS,B_CHECK_CROSS);
    myGLCD.drawLine(x,y,x+15,y+15);
    myGLCD.drawLine(x+1,y+15,x+15,y+1);
  }
  myGLCD.setColor(R_TEXT,V_TEXT,B_TEXT);
  myGLCD.print(text,x+16+3,y+3);
}

void show_tab(char no_tab)
{
  n_tab=no_tab;
  myGLCD.setBackColor(R_FOND,V_FOND,B_FOND);
  myGLCD.setColor(R_FOND,V_FOND,B_FOND);
  myGLCD.drawLine(0,16,3*8+3+4*8+3+5*8+3,16 );
  myGLCD.fillRect(16,32, 319-12, 239-16);

  myGLCD.setColor(R_ONGLET,V_ONGLET,B_ONGLET);
  if (no_tab != TAB_JOG ) myGLCD.drawLine(X_START_JOG,Y_END_JOG,X_END_JOG,Y_END_JOG ); // 1er choix non selectionne
  myGLCD.drawLine(X_START_JOG,Y_START_JOG,X_END_JOG,Y_START_JOG ); // 1er choix selectionne   
  myGLCD.drawLine(X_END_JOG,Y_START_JOG,X_END_JOG,Y_END_JOG);
  myGLCD.setColor(R_TEXT,V_TEXT,B_TEXT);
  myGLCD.print("JOG", X_START_JOG+3 , Y_START_JOG+3);
  myGLCD.setColor(R_ONGLET,V_ONGLET,B_ONGLET);
  if (no_tab != TAB_TEMP ) myGLCD.drawLine(X_START_TEMP,Y_END_TEMP,X_END_TEMP,Y_END_TEMP); //2em choix non selectionne
  myGLCD.drawLine(X_START_TEMP,Y_START_TEMP,X_END_TEMP,Y_START_TEMP); //2em choix selectionne  
  myGLCD.drawLine(X_END_TEMP,Y_START_TEMP,X_END_TEMP,Y_END_TEMP);
  myGLCD.setColor(R_TEXT,V_TEXT,B_TEXT);
  myGLCD.print("TEMP",X_START_TEMP+3,Y_START_TEMP+3);

  myGLCD.setColor(R_ONGLET,V_ONGLET,B_ONGLET);
  if (no_tab != TAB_GCODE) myGLCD.drawLine(X_START_GCODE,Y_END_GCODE,X_END_GCODE,Y_END_GCODE); //3em choix non selectionne
  myGLCD.drawLine(X_START_GCODE,Y_START_GCODE,X_END_GCODE,Y_START_GCODE); //3em choix selectionne  
  myGLCD.drawLine(X_END_GCODE,Y_START_GCODE,X_END_GCODE,Y_END_GCODE);
  myGLCD.setColor(R_TEXT,V_TEXT,B_TEXT);
  myGLCD.print("GCODE",X_START_GCODE+3,Y_START_GCODE+3);

  myGLCD.setColor(R_ONGLET,V_ONGLET,B_ONGLET);
  myGLCD.drawLine(3*8+3+4*8+3+5*8+3,0,3*8+3+4*8+3+5*8+3,16); 
  myGLCD.drawLine(3*8+3+4*8+3+5*8+3, 16, 319-20, 16);
  myGLCD.drawLine(319-20, 16, 319, 16+20);
  myGLCD.drawLine(319,16+20, 319, 239-20);
  myGLCD.drawLine(319,239-20, 319-20, 239);
  myGLCD.drawLine(20,239, 319-20, 239);
  myGLCD.drawLine(20,239,0,239-20);
  myGLCD.drawLine(0,0,0,239-20);

  myGLCD.setColor(R_INTERNAL,V_INTERNAL,B_INTERNAL);
  myGLCD.drawLine(3,16+3+20,3,239-20-3);
  myGLCD.drawLine(3,239-20-3,3+20,239-3);
  myGLCD.drawLine(3+20,239-3,319-20-3,239-3);
  myGLCD.drawLine(319-20-3,239-3,319-3,239-3-20);
  myGLCD.drawLine(319-3,239-3-20,319-3,16+20+3);
  myGLCD.drawLine(319-3,16+20+3,319-3-20,16+3);
  myGLCD.drawLine(319-3-20,16+3,20+3,16+3);
  myGLCD.drawLine(20+3,16+3,3,16+3+20);
  
  if (no_tab == TAB_TEMP )
  {
   draw_button(24,40,false,"PLA HEAT");
   myGLCD.drawRect(123,35,294,219);
  }
  
  if (no_tab == TAB_JOG )
  {
    // Home X Y Z ALL
    myGLCD.setColor(R_TEXT,V_TEXT,B_TEXT);
    myGLCD.drawBitmap(X_START_HOME_Y,Y_START_HOME_Y,22,19,homeX);
    myGLCD.print("Y",16+22+4,38+5);
    myGLCD.drawBitmap(170,38,22,19,homeX);
    myGLCD.print("Z",170+22+4,38+5);
    myGLCD.drawBitmap(16,199,22,19,homeX);
    myGLCD.print("X",16+22+4,199+5);
    myGLCD.drawBitmap(170,199,22,19,homeX);

    myGLCD.print(" 1  10  100",112,128-8,270+45);
    myGLCD.print("+X",172+8,128-8);
    myGLCD.print("+Y",112-8,128-90+8);
    myGLCD.print("+Z",235-8,128-90+8);
    
    myGLCD.setColor(R_JOG,V_JOG,B_JOG);
    // Croix direction XY
    drawPie(112,128, 90, -30, 30);
    drawPie(112,128, 90, 60, 120);
    drawPie(112,128, 90, 150, 210);
    drawPie(112,128, 90, 240, 300);
    
    drawPie(112,128, 60, -30, 30);
    drawPie(112,128, 60, 60, 120);
    drawPie(112,128, 60, 150, 210);
    drawPie(112,128, 60, 240, 300);
    
    drawPie(112,128, 30, -30, 30);
    drawPie(112,128, 30, 60, 120);
    drawPie(112,128, 30, 150, 210);
    drawPie(112,128, 30, 240, 300);
    
    // Croix direction Z
    drawPie(235 ,128,90,-15,15);
    drawPie(235 ,128,60,-15,15);
    drawPie(235 ,128,30,-15,15);
    
    drawPie(235 ,128,90,165,195);
    drawPie(235 ,128,60,165,195);
    drawPie(235 ,128,30,165,195);

    draw_value_int(x,259,80,"X:");
    draw_value_int(y,259,80+27,"Y:"); 
    draw_value_int(z,259,80+27*2,"Z:"); 
    draw_value_int(e,259,80+27*3,"E:");  
  }
}

void loop()
{
  while (myTouch.dataAvailable() == false) {}
  {
    myTouch.read();
    tx=myTouch.getX();
    ty=myTouch.getY();
  }
  // Gestion Tab
  if ( tx > X_START_JOG && tx < X_END_JOG && ty > Y_START_JOG && ty < Y_END_JOG ) show_tab(TAB_JOG);
  if ( tx > X_START_TEMP && tx < X_END_TEMP && ty > Y_START_TEMP && ty < Y_END_TEMP ) show_tab(TAB_TEMP);
  if ( tx > X_START_GCODE && tx < X_END_GCODE && ty > Y_START_GCODE && ty < Y_END_GCODE ) show_tab(TAB_GCODE);
  
  // Gestion touche ecran JOG
  myGLCD.setColor(R_ONGLET,V_ONGLET,B_ONGLET);
  if (n_tab==TAB_JOG && tx > X_START_JOG_YP100 && tx < X_END_JOG_YP100 && ty > Y_START_JOG_YP100 && ty < Y_END_JOG_YP100)
    myGLCD.print("YP_100",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_YP10 && tx < X_END_JOG_YP10 && ty > Y_START_JOG_YP10 && ty < Y_END_JOG_YP10)
    myGLCD.print("YP_10",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_YP1 && tx < X_END_JOG_YP1 && ty > Y_START_JOG_YP1 && ty < Y_END_JOG_YP1)
    myGLCD.print("YP_1",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_YM1 && tx < X_END_JOG_YM1 && ty > Y_START_JOG_YM1 && ty < Y_END_JOG_YM1 )
    myGLCD.print("YM_1",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_YM10 && tx < X_END_JOG_YM10 && ty > Y_START_JOG_YM10 && ty < Y_END_JOG_YM10 )
    myGLCD.print("YM_10",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_YM100&& tx < X_END_JOG_YM100&& ty > Y_START_JOG_YM100&& ty < Y_END_JOG_YM100)
    myGLCD.print("YM_100",RIGHT,4);
    
    if (n_tab==TAB_JOG && tx > X_START_JOG_XP100 && tx < X_END_JOG_XP100 && ty > Y_START_JOG_XP100 && ty < Y_END_JOG_XP100)
      myGLCD.print("XP_100",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_XP10 && tx < X_END_JOG_XP10 && ty > Y_START_JOG_XP10 && ty < Y_END_JOG_XP10)
      myGLCD.print("XP_10",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_XP1 && tx < X_END_JOG_XP1 && ty > Y_START_JOG_XP1 && ty < Y_END_JOG_XP1)
      myGLCD.print("XP_1",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_XM1 && tx < X_END_JOG_XM1 && ty > Y_START_JOG_XM1 && ty < Y_END_JOG_XM1 )
      myGLCD.print("XM_1",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_XM10 && tx < X_END_JOG_XM10 && ty > Y_START_JOG_XM10 && ty < Y_END_JOG_XM10 )
      myGLCD.print("XM_10",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_XM100&& tx < X_END_JOG_XM100&& ty > Y_START_JOG_XM100&& ty < Y_END_JOG_XM100)
      myGLCD.print("XM_100",RIGHT,4);
      
   if (n_tab==TAB_JOG && tx > X_START_JOG_ZP10 && tx < X_END_JOG_ZP10 && ty > Y_START_JOG_ZP10 && ty < Y_END_JOG_ZP10)
      myGLCD.print("ZP_10",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_ZP1 && tx < X_END_JOG_ZP1 && ty > Y_START_JOG_ZP1 && ty < Y_END_JOG_ZP1)
      myGLCD.print("ZP_1",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_ZM1 && tx < X_END_JOG_ZM1 && ty > Y_START_JOG_ZM1 && ty < Y_END_JOG_ZM1 )
      myGLCD.print("ZM_1",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_JOG_ZM10 && tx < X_END_JOG_ZM10 && ty > Y_START_JOG_ZM10 && ty < Y_END_JOG_ZM10 )
      myGLCD.print("ZM_10",RIGHT,4);
    
   if (n_tab==TAB_JOG && tx > X_START_HOME_Y&& tx < X_END_HOME_Y&& ty > Y_START_HOME_Y&& ty < Y_END_HOME_Y)
      myGLCD.print("HOME_Y",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_HOME_X&& tx < X_END_HOME_X&& ty > Y_START_HOME_X&& ty < Y_END_HOME_X)
      myGLCD.print("HOME_X",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_HOME_ALL&& tx < X_END_HOME_ALL&& ty > Y_START_HOME_ALL&& ty < Y_END_HOME_ALL)
      myGLCD.print("HOME_ALL",RIGHT,4);
   if (n_tab==TAB_JOG && tx > X_START_HOME_Z&& tx < X_END_HOME_Z&& ty > Y_START_HOME_Z&& ty < Y_END_HOME_Z)
      myGLCD.print("HOME_Z",RIGHT,4);  
  
  myGLCD.printNumI(tx, RIGHT, 100);
  myGLCD.printNumI(ty, RIGHT, 120);

}


