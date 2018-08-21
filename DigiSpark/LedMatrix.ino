#include <LedControl.h>

const int DIN_PIN = 4;
const int CS_PIN = 1;
const int CLK_PIN = 0;

const uint64_t IMAGES[] = {
  0x3c7ec3bdffdb7e3c,
  0xc3813c42002481c3,
  0x1824428181819966,
  0x183c7e8181819966,
  0x183c7effff819966,
  0x183c7effffffff66,
  0xe7c3810000000099,
  0x183c7effffffff66,
  0x182442ff9999ff66,
  0x182442bdff999966,
  0x04649c185e380c0c,
  0x2818183838180c0c,
  0x04649c185e380c0c,
  0x8142242424425a99,
  0x4242242424245a5a,
  0x8142242424425a99,
  0x3e66663e66663e00,
  0x66361e3e66663e00,
  0x3c66660666663c00,
  0x188cc66363c68c18,
  0xc6633118183163c6,
  0x31188cc6c68c1831,
  0x188cc66363c68c18,
  0x008cc66363c68c00,
  0x00300000c6c60000,
  0x003c420066660000,
  0x003c400006660000,
  0x003c420000660000,
  0x0018180066660000,
  0x1800666600000000,
  0x6666000000000000,
  0xffff000000000000,
  0xffef250400000000,
  0xffffbab220200000,
  0xfffffffba9212000,
  0xfffffffff7f7d5d4,
  0xffffff7d74541400,
  0xfffffffda9a98080,
  0xfffff7d756020200,
  0xffffffffffebab89,
  0xffffffffffffffff,
  0xc19999c19999c1ff,
  0x99c9e1c19999c1ff,
  0xc39999f99999c3ff,
  0xc3a164607050b1c3,
  0x3c5e9b9f8faf4e3c
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
int i=0;
void loop() {
  displayImage(IMAGES[i]);
  if (++i >= IMAGES_LEN) {
    i = 0;
  }
  delay(00);
}
