void answers() {
  int randomNumber;
    uView.clear(PAGE);
  
  randomSeed(analogRead(0));
  randomNumber = random(1,7);
  uView.setCursor(0, 0);
  switch (randomNumber) {
    case 1:
    uView.print("The world is yours!");
    break;
    case 2:
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth(), 0);
    uView.print("Abso");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth(), (uView.getLCDHeight()/2)-uView.getFontHeight());  
    uView.print("fucken");
    uView.setCursor((uView.getLCDWidth()/2)-uView.getFontWidth(), uView.getLCDHeight()-uView.getFontHeight());
    uView.print("lutely!");
    break;
    case 3:
    uView.print("You got it!");
    break;
    case 4:
    uView.print("Go get it!");
    break;
    case 5:
    uView.print("Everything is possible!");
    break;
    case 6:
    uView.print("Nothing can stop you!");
    break;
    case 7:
    uView.print("What are you waiting for!");
    break;
    case 8:
    uView.print("No pain, no gain!");
    break;
  }
  printInvader(4);
  uView.display();
  uView.setFontType(0); 
}

