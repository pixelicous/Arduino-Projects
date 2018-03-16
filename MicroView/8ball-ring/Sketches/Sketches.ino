//////////// 8Ball MicroView Ver 0.1
//////////// By: Netzer Rom 2018                        
//////////// Software date: 16.3.2018                  

#include <MicroView.h>

#define SHAPE_SIZE 600
#define ROTATION_SPEED 3 // ms delay between cube draws

int SCREEN_WIDTH = uView.getLCDWidth();
int SCREEN_HEIGHT = uView.getLCDHeight();

float d = 3;
float px[] = { -d,  d,  d, -d, -d,  d,  d, -d };
float py[] = { -d, -d,  d,  d, -d, -d,  d,  d };
float pz[] = { -d, -d, -d, -d,  d,  d,  d,  d };

float p2x[] = {0,0,0,0,0,0,0,0};
float p2y[] = {0,0,0,0,0,0,0,0};

float r[] = {0,0,0};

void setup()
{
	uView.begin();
	uView.clear(ALL);
	uView.display();  
}

void loop()
{
  demoNumber(1);
  for (int i=0;i<500;i++) {
     drawCube();
     delay(ROTATION_SPEED);
  }
  demoNumber(2);
  for (int i=0;i<3;i++) {
    drawHeart();
  }
  demoNumber(3);
  for (int i=0;i<3;i++) {
    drawWaves();
  }
  demoNumber(4);
    for (int i=0;i<3;i++) {
    drawSliders();
  }
}

