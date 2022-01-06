int button1 = 0;

int button2 = 0;

int button3 = 0;
int lastbutton1;
long lastdebounce1 = 0;
long lastdebounce3 = 0;
int lastbutton3;
long leddelay = 3000;
long led1 = -3000;
long led2 = -2000;
long led3 = -3000;
long led2delay = 2000;
long lastled1 = 0;
long lastled3 = 0;
long debouncedelay = 250;
long time1 = 0;
long button1time = 0;
void setup()
{
  
Serial.begin(9600);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  time1 = millis()-led1;
    
  button1 = digitalRead(12);
  button2 = digitalRead(11);
  button3 = digitalRead(10);
  ///////////////////////////////////////////////////////
   
  
  //////////////////////////////////////////
  int reading1 = button1;
    if(reading1 != lastbutton1){
      lastdebounce1 = millis();
    }
  if(millis()-lastdebounce1>debouncedelay){
    if(reading1 != button1){
      button1 = reading1;
    }
  }
 int reading3 = button3;
    if(reading3 != lastbutton3){
      lastdebounce3 = millis();
    }
  if(millis()-lastdebounce3>debouncedelay){
    if(reading3 != button3){
      button3 = reading3;
    }
  }
 
  if(digitalRead(4)== HIGH){
    if(button1 == LOW){
    lastled1 = millis();
    }
  }
  if (button1 == HIGH) {
    if(digitalRead(4)==LOW){
    led1= millis();
    }
  }
  
  if(digitalRead(4)==HIGH &&button1 == HIGH ){
    led1-=3000;
    
    }
  if(millis()-led1<leddelay){
    digitalWrite(4, HIGH);
    
  }else{
    digitalWrite(4, LOW);
    
  }
  ///////////////////////////////////////////////////////
  if(button2 == LOW&&digitalRead(4)==LOW&&digitalRead(2)==LOW){
    led2=millis();
    
  }
  
  if(millis()-led2<led2delay){
     if(millis()-led2>=0&&millis()-led2<500){
       digitalWrite(3,HIGH);
     }else if(millis()-led2>=500&&millis()-led2<1000){
       digitalWrite(3,LOW);
     }else if(millis()-led2>=1000&&millis()-led2<1500){
       digitalWrite(3,HIGH);
     }else{
     digitalWrite(3,LOW);
  }
    }
  ///////////////////////////////////////////////////////
 /* if (button3 == LOW&&digitalRead(4)==LOW) {
    
    led3= millis();
  }
  if(millis()-led3<leddelay){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
  if(digitalRead(2)==LOW &&button1 == LOW && millis()-lastled1 >bouncedelay){
    led3-=3000;
    
    }*/
   ////////////////////////////////////
    if(digitalRead(4)== HIGH){
    if(button1 == HIGH){
    lastled3 = millis();
    }
  }
  if (button3 == LOW&&digitalRead(4)==LOW) {
    if(digitalRead(2)==LOW){
    led3= millis();
    }
  }
  
  if(digitalRead(2)==HIGH &&button3 == LOW /*&& millis()-lastled1 >bouncedelay*/){
    led3-=3000;
    
    }
  if(millis()-led3<leddelay){
    digitalWrite(2, HIGH);
    
  }else{
    digitalWrite(2, LOW);
    
  }               
 /////////////////////////////////////
  Serial.print(button1);
  Serial.print(" ");
  Serial.print(button2);
  Serial.print(" ");
  Serial.print(button3);
  Serial.print(" ");
  Serial.print(led1);
  
  Serial.print("\n");
  
 //////////////////////////////////// 
 
  //////////////////////////////////
  
  
  /*if (button1 == HIGH) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }*/
  /*if (button2 == LOW) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }*/
  /*if (button3 == LOW) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }*/
  
}
