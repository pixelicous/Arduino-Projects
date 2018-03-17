void demoNumber(int num) {
  uView.clear(PAGE);
  uView.setCursor(0, 0);
  uView.print(num);
  uView.print(":");
}

void sayHello() {
  uView.invert(random(0,2));
  uView.clear(PAGE);
  uView.rect(1,1,62,46);
  uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*4, (uView.getLCDHeight()/2)-uView.getFontHeight()-10);
    uView.print("What is");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*2, uView.getLCDHeight()/2-3);
    uView.print("your");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*5, (uView.getLCDHeight()/2)+uView.getFontHeight()+4);
    uView.print("question?");
    
  
}

