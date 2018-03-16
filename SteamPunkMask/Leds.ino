
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
