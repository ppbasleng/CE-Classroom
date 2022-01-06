#include <SoftwareSerial.h>
String inputString = ""; // a string to hold incoming data
SoftwareSerial mySerial(8,9);

#define lowcalibrate 4
#define highcalibrate 5
#define pressed LOW
const unsigned int X_AXIS_PIN = 2; 
//const unsigned int Y_AXIS_PIN = 1; 
//const unsigned int Z_AXIS_PIN = 0; 
const unsigned int NUM_AXES = 1; 
const unsigned int PINS[NUM_AXES] = { X_AXIS_PIN}; 
const unsigned int BUFFER_SIZE = 16; 
const unsigned int BAUD_RATE = 9600; 
int buffers[NUM_AXES][BUFFER_SIZE]; 
int buffer_pos[NUM_AXES] = { 0 }; 
int lowcali_temp,highcali_temp;
int angle;

void setup()
{
  pinMode(lowcalibrate,INPUT_PULLUP);
   pinMode(highcalibrate,INPUT_PULLUP);
   lowcali_temp=0;
   highcali_temp=0;
Serial.begin(9600);
mySerial.begin(9600);
}

int get_axis(const int axis) 
{
buffers[axis][buffer_pos[axis]] = analogRead(PINS[axis]); 
buffer_pos[axis] = (buffer_pos[axis] + 1) % BUFFER_SIZE; 
long sum = 0; 
for (unsigned int i = 0; i < BUFFER_SIZE; i++) 
sum += buffers[axis][i]; return round(sum / BUFFER_SIZE); 
}

int get_x() 
{
  return get_axis(0); 
} 
bool isfullcollect()
{
  if(lowcali_temp!=0&&highcali_temp!=0)
  {
    return true;
  }
  return false;
}

void loop()
{
     if(angle<0){
      angle=-angle;
     }
     mySerial.println(angle);
    angle=map(get_x(),lowcali_temp,highcali_temp,-90,90);
  if(isfullcollect())
  {
    
    
  }
 // Serial.print(digitalRead(lowcalibrate));
  //Serial.print(digitalRead(highcalibrate));
Serial.println(get_x()); 
Serial.print(" "); 
  if(digitalRead(lowcalibrate)==pressed)
  {
    lowcali_temp=get_x();
  }
   else if(digitalRead(highcalibrate)==pressed)
  {
    highcali_temp=get_x();
  }
  Serial.print(lowcali_temp);
  Serial.print(" ");
  Serial.print(highcali_temp);
  Serial.print(" ");
  Serial.println(angle);
  
  delay(800);
}
