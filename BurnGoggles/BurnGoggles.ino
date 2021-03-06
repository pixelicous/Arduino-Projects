//IF FOUND PLEASE RETURN TO NETZER (pixi@pixelabs.net) THANK YOU!!!

#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include "prng.h"
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif
/* EEPROM usage:
 *   byte 0: last used mode
 *   byte 1: PRNG seed
 *   byte 2: PRNG seed
 */

#define NUMLEDS 32
#define PIN 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

byte mode=2;
int brt = 0;

extern uint16_t prng_register;

#define black strip.Color(0,0,0)

void setup() {
  initRandom();
  // Code to use reset button as mode switcher
  
  mode = (EEPROM.read(0));
  //switch between brtness modes
  if (mode == 0) {brt=40;}
  if (mode==1) {brt = 80;}
  if (mode==2) {brt = 255;}

  if (mode == 2) {EEPROM.write(0, 0);}
  else{EEPROM.write(0, mode+1);}

  strip.setBrightness(brt);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off  
}

void loop() {

  int list[] = {0,1,2,3,4,5,6,7,8,9,10,11};
  int size = sizeof(list);
  shuffleArray(list,size);
  int clr = random(0,7);

  for (int i=0;i<size; i++) {
    switch(list[i]) {
      case 0:
      loop_colorball(1);
      break;

      case 1: 
      theaterChase(clr,50,20);
      break;

      case 2: 
      loop_white_flash(1);
      break;

      case 3:
      loop_swirl(1);
      break; 

      case 4:
      loop_pulse_lr_colours(2);
      break;

      case 5:
      loop_police(100);
      break;

      case 6:
      loop_prng(3);
      break;

      case 7:
      loop_rainbow(15); 
      break;

      case 8:
      loop_amber_lr_pulse(2);
      break;

      case 9:
      loop_rainbow_on_off(2);
      break;

      case 10:
      loop_colour_swizz(5);
      break;

      case 11:
      loop_spin(0.2,30,clr);
      break;

    }
  }
}

void shuffleArray(int * array, int size)
{
  int last = 0;
  int temp = array[last];
  for (int i=0; i<size; i++)
  {
    int index = random(size);
    array[last] = array[index];
    last = index;
  }
  array[last] = temp;
}

void loop_slow_primary_fill() {

  uint32_t colour = strip.Color(1,1,1);
  setAllPixels(colour);

  strip.show();

  byte leftPrimary=-1;
  byte rightPrimary=-1;

  
  leftPrimary=pickPrimary(leftPrimary, rightPrimary);
  uint32_t leftColour = primaryToColour(leftPrimary);
  for(byte pix=0; pix<16; pix++) {
    strip.setPixelColor(pix, leftColour);
    strip.show();
    delay(1000);
    
    rightPrimary=pickPrimary(rightPrimary, leftPrimary);
    uint32_t rightColour = primaryToColour(rightPrimary);
    for(byte pix=16; pix<32; pix++) {
      strip.setPixelColor(pix, rightColour);
      strip.show();
      delay(1000);
    }
    
  }
}

void loop_white_flash(int loopy) {
  for (int c=0;c<=5;c++) {
    for (int i=0;i<=loopy;i++) {
     // uint32_t white = strip.Color(255,255,255);
      setAllPixels(black);
      strip.show();
      delay(100*i+10);
      setAllPixels(primaryToColour(c));
      strip.show();
      delay(200*i+10);
    }
  }
  setAllPixels(black);
}


uint32_t swirl_colour(byte start, byte pix) {
  byte off = (pix - start) & 0x0F;
  if(off < 7) { 
    byte amt = intpow(2, off+1);
    byte a = random(3);
    uint32_t cc = 0;
    if (a==0) {cc = strip.Color(0,amt,0);}
    if (a==1) {cc = strip.Color(amt,0,0);}
    if (a==2) {cc = strip.Color(0,0,amt);}
    return cc;
  } else {
    return black;
  }
}

void loop_swirl(int loopy) {
  for (int i=0;i<=loopy;i++) {
    for(byte start=0; start<16; start++) {
      for(byte pix=0; pix<16; pix++) {
        setPixelMirror(pix, swirl_colour(start, pix));
      }
      strip.show();
      delay(50);
    }
  }
}

void loop_pulse_lr_colours(int loopy) {
  for (int i=0;i<=loopy;i++) {
    for(byte level=0;level < 8*8; level++) {
      byte up = twopow(level);
      byte down = twopow(63-level);
      uint32_t left = strip.Color(0,up,down);
      uint32_t right = strip.Color(up,down,0);
      for(byte pix=0; pix<32; pix++) {
        strip.setPixelColor(pix, pix < 16 ? left : right);
      }
      strip.show();
      delay(25);
    }
  }
}

#define POLICE_BLUE strip.Color(0,0,255)
#define POLICE_AMBER strip.Color(255,64,0)
#define POLICE_INTERCOL strip.Color(0,0,32)

byte rotate_offset(uint16_t phase) {
  // needs to be a multiple of 6 so that
  // rotations do not happen out of phase
  // with the amber dots
  return phase/6;
}

uint32_t lbluex(uint16_t phase) {
  if((phase / 8) % 2 == 0) {
    return POLICE_BLUE;
  } else {
    return black;
  }
}

uint32_t rbluex(uint16_t phase) {
  if((phase / 8) % 2 == 0) {
    return black;
  } else {
    return POLICE_BLUE;
  }
}

uint32_t unrotated_police_colour(uint32_t (*bluecol)(uint16_t), uint16_t phase, byte pixel) {
  if(pixel >=0 && pixel < 8) return bluecol(phase); //pixel = 0 .. 7
  // if(pixel == 8) return POLICE_INTERCOL;

  if(pixel >= 8 && pixel <= 15) {

    byte amber_phase = 7 - phase % 8;

    if(amber_phase == (pixel - 9)) {
      return POLICE_AMBER;
    }
    else if(amber_phase == (pixel - 8)) {
      return POLICE_AMBER;
    } else {
      return black;
    }
  }

  // if this if is up by the other POLICE_INTERCOL,
  // the code uses 4 bytes extra (at time of writing)
  // if(pixel == 15) return POLICE_INTERCOL;
}

byte rotate_pixel(uint32_t phase, byte pixel) {
  return (pixel - rotate_offset(phase)) & 0x0F;
}

uint32_t x_police_colour(uint32_t (*bluecol)(uint16_t), uint16_t phase, byte pixel) {
  return unrotated_police_colour(bluecol, phase, rotate_pixel(phase, pixel));
}

uint32_t left_police_colour(uint16_t phase, byte pixel) {
  return x_police_colour(lbluex, phase, pixel);
}

uint32_t right_police_colour(uint16_t phase, byte pixel) {
  return x_police_colour(rbluex, phase, 31-pixel);
}

uint32_t police_colour(uint16_t phase, byte pixel) {
  if(pixel < 16) return left_police_colour(phase, pixel);
  if(pixel >= 16) return right_police_colour(phase, pixel);
}

void loop_police(int loopy) {
    uint16_t phase=0;
  for (int i=0;i<=loopy;i++) {
    for(byte pixel = 0; pixel < 32; pixel++) {
      strip.setPixelColor(pixel, police_colour(phase, pixel));
    }

    // render and advance
    // this needs to be a common multiple of all relevant phases
    // otherwise we get jumps at rollover.
    phase = (phase + 1) % (256 * 6);
    strip.show();
    delay(40);
  }
}

// show the PRNG shift register on one side - this should
// sort-of rotate but with feedback happening.
// and on the other side, set each LED in turn on or off
// based on the result of generating one random bit
// every time period. This one bit generation is also
// what will drive the first side to rotate.

#define PRNG_RED strip.Color(255,0,0)
#define PRNG_GREEN strip.Color(0,255,0)

void loop_prng(int loopy) {
    setAllPixels(black);
    strip.show();
  for (int i=0;i<=loopy;i++) {
    for(byte pix=0; pix<16; pix++) {
      byte b = nextRNGBit();
      if(b == 1) {
        strip.setPixelColor(pix, PRNG_RED);
      } else {
        strip.setPixelColor(pix, black);
      }
      for(byte lsfr_pix=0; lsfr_pix<16; lsfr_pix++) {
        byte lsfr_b = (prng_register >> lsfr_pix) & 1;
        if(lsfr_b == 1) {
          strip.setPixelColor(lsfr_pix + 16, PRNG_GREEN);
        } else {
          strip.setPixelColor(lsfr_pix + 16, black);
        }
      }
      strip.show();
      delay(100);
    } 
  }  
}


void loop_rainbow(int loopy) {
  byte col = 0;
  byte pix = 0;
  
  for (int i=0;i<=loopy;i++) {
    setPixelMirror(pix, primaryToColour(col));
    col = (col + 1) % 6;
    pix = (pix + 1) % 16;
    strip.show();
    delay(166); // will give us one swizzle per second with 6 colours
  }
}

void loop_amber_lr_pulse(int loopy) {
  for (int i=0;i<=loopy;i++) {
    for(byte offset=0; offset < 32; offset +=16) {
      for(byte level=8;level < 8*8; level++) {
        byte up = twopow(level);
        uint32_t left = strip.Color(up,up/2,0);
        for(byte pix=0; pix<16; pix++) {
          strip.setPixelColor(pix+offset, left);
        }
        strip.show();
        delay(10);
      }
      delay(200);
      for(byte level=8*8-1;level > 8; level--) {
        byte up = twopow(level);
        uint32_t left = strip.Color(up,up/2,0);
        for(byte pix=0; pix<16; pix++) {
          strip.setPixelColor(pix+offset, left);
        }
        strip.show();
        delay(15);
      }
      for(byte pix=0; pix<16; pix++) {
        strip.setPixelColor(pix+offset, black);
      }
      strip.show();
      delay(200);
    }
  }
}

void loop_rainbow_on_off(int loopy) {
  for (int i=0;i<=loopy;i++) {
    byte col = 0;

    for(byte offset=0; offset<32; offset+=16) {
      byte rot = nextRNGBits(4);
      byte dir = nextRNGBit();
      for(byte pix=0;pix<16;pix++) {
        byte phys_pix = (pix + rot) % 16;
        if(dir == 0) phys_pix = 15-phys_pix;
        strip.setPixelColor(phys_pix+offset, primaryToColour(col));
        col = (col + 1) % 6;
        strip.show();
        delay(30); // will give us one swizzle per second with 6 colours
      }
      for(byte pix=0;pix<16;pix++) {
      
        byte phys_pix = (pix + rot) % 16;
        if(dir == 0) phys_pix = 15-phys_pix;
        strip.setPixelColor(phys_pix+offset, black);
        strip.show();
        delay(70);
      }
    }
  }
}


uint32_t colour_of_swizz(byte offset, byte destpix) {
  byte pix = (destpix - offset) & 0x0F;
  if(pix >= 0 && pix < 3) return primaryToColour(1);
  if(pix >= 4 && pix < 7) return primaryToColour(0);
  if(pix >= 8 && pix < 11) return primaryToColour(3);
  if(pix >=12 && pix < 15) return primaryToColour(4);
  return black;
}

void loop_colour_swizz(int loopy)  {
  for (int i=0;i<=loopy;i++) {
    for(byte offset=0; offset<16; offset++) {
      for(byte pix = 0; pix < 16; pix++) {
        setPixelMirror(pix,colour_of_swizz(offset, pix));
      }
      strip.show();
      delay(100);
    }
  }
}

byte intpow(byte e, byte n) {
  byte v = 1;
  for(;n>0;n--) {
    v *= e;
  }
  return v; 
}

// n is a number between 0 .. 63
// so 6 bits
// use highest 3 bits as exponent
// and lowest 3 bits as linear filler
uint8_t twopow(uint8_t n) {
  uint8_t v = 1;
  uint8_t ex = (n & 0x38) >> 3;
  uint8_t fill = n & 0x07;
  v <<= ex;
  if(ex >= 3) {
    fill <<= ex - 3;
  } else { // ex < 3 
    fill >>= -(ex - 3);
  }
  v = v | fill;
  return v;
}


