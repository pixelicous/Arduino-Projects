void loop_sparks() {
    int i = random(32);
    int color = random(0,2147483647);
    strip.setPixelColor(i, color);
    strip.show();
    delay(random(80,450));
    strip.setPixelColor(i, 0);
}
