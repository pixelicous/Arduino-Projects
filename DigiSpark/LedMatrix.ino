#include <LedControl.h>

const int DIN_PIN = 4;
const int CS_PIN = 1;
const int CLK_PIN = 0;

const uint64_t IMAGES[] = {
  0x7e8199a5a599817e,
  0x003c425a5a423c00,
  0x0000182424180000,
  0x0000001818000000,
  0x00003c24243c0000,
  0x007e424242427e00,
  0xff818181818181ff,
  0x007e424242427e00,
  0x00003c24243c0000,
  0x0000001818000000,
  0x1818181818181818,
  0x2424242424242424
};
const int IMAGES_LEN = sizeof(IMAGES);

const uint64_t IMAGEStwo[] = {
  0x3c7ec3bdffdb7e3c,
  0xc3813c42002481c3,
  0xc3810000000081c3,
  0xe7818100008181e7,
  0xff818181818181ff,
  0xff81bdc3a5a581ff,
  0x1824428181819966,
  0x183c7e8181819966,
  0x183c7effff819966,
  0x183c7effffffff66
};

const uint64_t IMAGES3[] = {
  0xe7c3810000000099,
  0x183c7effffffff66,
  0x182442ff9999ff66,
  0x182442bdff999966,
  0x42ad9999997e1866,
  0x04649c185e380c0c,
  0x2818183838180c0c,
  0x04649c185e380c0c,
  0x8142242424425a99,
  0x4242242424245a5a,
  0x8142242424425a99,
  0xff81bda585fd01ff,
  0xff81bda585fd01ff,
  0x007e425a7a02fe00
};

const uint64_t IMAGES4[] = {
 0x007e42426202fe00,
  0x007e02020202fe00,
  0x000602020202fe00,
  0x000000000002fe00,
  0x000000000000e000,
  0x0000000000000000,
  0x0000000000000000,
  0xffffffffffffffff,
  0xff7ddfff7bffeebf,
  0xd76dde65bb6ee9b7,
  0x7beddef5bbffeddf,
  0x52adda75abdc2dd3
};

const uint64_t IMAGES5[] = {
   0x08a55214aa902912,
  0x002410042a000800,
  0x0000000000000000,
  0x3e66663e66663e00,
  0x66361e3e66663e00,
  0x3c66660666663c00,
  0x188cc66363c68c18,
  0xc6633118183163c6,
  0x31188cc6c68c1831,
  0x188cc66363c68c18,
  0x008cc66363c68c00,
  0x0000000063630000,
  0x0000000063630000

};

const uint64_t IMAGES6[] = {
  0x00000000c6c60000,
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

const int IMAGEStwo_LEN = sizeof(IMAGEStwo)/8;
const int IMAGES3_LEN = sizeof(IMAGES3)/8;
const int IMAGES4_LEN = sizeof(IMAGES4)/8;
const int IMAGES5_LEN = sizeof(IMAGES5)/8;
const int IMAGES6_LEN = sizeof(IMAGES6)/8;

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

void loop() {

  for(int i=0;i<IMAGES_LEN;i++) {
    displayImage(IMAGES[i]);
    delay(700);
  }

  for(int i=0;i<IMAGEStwo_LEN;i++) {
    displayImage(IMAGEStwo[i]);
    delay(700);
  }

  for(int i=0;i<IMAGES3_LEN;i++) {
    displayImage(IMAGES3[i]);
    delay(700);
  }

  for(int i=0;i<IMAGES4_LEN;i++) {
    displayImage(IMAGES3[i]);
    delay(700);
  }

  for(int i=0;i<IMAGES5_LEN;i++) {
    displayImage(IMAGES3[i]);
    delay(700);
  }

  for(int i=0;i<IMAGES6_LEN;i++) {
    displayImage(IMAGES3[i]);
    delay(700);
  }
}
