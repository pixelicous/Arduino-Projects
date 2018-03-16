void answers() {
  int randomNumber;
    uView.clear(PAGE);
  
  randomSeed(analogRead(0));
  randomNumber = random(1,7);
  uView.setCursor(0, 0);
  switch (randomNumber) {
    case 1:
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*4.5, 0);
    uView.print("The world");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*4.5, uView.getFontHeight());  
    uView.print("is yours!");
    break;
    case 2:
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*2.5, 0);
    uView.print("Abso-");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*3.5, uView.getFontHeight());  
    uView.print("fucken-");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*3.5, uView.getFontHeight()*2);
    uView.print("lutely!");
    break;
    case 3:
    uView.setCursor(0, 0);
    uView.print("You got it");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*1.5, uView.getFontHeight());
    uView.print("!!!");
    break;
    case 4:
    uView.setCursor(1, 0);
    uView.print("Go get it!");
    break;
    case 5:
    uView.setCursor(1, 0);
    uView.print("Everything");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*2, uView.getFontHeight());
    uView.print("is");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*4.5, uView.getFontHeight()*2);
    uView.print("Possible!");
    break;
    case 6:
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*3.5, 0);
    uView.print("Nothing");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*1.5, uView.getFontHeight());
    uView.print("Can");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*4.5, uView.getFontHeight()*2);
    uView.print("Stop You!");
    break;
    case 7:
    uView.print("What are you waiting for!");
    break;
    case 8:
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*7, uView.getFontHeight());
    uView.print("No pain");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth()*8, uView.getFontHeight());
    uView.print("No gain!");
    break;
  }
  printInvader(4);
  uView.display();
  uView.setFontType(0); 
}

