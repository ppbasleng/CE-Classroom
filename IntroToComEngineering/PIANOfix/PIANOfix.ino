
int notes[]={262,294,330,349,392,440,494};
int button = 0;


int recorded_button[300];
int tempbutton;
int recordedtime [300];
char timei;
char bi = 0;
unsigned long stime;
int notetime;
long int bounce;

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
}

void loop() {
 
  if(digitalRead(10)==0){
    delay(250);
   while(digitalRead(10)!=0){
      
     recording();
     playing();
  Serial.print(button);
  Serial.print("time>>");
  Serial.println(notetime/10);
   }
    delay(250);
  }
  if(digitalRead(11)==0){

    for(int i =0;i<sizeof(recorded_button)/2;i++){
      delay((recordedtime[i]));
      if(recorded_button[i]==0){
      noTone(13);
      }else{
      tone(13,notes[(recorded_button[i]-1)]);
      }
      Serial.print(recorded_button[i]);
      Serial.print("time>>");
      Serial.println(recordedtime[i]);
    }
  }
  
  
  
  
  
  
  
  
  
  
 if(digitalRead(2)==0){
    tone(13,notes[0]);
   
  }if(digitalRead(3)==0){
    tone(13,notes[1]);
 
  }if(digitalRead(4)==0){
    tone(13,notes[2]);
 
  }if(digitalRead(5)==0){
    tone(13,notes[3]);
  
  }if(digitalRead(6)==0){
    tone(13,notes[4]);
  
  }if(digitalRead(7)==0){
    tone(13,notes[5]);
 
  }if(digitalRead(8)==0){
    tone(13,notes[6]);

  }if(digitalRead(2)==1&&digitalRead(3)==1&&digitalRead(4)==1&&digitalRead(5)==1&&digitalRead(6)==1&&digitalRead(7)==1&&digitalRead(8)==1){
  noTone(13);

  }
    //delay(10);// for simulation performance
}


void playing(){
   if (button != tempbutton)
  {
    
    notetime = (millis() - stime);

    recordedtime[timei] = notetime;
    timei++;

    stime = millis();
    if(button!=0&&tempbutton!=0){
      recordedtime[timei]= 0 ;
      timei++;
    }
  }
 
  
  if(digitalRead(2)==0){
    tone(13,notes[0]);
   
  }if(digitalRead(3)==0){
    tone(13,notes[1]);
 
  }if(digitalRead(4)==0){
    tone(13,notes[2]);
 
  }if(digitalRead(5)==0){
    tone(13,notes[3]);
  
  }if(digitalRead(6)==0){
    tone(13,notes[4]);
  
  }if(digitalRead(7)==0){
    tone(13,notes[5]);
 
  }if(digitalRead(8)==0){
    tone(13,notes[6]);

  }if(digitalRead(2)==1&&digitalRead(3)==1&&digitalRead(4)==1&&digitalRead(5)==1&&digitalRead(6)==1&&digitalRead(7)==1&&digitalRead(8)==1){
  noTone(13);

  }
 }

void recording(){

  tempbutton=button;
   if(digitalRead(2)==0){
    button=1;
   
  }if(digitalRead(3)==0){
    button=2;
  
  }if(digitalRead(4)==0){
    button=3;

  }if(digitalRead(5)==0){
    button=4;

  }if(digitalRead(6)==0){
    button=5;

  }if(digitalRead(7)==0){
    button=6;

  }if(digitalRead(8)==0){
    button=7;

  }if(digitalRead(2)==1&&digitalRead(3)==1&&digitalRead(4)==1&&digitalRead(5)==1&&digitalRead(6)==1&&digitalRead(7)==1&&digitalRead(8)==1){
  noTone(13);
    button=0;
  }
    if (button != tempbutton && tempbutton != 0)
  {
    recorded_button[bi] = tempbutton; 
    bi++;
    recorded_button[bi] = 0;
    bi++;
    
  }
 
}
 
  
  
