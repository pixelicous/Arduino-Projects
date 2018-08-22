byte pickPrimary(byte oldPrimary, byte otherOldPrimary) {
  byte newPrimary=oldPrimary;
  while(newPrimary == oldPrimary || newPrimary == otherOldPrimary) {
    // using this random number generator is
    // pretty expensive - about 692 bytes.
    // newPrimary = random(0,6);
    newPrimary = get3BitRandomLessThan(6);
  }
  return newPrimary;
}

uint32_t primaryToColour(byte primary) {
  switch(primary) {
    case 0: return strip.Color(  0,  0,255);
    case 1: return strip.Color(  0,255,  0);
    case 2: return strip.Color(  0,128,64);
    case 3: return strip.Color(255,  0,  0);
    case 4: return strip.Color(192,  0,192);
    case 5: return strip.Color(255,128,  0);
    case 6: return strip.Color(255,255, 255);
  }
}

void setPixelMirror(byte pix, uint32_t colour) {
  strip.setPixelColor(pix, colour);
  strip.setPixelColor(NUMLEDS - pix - 1, colour);
}

void setAllPixels(uint32_t colour) {
  for(byte pix=0; pix<NUMLEDS; pix++) {
    strip.setPixelColor(pix, colour);  
  }
}
