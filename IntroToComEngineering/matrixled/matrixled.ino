#include "LedControl.h"
LedControl lc=LedControl(13,11,10,1); // CLK,DIN,CS,Number of LED Module
unsigned long delaytime=500; // time to updates of the display
void setup() {
  int devices=lc.getDeviceCount(); // find no of LED modules
  pinMode(7, OUTPUT);
  //we have to init all devices in a loop
}
void loop() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      delay(delaytime);
      lc.setLed(0,row,col,false);
    }
  }
  digitalWrite(7, HIGH);
  delay(delaytime);
  digitalWrite(7, LOW);
  delay(delaytime);
}
