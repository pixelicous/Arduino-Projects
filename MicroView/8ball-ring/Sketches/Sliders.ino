void drawSliders {
  widget1 = new MicroViewGauge(15, 24, 0, 200, WIDGETSTYLE0);
  widget2 = new MicroViewGauge(48, 24, 0, 200, WIDGETSTYLE0 + WIDGETNOVALUE);

  spin(0, 200, 10, 100, update2widgets);

  delete widget1;
  delete widget2;
  
  widget1 = new MicroViewGauge(32, 24, -10, 150, WIDGETSTYLE1);
  
    spin(-10, 150, 8, 100, update1widget);
  
    delete widget1;
}

// Function to update widget1
void update1widget(int16_t val) {
  widget1->setValue(val);
}

// Function to update widget1 and widget2
void update2widgets(int16_t val) {
  widget1->setValue(val);
  widget2->setValue(val);
}

// Spin up, then down, through the values.
//
// For each value, call the update function and display the new screen.
void spin(int16_t lowVal, int16_t highVal, int16_t stepSize,
  unsigned long stepDelay, void (*drawFunction)(int16_t val)) {
  drawFunction(lowVal);
  uView.display();
  prevVal = lowVal;
  delay(1500);
  
  for (int16_t i = lowVal + stepSize; i <= highVal; i += stepSize) {
    drawFunction(i);
    uView.display();
    prevVal = i;
    delay(stepDelay);
    if ((i == 0) && (lowVal != 0)) { // pause briefly for a value of 0
      delay(750);
    }
  }
  
  delay(1500);
  
  for (int16_t i = highVal; i >= lowVal; i -= stepSize) {
    drawFunction(i);
    uView.display();
    prevVal = i;
    delay(stepDelay);
    if ((i == 0) && (lowVal != 0)) { // pause briefly for a value of 0
      delay(750);
    }
  }
  
  delay(1500);
}

