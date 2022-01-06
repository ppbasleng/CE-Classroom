#include "ST7735_TEE.h"

TEE_ST7735 lcd(9, 10, 11, 12, 13); //Arduino  csk,sda,A0,rst,cs
int hour = 0, minute = 0, second = 0;
int temph10,temph1,tempm10,tempm1,temps10;
char hr[3],m[3],s[3];
bool clockstop=false;
bool printstop=false;
char clockshow[8];
String inputstring="";
int timesetupcount = 0;
void setup()
{
    //lcd.init(lcd.HORIZONTAL);
    lcd.init(lcd.VERTICAL);
    lcd.fillScreen(BLACK);
    Serial.begin(9600);
    noInterrupts();           /* disable all interrupts             */
  TCCR1A  = 0;
  TCCR1B  = 0;
  TCNT1   = 3036;           /* preload timer 65536-16MHz/256/1Hz  */
  TCCR1B |= (1 << CS12);    /* 256 prescaler                      */
  TIMSK1 |= (1 << TOIE1);   /* enable timer overflow interrupt    */
  interrupts();   
  clockstop=true;
}
/*void receiveinput(){
  if(Serial.available){
    
  }
}*/
void timecontrol(){
  clockshow[0]=hr[0];
  clockshow[1]=hr[1];
  clockshow[3]=m[0];
  clockshow[4]=m[1];
  clockshow[6]=s[0];
  clockshow[7]=s[1];

  clockshow[2]=':';
  clockshow[5]=':';
  

}
void cleartime(){

}
void inttostr(){
  hr[0]=hour/10+'0';
  hr[1]=hour%10+'0';
  m[0]=minute/10+'0';
  m[1]=minute%10+'0';
  s[0]=second/10+'0';
  s[1]=second%10+'0';
}
void drawtime(){
  
  lcd.drawChar(15,20, clockshow[0],WHITE,2); 
  lcd.drawChar(30,20, clockshow[1],WHITE,2); 
  lcd.drawChar(40,20, clockshow[2],WHITE,2); 
  lcd.drawChar(50,20, clockshow[3],WHITE,2); 
  lcd.drawChar(65,20, clockshow[4],WHITE,2); 
  lcd.drawChar(75,20, clockshow[5],WHITE,2);
  lcd.drawChar(85,20, clockshow[6],WHITE,2); 
  lcd.drawChar(100,20, clockshow[7],WHITE,2); 
}


ISR(TIMER1_OVF_vect)        // interrupt service routine
{
  TCNT1 = 3036;     
  if(!clockstop){
  lcd.drawChar(100,20,clockshow[7],BLACK,2);
  if(second%10==9){
    lcd.drawChar(85,20,clockshow[6],BLACK,2);
  }
  Serial.println(second++);
  
  if (second > 59) {
    second = 0; minute++;
    lcd.drawChar(65,20,clockshow[4],BLACK,2);
  }
   if (minute%10 == 0&&second==0) {
   lcd.drawChar(50,20,clockshow[3],BLACK,2);
  }
  
  if (minute > 59) {
    minute = 0; hour++;
    lcd.drawChar(30,20,clockshow[1],BLACK,2);
  }
  if(hour%10==0&&minute==0&&second==0){
    lcd.drawChar(15,20,clockshow[0],BLACK,2);
  }
  if (hour > 23) {
    hour = 0;
    lcd.drawChar(15,20,clockshow[0],BLACK,2);
  }
  }
  
  
  inttostr();
  timecontrol();
  drawtime();
  if(clockstop){
      lcd.drawString(20,60,"CLOCK",RED,3);
      lcd.drawString(20,85,"SETUP",RED,3);
      setupclock();
     
      
   }
  
}
void adjust(){
  lcd.drawChar(15,20, clockshow[0],BLACK,2); 
  lcd.drawChar(30,20, clockshow[1],BLACK,2); 
  lcd.drawChar(50,20, clockshow[3],BLACK,2); 
  lcd.drawChar(65,20, clockshow[4],BLACK,2); 
  lcd.drawChar(85,20, clockshow[6],BLACK,2); 
  lcd.drawChar(100,20, clockshow[7],BLACK,2); 
  lcd.drawString(20,60,"CLOCK",BLACK,3);
  lcd.drawString(20,85,"SETUP",BLACK,3);
  hour = (inputstring[0]-'0')*10+(inputstring[1]-'0');
  minute = (inputstring[2]-'0')*10+(inputstring[3]-'0');
  second = (inputstring[4]-'0')*10+(inputstring[5]-'0');
 
}
void setupclock(){
  while(Serial.available()){
    char readserial = (char)Serial.read();
    inputstring+=readserial;
    
    if(readserial==10){
      Serial.print(inputstring);
      adjust();
      clockstop=false;
       inputstring = "";
    }
    
  }
}
void loop(){
  

  
   
   delay(500);
 
   
}
