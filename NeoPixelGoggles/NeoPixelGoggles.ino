// Low power NeoPixel goggles.  Makes a nice blinky display
// with just a few LEDs on at any time.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif

#define PIN 0
#define POLICE_BLUE pixels.Color(0,0,255)
#define POLICE_AMBER pixels.Color(255,64,0)
#define POLICE_INTERCOL pixels.Color(0,0,32)
#define black pixels.Color(0,0,0)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start red
uint32_t prevTime;
const int timedelay = 20;

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
  prevTime = millis();
}

void loop() {
  uint8_t  i;
  uint32_t t;

  // if button pressed switch color to jog wheel color- press again, default colors of functions

  switch(mode) {

   case 0: loop_sparks(); break;// Random sparks - just one LED on at a time!
   case 1: loop_spinner(color, offset); break;// Spinny wheels (8 LEDs on at a time)
   case 2: loop_rainbow(); break;
   case 4: loop_police(); break;
   case 5: loop_green_swirl(); break;
   
  }

  t = millis();
  if((t - prevTime) > 3000) {      // Every 8 seconds...
    mode++;                        // Next mode
    if(mode > 5) {                 // End of modes?
      mode = 0;                    // Start modes over
      color >>= 8;                 // Next color R->G->B
      if(!color) color = 0xFF0000; // Reset to red
    }
    for(i=0; i<32; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}

void loop_rainbow() {
  byte col = 0;
  byte pix = 0;
  int i=0;
  for(int i=0;i<10;i++) {
    setPixelMirror(pix, primaryToColour(col));
    col = (col + 1) % 6;
    pix = (pix + 1) % 16;
    pixels.show();
    delay(166); // will give us one swizzle per second with 6 colours
    i++;
  }
}

void loop_sparks() {
    int i = random(32);
    color = random(0,2147483647);
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(random(80,450));
    pixels.setPixelColor(i, 0);
}

void loop_spinner(uint32_t color, uint8_t offset) {
    for(int i=0; i<16; i++) {
      uint32_t c = 0;
      color >>= 3;
      if(((offset + i) & 7) < 2) c = color; // 4 pixels on...
      pixels.setPixelColor(   i, c); // First eye
      pixels.setPixelColor(31-i, c); // Second eye (flipped)
    }
    pixels.show();
    offset++;
    delay(50);
}


void loop_police() {

  uint16_t phase=0;
  for(int i=0;i<10;i++) {

    for(byte pixel = 0; pixel < 32; pixel++) {
      pixels.setPixelColor(pixel, police_colour(phase, pixel));
    }

    // render and advance
    // this needs to be a common multiple of all relevant phases
    // otherwise we get jumps at rollover.
    phase = (phase + 1) % (256 * 6);
    pixels.show();
    delay(40);
  }
}

void loop_greentime() {

}

void loop_colorpicker() {

}

void loop_green_swirl() {
  for(byte start=0; start<16; start++) {
    for(byte pix=0; pix<16; pix++) {
      setPixelMirror(pix, green_swirl_colour(start, pix));
    }
    pixels.show();
    delay(200);
  }
}

byte intpow(byte e, byte n) {
  byte v = 1;
  for(;n>0;n--) {
    v *= e;
  }
  return v; 
}

uint32_t green_swirl_colour(byte start, byte pix) {
  byte off = (pix - start) & 0x0F;
  if(off < 7) { 
    byte amt = intpow(2, off+1);
    uint32_t green = pixels.Color(0,amt,0);
    return green;
  } else {
    return black;
  }
}

void setPixelMirror(byte pix, uint32_t colour) {
  pixels.setPixelColor(pix, colour);
  pixels.setPixelColor(32 - pix - 1, colour);
}

uint32_t primaryToColour(byte primary) {
  switch(primary) {
    case 0: return pixels.Color(  0,  0,255);
    case 1: return pixels.Color(  0,255,  0);
    case 2: return pixels.Color(  0,128,64);
    case 3: return pixels.Color(255,  0,  0);
    case 4: return pixels.Color(192,  0,192);
    case 5: return pixels.Color(255,128,  0);
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

byte rotate_pixel(uint32_t phase, byte pixel) {
  return (pixel - rotate_offset(phase)) & 0x0F;
}

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
