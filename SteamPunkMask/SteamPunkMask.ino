
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









