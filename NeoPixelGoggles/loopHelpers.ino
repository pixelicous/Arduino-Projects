
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
