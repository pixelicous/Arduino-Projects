void ModeSound() { 
  int soundButtonState;

  
        soundButtonState = digitalRead(buttonPush); // Chec
      // BUTTON PRESSED CHANGE MODE
      if (soundButtonState != lastsoundButtonState) { // Rise detector prevent multi press
        if (soundButtonState == HIGH) {
          sensorSensitivity += sensorSensitivityBuffer; // Increase sound sensitivity
          if (sensorSensitivity > sensorSensitivityMax) {
          triangLED2();
          sensorSensitivity = 0;}
          
        }
      }
       else  if (soundButtonState == lastsoundButtonState) {
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
           else if (held > 60){ //IF PRESSED FOR LONGER THAN 6 SECOND BUT LOWER THAN 10 SECONDs
            sensorSensitivity=0;
            SilenceAvgCheck();
           }
          else if (held > 35){ //IF PRESSED FOR LONGER THAN 3.5 SECONDS BUT LOWER THAN 10 SECONDs
            triangLED2();
            sensorSensitivity = 0; 
           }
          else if (held > 15){ //IF PRESSED FOR LONGER THAN 1.5 SECONDS BUT LOWER THAN 5 SECONDs
            triangLED2();
            soundDisplayMode += 1;
            if (soundDisplayMode > 2) {soundDisplayMode = 0;}
           }
      }
          
      lastsoundButtonState = soundButtonState; // Save last button state in sound mode
      
  volumeThreshold = volumeAverage+sensorSensitivity; //Threshold set
  volume = analogRead(SoundSensor); // Reads the value from the Sound Sensor
//DEBUG - FINAL5- NOT SURE IF TO REMOVE-----  if (volume > volumeLast){  volumeLast=volume;}  // Get MAX
//DEBUG - FINAL5- NOT SURE IF TO REMOVE-----  if( volume < volumeLast){  volumeLastMin=volume;}  // Get MIN
  
  //delay(1);
  TurnAllOff(); //debug-final5
  //TURN LEDS ON  ACCORING TO SOUND MODE
  if (volume>volumeThreshold) {
    switch (soundDisplayMode) {
     case 0:
     TurnAllOn();
     break;
     case 1:
      soundAllRandom();
     break;
     case 2:
      soundScale();
     break;
    }
   delay(10);
  }
  else {
    TurnAllOff();
    } 
}

void SilenceAvgCheck() {
 // Primary Silence Average check
  for (int x =0; x<volumeReadingsAmount; x++){
     volume = analogRead(SoundSensor); // Reads the value from the Analog PIN A0
 
  volumeTotal= volumeTotal - volumeReadings[index];         // subtract the last reading:
  volumeReadings[index] = analogRead(SoundSensor);               // read from the sensor:  
  volumeTotal= volumeTotal + volumeReadings[index];         // add the reading to the total:
  index = index + 1;                                        // advance to the next position in the array:  

  if (index >= volumeReadingsAmount)  { index = 0;}  // if we're at the end of the array wrap around to the beginning: 
  volumeAverage = volumeTotal / volumeReadingsAmount;           // calculate the average:
  }

  volumeThreshold = volumeAverage+sensorSensitivity; // set volume threshold  
}
