void loop_sparks() {
    int i = random(32);
    int color = random(0,2147483647);
    strip.setPixelColor(i, color);
    strip.show();
    delay(random(80,450));
    strip.setPixelColor(i, 0);
}

void loop_colorball(int loopy) {
  for (int i=0;i<=loopy;i++) {
    for (int c=0;c<=5;c++) {
      for (int pix=0;pix<16;pix++) {
        setPixelMirror(pix, primaryToColour(c));
        strip.show();
        delay(30);
      }
    }
  }
}


void setPixel(int Pixel, byte red, byte green, byte blue) {
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
}

void theaterChase(int clr, int SpeedDelay, int itr) {
uint32_t c = primaryToColour(clr);
 for (int j=0; j<itr; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUMLEDS; i=i+3) {
        strip.setPixelColor(i+q, c); // First eye
      }
      strip.show();
     
      delay(SpeedDelay);
     
      for (int i=0; i < NUMLEDS; i=i+3) {
        strip.setPixelColor(i+q, black); // First eye
      }
    }
  }
}
int spino = 0;
void loop_spin(int spd, int itr, int co) {
  for (byte i=0; i<itr;i++) {
    for(int i=0; i<16; i++) {
      uint32_t c = 0;
      if(((spino + i) & 7) < 2) c = primaryToColour(co); // 4 pixels on...
      strip.setPixelColor(i, c); // First eye
      strip.setPixelColor(NUMLEDS-i, c); // Second eye (flipped)
    }
    strip.show();
    spino++;
    delay(50);
  }
}