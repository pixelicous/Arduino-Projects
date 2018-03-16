void runDisplaySeque(){
 // Check Mode, light accordingly
 switch (runDisplayCase) {  // Maximum case variable - runDisplayCaseMax
  case 1:
   SequeLedRotate();
   rightTubesSequencial();
   break;
  case 2:
   for (int x = 2; x<=8; x++) {
    digitalWrite(x, HIGH);
    delay(DisplayTime);
    digitalWrite(x, LOW);
   }
   break;
  case 3:
   SequeELBlinker();
   break;
  case 4:
    triangLED();
   break;
  case 5:
    triangLED2();
   break;
  case 6:
  showZigZag();
  break;
  }
}

