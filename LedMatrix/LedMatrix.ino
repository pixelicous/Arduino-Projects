#include <LedControl.h>

const int DIN_PIN = 4;
const int CS_PIN = 1;
const int CLK_PIN = 0;

const uint64_t IMAGES[] = {
  0x00387c7c7c380000,
  0x00001c3e3e3e1c00,
  0x0000000e1f1f1f0e,
  0x0000001c3e3e3e1c,
  0x0000387c7c7c3800,
  0x0070f8f8f8700000,
  0x387c7c7c38000000,
  0x001c3e3e3e1c0000,
  0x001c3e3e3e1c0000,
  0x00000e1f1f1f0e00,
  0x0000001c3e3e3e1c,
  0x0000387c7c7c3800,
  0xffc7838383c7ffff,
  0x0038444444380000,
  0xffc7bbbbbbc7ffff,
  0x00384444443d0307,
  0x0038444438107c10,
  0x060e0c0808281800,
  0x001838302020a060,
  0x0c1c181010503000,
  0x0307060404140c00,
  0x066eecc88898f000,
  0x00105438ee385410
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
  displayImage(IMAGES[i]);
  if (++i > IMAGES_LEN ) {
    i = 0;
  }
  delay(240);
}
