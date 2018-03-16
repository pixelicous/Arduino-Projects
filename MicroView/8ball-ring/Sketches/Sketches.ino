//////////// 8Ball MicroView Ver 0.1
//////////// By: Netzer Rom 2018                        
//////////// Software date: 16.3.2018                  

#include <MicroView.h>

int totalfonts = uView.getTotalFonts();

#define delayTime 2000
 #define SHAPE_SIZE 600
  #define ROTATION_SPEED 3 // ms delay between cube draws

  float d = 3;
  float px[] = { -d,  d,  d, -d, -d,  d,  d, -d };
  float py[] = { -d, -d,  d,  d, -d, -d,  d,  d };
  float pz[] = { -d, -d, -d, -d,  d,  d,  d,  d };
  
  float p2x[] = {0,0,0,0,0,0,0,0};
  float p2y[] = {0,0,0,0,0,0,0,0};
  
  float r[] = {0,0,0};


    int SCREEN_WIDTH = uView.getLCDWidth();
  int SCREEN_HEIGHT = uView.getLCDHeight();
void setup()
{
	uView.begin();
	uView.clear(ALL);
	uView.display();  
}

void loop()
{
  
    /*
  sayHello();
  uView.print(totalfonts);
  uView.display();
  delay(delayTime*2);

  for (int i=0;i<500;i++) {
     drawCube();
     delay(delayTime/300);
  }
uView.clear(PAGE);
  for (int i=0;i<3;i++) {
    drawHeart();
  }
uView.clear(PAGE);
  for (int i=0;i<1;i++) {
    drawWaves();
  }
uView.clear(PAGE);
    for (int i=0;i<1;i++) {
    drawSliders();
  }*/
    for (int i=0;i<7;i++) {
    answers();
    delay(delayTime);
  }/*
    for (int i=0;i<5;i++) {
    drawInvader();
    delay(400);
  }*/
}

