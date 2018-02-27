
#include "Tlc5940.h"
#include "hsv2rgb.h"

#define NUM_LEDS 10

struct RGB { byte r; byte g; byte b; };

// Candle Mode variables


// the start of the flicker (low)
static int CandFlicker_low_min = 200;
static int CandFlicker_low_max = 240;
// the end value of the flicker (high)
static int CandFlicker_high_min = 230;
static int CandFlicker_high_max = 255; 
// delay between each low-high-low cycle
// low->high |flicker_hold| high->low
static int CandFlicker_hold_min = 40; // milliseconds
static int CandFlicker_hold_max = 80; // milliseconds 
// delay after each low-high-low cycle
// low->high->low |flicker_pause| low->high...
static int CandFlicker_pause_min = 100; // milliseconds
static int CandFlicker_pause_max = 200;  // milliseconds 
// delay low to high and high to low cycle
static int CandFlicker_speed_min = 900; // microseconds
static int CandFlicker_speed_max = 1000; // microseconds



RGB rgb;
int global_dim=16;

void setup(){

	Tlc.init();  
}

void loop(){
  
	randomSeed(millis());
 
	int wait=random(1,5);
	int dim=random(6,6);
	int max_cycles=8;
	int cycles=random(1,max_cycles+1);
	
	rainbowCycle(wait,cycles,dim);
	
}

void setLed(byte num,int red,int green,int blue){

	if(global_dim){
		red=red/global_dim;
		green=green/global_dim;
		blue=blue/global_dim;
	}
	
	Tlc.set(num*3,red);
	Tlc.set(num*3+1,green);
	Tlc.set(num*3+2,blue);
	
} 

void rainbowCycle(uint8_t wait,byte cycle,byte dim) {
  
  int cycles, j, k;
  
  for(cycles=0;cycles<cycle;cycles++){
  
    byte dir=random(0,2);
    k=255;
    
    for (j=0; j < 256; j++,k--) {     // cycles of all colors in the wheel
      
      if(k<0)k=255;
 
   // Tlc.clear();
 
      for(int i=0; i<NUM_LEDS; i+=1) {
        
        Wheel(((i * 256 / NUM_LEDS) + (dir==0?j:k)) % 256,dim);        
        setLed(i,rgb.r*16,rgb.g*16,rgb.b*16);
	    

      }
	Tlc.update();
      delay(wait);
    }
  }
}

void LedsCandle2(){
  int CandFlicker_random_low_start = 0;
int CandFlicker_random_low_end = 0;
int CandFlicker_random_high = 0;
int CandFlicker_random_speed_start = 0;
int CandFlicker_random_speed_end = 0;

  int hue = 19;
int sat = 255;
int val;  
   // random time for low
  CandFlicker_random_low_start = random(CandFlicker_low_min, CandFlicker_low_max);
  CandFlicker_random_low_end = random(CandFlicker_low_min, CandFlicker_low_max);
   
  // random time for high
  CandFlicker_random_high = random(CandFlicker_high_min, CandFlicker_high_max);
   
  // random time for speed
  CandFlicker_random_speed_start = random(CandFlicker_speed_min, CandFlicker_speed_max);
  CandFlicker_random_speed_end = random(CandFlicker_speed_min, CandFlicker_speed_max);
   
  // low -> high
  
  for (int i = CandFlicker_random_low_start; i<CandFlicker_random_high; i++) {
    val=i;
       for(int led=0;led<(NUM_TLCS*8/3);led++){ // loop over all LED's
        setLed(led,hue,sat,val);
       	Tlc.update();
      }
    delayMicroseconds(CandFlicker_random_speed_start);
  }
   
  // hold
  delay(random(CandFlicker_hold_min, CandFlicker_hold_max));
   
  // high -> low
  for (int i = CandFlicker_random_high; i>=CandFlicker_random_low_end; i--) {
    val=i;
       for(int led=0;led<(NUM_TLCS*8/3);led++){ // loop over all LED's
        setLed(led,hue,sat,val);
      	Tlc.update();
      }
    delayMicroseconds(CandFlicker_random_speed_end);
  }
   
  // pause
  delay(random(CandFlicker_pause_min, CandFlicker_pause_max));
  
}


void Wheel(byte WheelPos,byte dim){
  
  if (WheelPos < 85) {
   rgb.r=0;
   rgb.g=WheelPos * 3/dim;
   rgb.b=(255 - WheelPos * 3)/dim;;
   return;
  } 
  else if (WheelPos < 170) {
   WheelPos -= 85;
   rgb.r=WheelPos * 3/dim;
   rgb.g=(255 - WheelPos * 3)/dim;
   rgb.b=0;
   return;
  }
  else {
   WheelPos -= 170; 
   rgb.r=(255 - WheelPos * 3)/dim;
   rgb.g=0;
   rgb.b=WheelPos * 3/dim;
   return;
  }
}


