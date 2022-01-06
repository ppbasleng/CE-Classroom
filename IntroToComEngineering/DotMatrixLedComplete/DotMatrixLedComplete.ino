#include "LedControl.h"

///////////////////////////////JOYSTICK GLOBAL VARIABLE//////////////////////////////////////////////////////////
int up_button = 2;
int down_button = 4;
int left_button = 5;
int right_button = 3;
int start_button = 6;
int select_button = 7;
int joystick_button = 8;
int joystick_axis_x = A0;
int joystick_axis_y = A1;
int buttons[] = {up_button, down_button, left_button, right_button, start_button, select_button, joystick_button};
////////////////////////////////////////////////////////////////////
LedControl lc=LedControl(11,13,10,4); // CLK,DIN,CS,Number of LED Module
unsigned long delaytime=10; // time to updates of the display
///////////////////////////Ammo Global Variable///////////////////////////////
bool ammostatus;
#define N 2 //define for max ammo on screen
#define NON -2//define for empty array element
int ammo_coord_x[N];
int ammo_coord_y[N];
int ammo_delay=0;
int initdelay=2;
//////////////////////////Game Mode Variable///////////////////////
int boss[7]={1,3,5,7,9,11,13};
int player[2]={1,3};
int life=3,bosslife=8;
int playersw=0,bosssw=0;
int bbeat=1,pbeat=1;
///////////////////////////Ship Global Variable//////////////////////
int x=7,y=3;

///////////////////////////Alien Global Variable////////////////////
#define depth 3
#define alive 1
#define death 0
#define maxalienammo 3
int alien_horde[8][8];
int ax=0,ay=1,tempay=1,alien_delay=0;
int alienammo_x[maxalienammo],alienammo_y[maxalienammo];
int ranalien=0;
bool alienammostatus;
////////////////////////////////////////////////////////////////////
/////////////////////////draw alien////////////////////////////
void initalien(int x,int y)
{
  lc.setLed(0,x,y,true);
  lc.setLed(0,x,y+1,true);
  lc.setLed(0,x,y+2,true); 
  lc.setLed(0,x,y+3,true); 
  lc.setLed(0,x,y+4,true); 
  lc.setLed(0,x,y+5,true); 
  
  lc.setLed(0,x+1,y+1,true); 
  lc.setLed(0,x+1,y+4,true); 
  /*for(int i=0;i<depth;i++)
  {
    for(int j=1;j<=6;j++)
    {
      alien_horde[i][j]=alive;
      lc.setLed(0,i,j,true);
    }
  }*/
}
void rmalienship(){             //remove alien ship
  lc.setLed(0,ax,ay,false);
  lc.setLed(0,ax,ay+1,false);
  lc.setLed(0,ax,ay+2,false); 
  lc.setLed(0,ax,ay+3,false); 
  lc.setLed(0,ax,ay+4,false); 
  lc.setLed(0,ax,ay+5,false); 
 
  lc.setLed(0,ax+1,ay+1,false); 
  lc.setLed(0,ax+1,ay+4,false);
}

void randomalienposition(){ //random move alien ship (left or right)
  int arandom;
  arandom =random(0,10);
  if(arandom==9){
    tempay=random(0,3);
    if(tempay!=ay){
      rmalienship();
      ay=tempay;
      initalien(ax,ay);
      
    }else{
      tempay=ay;
    }
    
  }
}
void initalienammoarr() // generate alien ammo
{
  for(int i=0;i<maxalienammo;i++)
  {
    alienammo_x[i]=NON;
    alienammo_y[i]=NON;
  }
}
/////////////////////////////////////////////////alien ammo control/////////////////////////////////////////////////
void alienammocontrol()   //alien ammo control
{
    
  
    
    for(int i=0;i<maxalienammo;i++)
    {
      if(alienammo_x[i]!=NON&&alienammo_y[i]!=NON){
            remove_1_obj(alienammo_x[i],alienammo_y[i]);//remove old ammo
      }
    }
    for(int i=0;i<maxalienammo;i++)
    {
      if(alienammo_x[i]!=NON&&alienammo_y[i]!=NON)
      {
        if(inScreen(alienammo_x[i],alienammo_y[i])&&ammo_delay<5)
        {
            draw_ammo(alienammo_x[i],alienammo_y[i]);//draw new ammo
            //lc.setLed(0,ax,ay,true);
        }else if(inScreen(alienammo_x[i],alienammo_y[i])&&ammo_delay==5)
        {
            draw_ammo(++alienammo_x[i],alienammo_y[i]);//draw new ammo
            //lc.setLed(0,ax,ay,true);
        
        }
        else
        {
          remove_1_obj(alienammo_x[i],alienammo_y[i]);//out of screen
          alienammo_x[i]=NON;//release
          alienammo_y[i]=NON;//release
        }
      }
    }
    
    
    if(ammo_delay>=5){
    lifepoint();
    
    ammo_delay=0;
    }
    ammo_delay++;
}
//////////////////////////////////////return all object//////////////////////////////////
void returnobject(){ //draw ship again
  draw_ship(x,y);
  initalien(ax,ay);
}
//////////////////////////////////////////////////////////////////////alien ammo control/////////////////////////////////////
void initalienammo()  //generate alien ammo
{
  
  int x_space,y_space;
  if(!Havespace(maxalienammo,alienammo_x,alienammo_y,x_space,y_space))
  {
    return ;
  }
  /////random ammo/////
  int randvar=random(0,2);
  /////random ammo/////
  if(randvar==0)
  {
    alienammo_x[x_space]=ax+1;
    alienammo_y[y_space]=ay+1;
  }
  else
  {
    alienammo_x[x_space]=ax+1;
    alienammo_y[y_space]=ay+4;
  }
}
///////////////////////////////////game config///////////////////
void lifepoint(){         //player life
  for(int i=0;i<=3;i++){
    if(alienammo_x[i]==7){
      life-=1;
      
    }
  }
}
void lose(){              //when player lose //player life reach 0
  returnobject();
  digitalWrite(9,LOW);
  while(true){
    removeship();
    delay(500);
    draw_ship(x,y);
    delay(500);
  }
}
void win(){             // when player win //boss life reach 0
  returnobject();
  digitalWrite(12,LOW);
  for(int i =0;i<=3;i++){
   rmalienship();
   delay(500);
   initalien(ax,ay); 
   delay(500);
  }
  for(int x=0;x<=7;x++){
    for(int y =0;y<=7;y++){
      lc.setLed(0,x,y,false);
    }
  }
  draw_ship(x,y);
  while(x>0){
    removeship();
    draw_ship(--x,y);
    delay(200);
  }
   for(int x=0;x<=7;x++){
    for(int y =0;y<=7;y++){
      
      lc.setLed(0,x,y,false);
      
      
    }
  }
  while(true){
    for(int x=0;x<=7;x++){
    for(int y =0;y<=7;y++){
      lc.setLed(0,x,y,true);
      lc.setLed(0,x-1,y,false);
      if(x==0){
        lc.setLed(0,7,y,false);
      }
      delay(100);
    }
  }
  }
  
}

void heartbeat(){                 //control player's life led
  if(digitalRead(9)==HIGH){
    digitalWrite(9,LOW);
  }else if(digitalRead(9)==LOW){
    digitalWrite(9,HIGH);
  }
}
void bossbeat(){                //control boss's life led
  if(digitalRead(12)==HIGH){
    digitalWrite(12,LOW);
  }else if(digitalRead(12)==LOW){
    digitalWrite(12,HIGH);
  }
}
/////////////////////////////alien/////////////////////////
void setup() 
{
int devices=lc.getDeviceCount(); // find no of LED modules
//we have to init all devices in a loop
  randomSeed(analogRead(0));
  pinMode(9,OUTPUT);
  pinMode(12,OUTPUT);
  
  digitalWrite(9,HIGH);
  digitalWrite(12,HIGH);
  Serial.begin(9600);
  
  for(int address=0;address<devices;address++) //init dotmatrix
  { // set up each device
    lc.shutdown(address,false);
    lc.setIntensity(address,8);
    lc.clearDisplay(address);
  }
  for (int i=0; i < 7; i++)//init button
  {
   pinMode(buttons[i], INPUT);
   digitalWrite(buttons[i], HIGH);
  }
  draw_ship(x,y);
  ammostatus=false;
  alienammostatus=false;
  init_ammo_arr();
  initalienammoarr();
  initalien(ax,ay);
}
void init_ammo_arr()            //generate player ammo
{
  for(int i=0;i<N;i++)
  {
    ammo_coord_x[i]=NON;
    ammo_coord_y[i]=NON;
  }
}
void draw_ship(int x,int y)     //draw player ship
{
  lc.setLed(0,x,y,true);
  lc.setLed(0,x,y+1,true);
  lc.setLed(0,x,y-1,true);
}
int isKey_hit()                 //joystick button reciever
{
  if(digitalRead(up_button)==LOW)
  {
   return up_button;
  }
  /*else if(digitalRead(right_button)==LOW)
  {
    return right_button;
  }*/
  else if(digitalRead(down_button)==LOW)
  {
    return down_button;
  }
 /* else if(digitalRead(left_button)==LOW)
  {
    return left_button;
  }*/
  else if(digitalRead(up_button)==LOW)
  {
    return up_button;
  }else if(map(analogRead(joystick_axis_x), 0, 1000, -1, 1)==-1){
    return left_button;
  }
  else if(map(analogRead(joystick_axis_x), 0, 1000, -1, 1)==1){
    return right_button;
  }
  return false;
}
void removeship()                         //remove old ship
{
  lc.setLed(0,x,y,false);
  lc.setLed(0,x,y+1,false);
  lc.setLed(0,x,y-1,false);
}
void Ship_movement_control(int pressed_button)    //control ship position
{
  if(pressed_button==left_button&&y-2>=0)
  {
    removeship();
    draw_ship(x,--y);
  }
  if(pressed_button==right_button&&y+2<=7)
  {
    removeship();
    draw_ship(x,++y);
  }
 
}
bool isFire(int pressed_button)     //check if player shot
{
  if(pressed_button==up_button)
  {
    return true;
  }
  return false;
}
bool Havespace(int index_num,int *ammoarr_x,int *ammoarr_y,int &x_space,int &y_space) //check ammo space(not fired ammo)
{
  for(x_space=0,y_space=0;x_space<index_num,y_space<index_num;x_space++,y_space++)
  {
    if(ammoarr_x[x_space]==NON&&ammoarr_y[y_space]==NON)
    {
      return true;
    }
  }
  return false;
}
void remove_1_obj(int x,int y)  //remove something
{
  lc.setLed(0,x,y,false);
}
void draw_ammo(int x,int y)   //draw new ammo
{
  lc.setLed(0,x,y,true);
}
void isCollision()///collision of ammo to ammo    // check collision of player's ammo and boss's ammo
{
  for(int i=0;i<N;i++)// ally ship ammo index
  {
    for(int j=0;j<maxalienammo;j++)//enemy ship ammo index
    {
      if(ammo_coord_x[i]!=NON&&ammo_coord_y[i]!=NON&&alienammo_x[j]!=NON&&alienammo_y[j]!=NON)
      {
        if(ammo_coord_x[i]-1==alienammo_x[j]&&ammo_coord_y[i]==alienammo_y[j])
        {
          remove_1_obj(ammo_coord_x[i],ammo_coord_y[i]);
          remove_1_obj(alienammo_x[j],alienammo_y[j]);
          ammo_coord_x[i]=NON;
          ammo_coord_y[i]=NON;
          alienammo_x[j]=NON;
          alienammo_y[j]=NON;
          bosslife--;
        }
        else if(ammo_coord_x[i]==alienammo_x[j]&&ammo_coord_y[i]==alienammo_y[j])
        {
          remove_1_obj(ammo_coord_x[i],ammo_coord_y[i]);
          remove_1_obj(alienammo_x[j],alienammo_y[j]);
          ammo_coord_x[i]=NON;
          ammo_coord_y[i]=NON;
          alienammo_x[j]=NON;
          alienammo_y[j]=NON;
          bosslife--;
      }
    }
  }
  
}
}
void initial_ammo_coord_arr()       //generate player's ammo 
{
  int x_space,y_space;
  if(!Havespace(N,ammo_coord_x,ammo_coord_y,x_space,y_space))
  {
    return ;
  }
  ammo_coord_x[x_space]=x;
  ammo_coord_y[y_space]=y;
}
void ammo_control()     //ammo move controling
{  
 
    
    for(int i=0;i<N;i++)
    {
      if(ammo_coord_x[i]!=NON&&ammo_coord_y[i]!=NON){
            remove_1_obj(ammo_coord_x[i],ammo_coord_y[i]);//remove old ammo
      }
    }
    for(int i=0;i<N;i++)
    {
      if(ammo_coord_x[i]!=NON&&ammo_coord_y[i]!=NON)
      {
        if(inScreen(ammo_coord_x[i],ammo_coord_y[i]))
        {
          
        
         draw_ammo(--ammo_coord_x[i],ammo_coord_y[i]);//draw new ammo
          
        }
        else
        {
          remove_1_obj(ammo_coord_x[i],ammo_coord_y[i]);//out of screen
          ammo_coord_x[i]=NON;//release
          ammo_coord_y[i]=NON;//release
        }
      }
    }
  

}
bool inScreen(int x,int y)    // check if ammo collide with wall
{
  if(x>=0&&x<=7&&y>=0&&y<=7)return true;
  return false;
}
bool ammostatus_update(int *ammo_x,int *ammo_y,int index_num)
{
  for(int i=0;i<index_num;i++)
  {
    if(ammo_x[i]!=NON&&ammo_y[i]!=NON)
    {
      return true;
    }
  }
  return false;
}
void debug_monitor()    //for debugging
{
  //Serial.print(ammostatus);
  for(int i=0;i<depth;i++)
  {
    for(int j=1;j<=6;j++)
    {
      Serial.print(alien_horde[i][j]);
    }
    Serial.println();
  }
  Serial.println();
}
void loop() //main loop
{
int devices=lc.getDeviceCount();// find no of LED modules
//Serial.println(devices);
  
  int pressed_button=isKey_hit();
  delay(100);
  
 // debug_monitor();
  randomalienposition();
  if(ammo_delay==4){
  ranalien=random(0,10);
  if(ranalien==4){
    initalienammo();
  }
  }
   isCollision();
  
  Serial.print(life);     //for debugging
  Serial.print(bosslife);
   Serial.print(playersw);
    Serial.println(bosssw);
  if(pressed_button)
  {
    Ship_movement_control(pressed_button);
    if(isFire(pressed_button))
    {
      //initial ammo coord//////////
      initial_ammo_coord_arr();
    }
  }
  ammostatus=ammostatus_update(N,ammo_coord_x,ammo_coord_y);
  alienammostatus=ammostatus_update(maxalienammo,alienammo_x,alienammo_y);
  if(ammostatus)
  {
    /////Ammo Control function//////
    ammo_control();
  }
  
  if(alienammostatus)
  {
    //ammo control
    
    alienammocontrol();
   
    
  }
 
  if(life<3){
    playersw++;
    if(playersw>player[life-1]){
      playersw=0;
      heartbeat();
      
    }
  
  }
  if(bosslife<8){
    bosssw++;
    if(bosssw>boss[bosslife-1]){
      bossbeat();
      bosssw=0;
    }
  }
  if(life<=0){
        lose();
      }
  if(bosslife==0){
    win();
  }
  
  
  Serial.print(alien_delay);  // for debugging
  
  returnobject();
}
