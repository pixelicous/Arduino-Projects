void answers() {
  int randomNumber;
    uView.clear(PAGE);
  uView.setCursor(0, 0);
  randomSeed(analogRead(0));
  randomNumber = random(1,7);

  switch (randomNumber) {
    case 1:
    uView.print("The world is yours!");
    break;
    case 2:
    uView.print("Absolutely!");
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

