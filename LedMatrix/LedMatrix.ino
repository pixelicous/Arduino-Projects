#include <LedControl.h>

const int DIN_PIN = 4;
const int CS_PIN = 1;
const int CLK_PIN = 0;

const uint64_t IMAGES[] = {
  0x817effffffff7e81,
  0x8142bda5a5bd4281,
  0x7e8199a5a599817e,
  0x003c425a5a423c00,
  0x0000182424180000,
  0x0000001818000000,
  0x00003c24243c0000,
  0x007e424242427e00,
  0xff818181818181ff,
  0xffc1a191898583ff,
  0xffc3a59999a5c3ff,
  0xffc3e7ffffe7c3ff,
  0xffffbd9999bdffff,
  0xffffbd9999bdffff,
  0x0000426666420000,
  0x0000001818000000,
  0x0000241818240000,
  0x8142241818244281,
  0x7ebddbe7e7dbbd7e,
  0x7e8199a5a599817e,
  0x003c425a5a423c00,
  0xa5a57e7e5aff9981,
  0xa5a57effdbff1800,
  0xa5a57e7e5aff9981,
  0xa5a57e7e5aff9981,
  0xcccc3333cccc3333,
  0x3333cccc3333cccc,
  0xcccc3333cccc3333,
  0x5555555555555555,
  0x00ff00ff00ff00ff,
  0xaaaaaaaaaaaaaaaa,
  0xff00ff00ff00ff00,
  0x9249249249249249,
  0x4992244992244992,
  0x2492492492492492,
  0x9249249249249249,
  0x2492492492492492,
  0x9249249249249249,
  0x00ff00ff00ff00ff,
  0xff00ff00ff00ff00,
  0x00ff00ff00ff00ff,
  0xff00ff00ff00ff00,
  0xaaaaaaaaaaaaaaaa,
  0x5555555555555555,
};
const int IMAGES_LEN = sizeof(IMAGES)/8;

LedControl display = LedControl(DIN_PIN, CLK_PIN, CS_PIN);

void setup() {
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 1);
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}

int i = 0;

void loop() {
  displayImage(IMAGES[random(0,IMAGES_LEN)]);
  if (++i > IMAGES_LEN ) {
    i = 0;
  }
  delay(240);
}
