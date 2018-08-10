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