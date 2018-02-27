
//////////// SteamPunk Mask Ver 2.01 - dated 29.3.2016  
//////////// By: Netzer Rom 2014                     
//////////// Original fabrication date: 16.3.2014       
//////////// Software date: 15.2.2015                   


#include <avr/io.h> 
#include <avr/wdt.h>


////// Sound Sensor Function Variables 
    int volumeThreshold;
    int sensorSensitivity = 0; // Sound sensor sensitivity
    int sensorSensitivityBuffer = 15; // Sound sensor filter buffer
    int sensorSensitivityMax = 700; // Sound sensor sensitivity maximum filter
    int lastsoundButtonState;
    int soundDisplayMode = 0; // Sound mode display type
    int displayRunRandomMax = 30; // Max number for - Run amount for displays with random case picks
    int displayRunRandom = displayRunRandomMax; // Run amount for displays with random case picks

///// Silence Average checker
    const int volumeReadingsAmount = 30;     // How many readings to check for average
    int volumeReadings[volumeReadingsAmount];      // Readings array for the analog input
    int index = 0;                  // Index in the array
    int volumeTotal = 0;                  // Total readings
    int volumeAverage = 0;          // the average
    float volume=0,volumeLast=0,volumeLastMin=1024;



////// Set different Arduino pins as variables
    
    const int SoundSensor = A4;     // Sound Sensor Pin
    const int buttonTrigger = A3;     // Display or Sound activated button
    const int buttonPush = A2;     // Display Sequence chooser button
    
    const int ledTop =  12;      // Top Led
    const int ledBotR =  13;      // Bottom Right Led
    const int ledBotL =  11;      // Bottom Left Led
    
    const int ELRight1 =  2;      // 1st EL ring (RTL reading)
    const int ELRight2 =  3;      // 2nd EL ring
    const int ELRight3 =  4;      // 3rd EL ring
    const int ELRight4 =  5;      // EL in between pipes
    const int ELLeft1 =  6;      // 1st EL floating pipe (LTR reading)
    const int ELLeft2 =  7;      // 2nd EL floating pipe
    const int ELNose =  8;      // EL wire inside nose

//////////// LIGHT DISPLAY RELATED VARIABLES ////////////

int DisplayTime = 100; // Interval for displays
int DisplaySeque = 1;

    ////// Regular Mode - Display Variables
int runDisplayMode = 0;
int runDisplayCase = 1;
int runDisplayModeMax = 2;
int runDisplaySpeedDefault = 20;
int runDisplaySpeed = runDisplaySpeedDefault;
int runDisplayCaseMax = 6;

//////////// BUTTON VARIABLES //////////// 

int buttonTriggerState = 0;         // sound mode or not status
int lastbuttonTriggerState = 1;
int buttonPushState = 1;
int lastbuttonPushState = 1;

///// Animations Global variables
int ELSelected;
int LEDSelected;
int ELCounter = 50;
int ELDelay = 0; 
int ELDelayStart = 100;

//////////////////////////////////// SETUP //////////////////////////////////// 

void setup() {
  pinMode(SoundSensor, INPUT);     

  SilenceAvgCheck();
  
//DEBUG  Serial.begin(9600);  

////// Initialize OUTPUT
    ////// INITIALIZE EL PINS AS OUTPUTS
      pinMode(ELRight1, OUTPUT);  // channel A
      pinMode(ELRight2, OUTPUT);  // channel B
      pinMode(ELRight3, OUTPUT);  // channel C
      pinMode(ELRight4, OUTPUT);  // channel D 
      pinMode(ELLeft1, OUTPUT);  // channel E
      pinMode(ELLeft2, OUTPUT);  // channel E
      pinMode(ELNose, OUTPUT);  // channel F
    ////// INITIALIZE LED PINS AS OUTPUTS
      pinMode(ledTop, OUTPUT);
      pinMode(ledBotL, OUTPUT);
      pinMode(ledBotR, OUTPUT);
      
    // INITIALIZE BUTTONS AS INPUTS
      pinMode(buttonTrigger, INPUT);     
      pinMode(buttonPush, INPUT);   

////// INITIALIZE DISPLAY TO CHECK LIGHTS WORK
      //DEBUG  Serial.println("Initialising...");
        SequeLedRotate();
      
      ////// TURN ALL EL ON AND OFF
        for (int x = 2; x<=8; x++) {
          digitalWrite(x, HIGH);
          delay(DisplayTime);
        }
        for (int x = 2; x<=8; x++) {
          digitalWrite(x, LOW);
        }
      }

///////// MAIN LOOP /////////
void loop(){

  buttonTriggerState = digitalRead(buttonTrigger); ////// Read Trigger to choose mode
  if (buttonTriggerState == HIGH) { // If switch is on, sound mode
   ModeSound();
  }  
  else {
   if (lastbuttonTriggerState == 1) { TurnAllOff();}// If switched back to display state mode, first turn off all leds     
   ModeRegular();
  }
  
  ////// Set current buttons state as last status for edge detection (rising)
  lastbuttonPushState = buttonPushState;
  lastbuttonTriggerState = buttonTriggerState; 

}

///////// MAIN LOOP END /////////



///////// SOUND MODE
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

/////////////Regular Mode - Display Cases

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

////////////////////// Sound mode - Display modes
void soundAllRandom(){
   LEDSelected = random(11, 14); 
   digitalWrite(LEDSelected, HIGH);
   if (ELDelay > ELDelayStart) {     
     ELSelected = random(2, 8); 
     ELDelay = 0;
     ELDelayStart = random(5,16);
   }
   ELDelay += 1;
   digitalWrite(ELSelected, HIGH);  
   digitalWrite(ELNose, HIGH);
}

void soundScale(){
   ELCounter += 1;
   LEDSelected = random(11, 14);
   digitalWrite(LEDSelected, HIGH);
   for (int x=2;x<ELCounter;x++){
     ELSelected = x;      
   digitalWrite(ELSelected, HIGH);
   delay(10);
   }
   if (ELCounter == 50) {ELCounter = 1;}
}



//////////// FUNCTIONS ////////////

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

  

/////////////////////// LED FUNCTIONS
////// UTILITY FUNCTIONS

void TurnAllOff() {
    for(int x=2; x<=8; x++) {        //turn all EL wires off - reset for next loop
    digitalWrite(x, LOW);     
    }
    for(int x=11; x<=13; x++) {        //turn all EL wires off - reset for next loop
    digitalWrite(x, LOW);     
    }
    
  }
  
  void TurnAllOn() {
    for(int x=2; x<=8; x++) {        //turn all EL wires off - reset for next loop
    digitalWrite(x, HIGH);     
    }
    for(int x=11; x<=13; x++) {        //turn all EL wires off - reset for next loop
    digitalWrite(x, HIGH);     
    }
    
  }




/////////////////////// ANIMATION Functions
void SequeLedRotate() {
 digitalWrite(ledTop, HIGH);
 delay(runDisplaySpeed); 
 digitalWrite(ledTop, LOW);
 digitalWrite(ledBotL, HIGH);
 delay(runDisplaySpeed); 
 digitalWrite(ledBotL, LOW);
 digitalWrite(ledBotR, HIGH);
 delay(runDisplaySpeed);
 digitalWrite(ledBotR, LOW);
 delay(runDisplaySpeed);
}

void SequeELThree(int SequeTime) {
 digitalWrite(ELRight1, HIGH);
 delay(SequeTime); 
 digitalWrite(ELRight1, LOW);
 digitalWrite(ELRight2, HIGH);
 delay(SequeTime); 
 digitalWrite(ELRight2, LOW);
 digitalWrite(ELRight3, HIGH);
 delay(SequeTime);
 digitalWrite(ELRight3, LOW);
 delay(SequeTime);
}
  
void SequeELBlinker(){

   ELSelected = random(2, 9); 
   digitalWrite(ELSelected, HIGH);
   delay(runDisplaySpeed);
   digitalWrite(ELSelected, LOW);
}

void SequeELRandFade(){
   LEDSelected = random(11, 14); 
   for (int x = 0; x<255; x++) {
    analogWrite(ELSelected, HIGH); 
    delay(runDisplaySpeed);
   }
   delay(DisplayTime);
}   
   


void triangLED()  {
 digitalWrite(ledTop, HIGH);
 digitalWrite(ledBotL, HIGH);
 delay(runDisplaySpeed); 
 digitalWrite(ledTop, LOW);
 digitalWrite(ledBotL, LOW);
 delay(runDisplaySpeed); 
 digitalWrite(ledTop, HIGH);
 digitalWrite(ledBotR, HIGH);
 delay(runDisplaySpeed);
 digitalWrite(ledTop, LOW);
 digitalWrite(ledBotR, LOW);
 delay(runDisplaySpeed);
 digitalWrite(ledBotL, HIGH);
 digitalWrite(ledBotR, HIGH);
 delay(runDisplaySpeed); 
 digitalWrite(ledBotL, LOW);
 digitalWrite(ledBotR, LOW);
} 

 void triangLED2() {
 digitalWrite(ledTop, HIGH);
 digitalWrite(ledBotL, HIGH);
 delay(runDisplaySpeed); 
 digitalWrite(ledBotL, LOW);
 delay(runDisplaySpeed); 
 digitalWrite(ledBotR, HIGH);
 delay(runDisplaySpeed);
 digitalWrite(ledTop, LOW);
 delay(runDisplaySpeed);
 digitalWrite(ledBotL, HIGH);
 delay(runDisplaySpeed); 
 digitalWrite(ledBotR, LOW);
} 

void rightTubesSequencial() {
  digitalWrite(ELRight2, HIGH);
  delay(runDisplaySpeed/2);
  digitalWrite(ELRight3, HIGH);
  delay(runDisplaySpeed/2);
  digitalWrite(ELRight4, HIGH);
  delay(runDisplaySpeed);
  digitalWrite(ELRight2, LOW);
  digitalWrite(ELRight3, LOW);
  digitalWrite(ELRight4, LOW);
  delay(runDisplaySpeed);
}
  

void showZigZag() {
   digitalWrite(ELRight1, HIGH);
   digitalWrite(ELRight3, HIGH);
   digitalWrite(ELLeft1, HIGH);
   delay(runDisplaySpeed/2);  
   digitalWrite(ELRight1, LOW);
   digitalWrite(ELRight3, LOW);
   digitalWrite(ELLeft1, LOW);
   digitalWrite(ELRight2, HIGH);
   digitalWrite(ELRight4, HIGH);
   digitalWrite(ELLeft2, HIGH);
   delay(runDisplaySpeed/2);     
   digitalWrite(ELRight2, LOW);
   digitalWrite(ELRight4, LOW);
   digitalWrite(ELLeft2, LOW);   
}
