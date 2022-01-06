
int bitsegment[6]={121,36,48,25,18,2};
int i = 4,n=0,m=-1,j;

void setup()
{
  // define pin modes
 Serial.begin(9600);
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);
 pinMode(11,INPUT);
 pinMode(12,INPUT);
 for(i=4;i<=10;i++){
  digitalWrite(i,HIGH);
 }
 for(i=0;i<=7;i++){
    digitalWrite(i+4,(bitsegment[n])>>(i)& 0x01);
    }
  digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
}

void loop() 
{

  
  guess();
 
  start();
    Serial.print(m);
  Serial.println(digitalRead(12));
 randomSeed(analogRead(A5));
 
 
  
  

}
void guess(){
  if(digitalRead(11)==HIGH){
    delay(150);
    n++;
    if(n>5){
      n=0;
    }
    
    for(i=0;i<=7;i++){
    digitalWrite(i+4,(bitsegment[n])>>(i)& 0x01);
    }
  
  
  } 
 
}
void start(){
    if(digitalRead(12)==HIGH){
      delay(150);
       rng();
      //m=0;//fortesting
    m = random(0,6);
    for(i=0;i<=7;i++){
    digitalWrite(i+4,(bitsegment[m])>>(i)& 0x01);
    }
    delay(1000);
      if(n==m){
        yes();
        
      }else{
        nope();
       
      }
    }

}
void rng(){
    for(j=0;j<4;j++){
    for(i=4;i<=10;i++){
      digitalWrite(i,HIGH);
    }
    if(digitalRead(2)==HIGH){
       digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    }else{
       digitalWrite(3,LOW);
    digitalWrite(2,HIGH);
    }
    digitalWrite(4,LOW);
    digitalWrite(7,LOW);
    delay(200);
    digitalWrite(5,LOW);
    digitalWrite(8,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    delay(200);
    digitalWrite(6,LOW);
    digitalWrite(9,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(8,HIGH);
   
    delay(200);
    digitalWrite(3,HIGH);
    }
}
void yes(){
     
   
    for(i=4;i<=10;i++){
      digitalWrite(i,HIGH);
    }
 
    for(j=0;j<=5;j++){
      for(i=4;i<=9;i++){
      digitalWrite(i,LOW);
      delay(30);
      if(i==5){
        digitalWrite(9,HIGH);
      }
      if(i==4){
        digitalWrite(8,HIGH);
      }
      digitalWrite(i-2,HIGH);
      delay(30);
      if(digitalRead(2)==HIGH){
         digitalWrite(2,LOW);
   
      }else{
        digitalWrite(2,HIGH);
      }
    }
      
    }
    digitalWrite(8,HIGH);
    delay(30);
    digitalWrite(9,HIGH);
    
    delay(200);
    n=0;
    for(i=0;i<=7;i++){
    digitalWrite(i+4,(bitsegment[n])>>(i)& 0x01);
    }
    m=-1;
}
void nope(){
for(i=4;i<=10;i++){
      digitalWrite(i,LOW);
    }    

    digitalWrite(3,LOW);
    delay(250);
digitalWrite(4,HIGH);
delay(250);
digitalWrite(5,HIGH);   
digitalWrite(9,HIGH);
digitalWrite(3,HIGH);
delay(250);
digitalWrite(10,HIGH);
delay(250);
digitalWrite(6,HIGH);  
digitalWrite(8,HIGH);
digitalWrite(3,LOW);
delay(250);
digitalWrite(7,HIGH);

  


    delay(250);
    digitalWrite(3,HIGH);
  m=-1;
  for(i=0;i<=7;i++){
    digitalWrite(i+4,(bitsegment[n])>>(i)& 0x01);
    }

}
