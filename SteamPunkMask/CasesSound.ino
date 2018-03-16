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
