void drawInvader() {
    int maxX=40;
  uView.setFontType(0);
  uView.setCursor(0,0);
  uView.print("  bam  ");
  for (int x=0; x<maxX;x+=2) {
    printInvaders(x,maxX);
  }

  for (int x=maxX; x>0;x-=2) {
    printInvaders(x,maxX);
  }
}

void printInvaders(int x, int maxX) {
int  onDelay=30;
    uView.setFontType(4);    
    uView.drawChar(x,0,48,WHITE, XOR);
    uView.setFontType(5);
    uView.drawChar(maxX-x,14,48,WHITE,XOR);
    uView.setFontType(6); 
    uView.drawChar(maxX-x,20,48,WHITE,XOR);  
    uView.setFontType(7);
    uView.drawChar(x,32,48,WHITE,XOR);

    uView.display();
    delay(onDelay);
    uView.setFontType(4);
    uView.drawChar(x,0,48,WHITE, XOR);
    uView.setFontType(5); 
    uView.drawChar(maxX-x,14,48,WHITE,XOR);
    uView.setFontType(6); 
    uView.drawChar(maxX-x,20,48,WHITE,XOR);  
    uView.setFontType(7);
    uView.drawChar(x,32,48,WHITE,XOR);

    uView.display();
    uView.setFontType(4);
    uView.drawChar(x,0,49,WHITE, XOR);
    uView.setFontType(5);
    uView.drawChar(maxX-x,10,49,WHITE,XOR);
    uView.setFontType(6); 
    uView.drawChar(maxX-x,20,49,WHITE,XOR);  
    uView.setFontType(7);
    uView.drawChar(x,32,49,WHITE,XOR);

    uView.display();
    delay(onDelay);
    uView.setFontType(4);
    uView.drawChar(x,0,49,WHITE, XOR);
    uView.setFontType(5);
    uView.drawChar(maxX-x,14,49,WHITE,XOR);
    uView.setFontType(6); 
    uView.drawChar(maxX-x,20,49,WHITE,XOR);  
    uView.setFontType(7);
    uView.drawChar(x,32,49,WHITE,XOR);
    uView.display();
    uView.clear(PAGE);
}


void printInvader(int invaderType) {
    uView.setFontType(4);    
    uView.drawChar(22,uView.getLCDHeight()-uView.getFontHeight(),48,WHITE, XOR);
}


