void drawWaves() {
int i;
  float rad,srad, x,y;
  int amp=20;
  int nPhase=360;

  for(i=0; i<nPhase;i++) {
    x=i;
    x=x*0.017453;
    y= sin(x);
    y=y*amp;  // amplitude
    y=y+24;
    x=(double)64/(double)nPhase;
    x=x*i;
    uView.pixel(x, y);
    uView.display();
  }

  amp=10;
  nPhase=3*360;
  
  for(i=0; i<nPhase;i++) {
    x=i;
    x=x*0.017453;
    y= cos(x);
    y=y*amp;  // amplitude
    y=y+24;
    x=(double)64/(double)nPhase;
    x=x*i;
    uView.pixel(x, y);
  }

  uView.display();
  delay(1500);
  uView.clear(PAGE);
 }
