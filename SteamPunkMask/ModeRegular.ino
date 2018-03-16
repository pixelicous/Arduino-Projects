void ModeRegular() {
  int buttonPushState;
  
  buttonPushState = digitalRead(buttonPush);      
  if (buttonPushState != lastbuttonPushState) { // Rise detector prevent multi press
   if (buttonPushState == HIGH) {
    runDisplaySpeed += 15; // Decrease playing speed
    if (runDisplaySpeed > DisplayTime*2) {
     triangLED2();
     runDisplaySpeed = runDisplaySpeedDefault;}          
    }
   }
   else  if (buttonPushState == lastbuttonPushState) {
    int held = 0;
    while (digitalRead(buttonPush) == HIGH && held < 81)
     {
      delay(100);
      held++;
     }
    if (held == 80){ //IF PRESSED FOR 8 SECONDS
     wdt_enable(WDTO_15MS); //RESET ARDUINO
     wdt_reset();
    }
    else if (held > 40){ //IF PRESSED FOR LONGER THAN 4 SECOND BUT LOWER THAN 6 SECONDs
     triangLED2();
     runDisplayMode = 0;
     displayRunRandom = displayRunRandomMax;
    }
    else if (held > 15){ //IF PRESSED FOR LONGER THAN 1.5 SECOND BUT LOWER THAN 3 SECONDs
     triangLED2();
     runDisplayMode += 1; // increment Mode
     displayRunRandom = displayRunRandomMax;
     if (runDisplayMode > runDisplayModeMax) {   //If display mode is greater than amount of display modes
      runDisplayMode = 0;
      TurnAllOff();
      //debug
      for (int x = 0; x<=3; x++) {
       digitalWrite(ledTop, HIGH);
       delay(DisplayTime);
       digitalWrite(ledTop, LOW);
       delay(DisplayTime);
      }//debug
     }
     for(int x=2; x<=8; x++) {digitalWrite(x, LOW);}        //turn all EL wires off - reset for next loop           
    }
  }
      
      
  switch (runDisplayMode) { //MODE REGULAR DISPLAY MODES - MAX VARIABLE - runDisplayModeMax
   case 0: //Mode Regular - run through cases randomlly  
    displayRunRandom += 1;
    if (displayRunRandom < displayRunRandomMax) { runDisplaySeque(); }
    else
    {
      runDisplayCase = random(1,runDisplayCaseMax);
      displayRunRandom = 0;
    }
    break;
   case 1: //Mode Regular - Run through cases
    runDisplayCase += 1;
    if (runDisplayCase > runDisplayCaseMax) {             // if sequence is greater than last case, restart from 1st sequence
     runDisplayCase = 1;
     TurnAllOff();
     //DEBUG
         for (int x = 0; x<=3; x++) {
          digitalWrite(ledTop, HIGH);
          delay(DisplayTime);
          digitalWrite(ledTop, LOW);
          delay(DisplayTime);
         }
     //DEBUG
    }
    runDisplaySeque();
    break;
   case 2:
    runDisplaySeque();
    break;
   }
}
