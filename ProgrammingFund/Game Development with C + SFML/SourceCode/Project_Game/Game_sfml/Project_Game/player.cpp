#include "entity.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>




class player : public entity
{
public:
	/////////////////////////vector//////////////////////////////////
	float x = 120, y = 360;
	//////////////////////////stat////////////////////////////////
	int str = 5, agi = 5, dex = 5, vit = 5,statp=0;
	int levelcap[14] = {2,3,4,5,6,7,8,9,10,11,13,15,18,21}, levelnow = 1,exp=0;
	/////////////////////////status///////////////////////////////////
	float movement_speed = 20;
	float tumblespeed = 0;
	float attack_damage = 10;
	float maxhp = 100;
	float currenthp = 100;
	float maxstamina = 100;
	float currentstamina = 100;
	int arrowremain = 0;
	int hppotremain = 0;
	int armed = 0;
	bool getbow = false;
	int iframe = 0;
	float hpregen = 0;
	float staregen = 0;
	bool stabperk = false;
	bool firstaidperk = false;
	bool slashperk = false;
	//////////////////////////counter/////////////////////////////
	int counter = 0;
	int movecounter = 0;
	int walking_buffer = 0;
	int direction = 0;
	int aimcount = 0;
	int atkdelay = 0;
	int shotdelay = 0;
	bool fired = false;
	int blinkcounter = 0;
	int blinking = rand()%30;
	int hppotbounce = 0;
	//////////////////////////////jump state/////////////////////////
	int jumpcounter = 0;
	int jumpspeed = -10;
	int jumpbuffer = 0;
	int fcount=0;
	////////////////////////////animation/////////////////////////////
	bool atk=false;
	bool tumble=false;
	bool block = false;
	bool moving = false;
	bool aim = false;
	bool shot = false;
	bool interact = false;
	bool jump = false;
	bool dead = false;
	bool interactthing = false;
	int deadtime = 0;
	////////////////////////////soundeffect////////////////////////
	
	
	/////////////////////////damagecalculator///////////////////////

	//////////////////////////function/////////////////////////////
	player();
	void keyboard_input();
	void minimove();
	void move();
	void movey();
	void update_action();
	void updateposition();
	void soundcontrol();
	void reset();

};
player::player()
{
	
	rect.setSize(Vector2f(160, 160));
	rect.setFillColor(Color::Color(200,100,0,120));
	rect.setOrigin(80, 80);
	sprite.setOrigin(80, 80);
}
void player::keyboard_input() {
	if (!dead) {
		if (interact&&!interactthing) {
			interact = false;
		}
		aim = false;
		block = false;
		if (Keyboard::isKeyPressed(Keyboard::W)&&hppotbounce==0&&currenthp<maxhp&&hppotremain>0) {
			hpregen += maxhp * 40 / 100;
			hppotremain -= 1;
			hppotbounce = 1;
			buffer2.loadFromFile("res/sound/player/potion.wav");
			sound2.setBuffer(buffer2);
			sound2.play();
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && !interactthing && !tumble && armed == 12 && !atk&&!aim&&!shot) {
			block = true;
			movecounter = 0;
			counter = 0;
			

		}
		if (Keyboard::isKeyPressed(Keyboard::D) && !shot && !interactthing && !block && !tumble && armed == 12 && !jump&&currentstamina>=15)
		{
			if (!atk && atkdelay == 0) {
				

				atk = true;
				movecounter = 0;
				counter = 0;
				atkdelay = 3;

			}
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift) && !shot && !interactthing && !atk&&!jump&&currentstamina>=15)
		{
			if (!tumble && x > 85 && x < 725) {


				tumble = true;
				aim = false;
				shot = false;
				iframe = 1;
				movecounter = 0;
				counter = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (x < 55) {
				moving = false;
			}
			else if (!atk && !block && !tumble && !block && !shot && !interactthing) {
				moving = true;
			}

			if (!atk) {
				direction = 2;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (x > 755) {
				moving = false;
			}
			else if (!atk && !block && !tumble && !block && !shot && !interactthing) {
				moving = true;
			}

			if (!atk) {
				direction = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && !interactthing && getbow && shotdelay == 0&&arrowremain>0) {
			movecounter = 0;
			aim = true;
			shot = true;
			atkdelay = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::E)&&!interactthing) {
			interact = true;
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && !shot && !interactthing && !block && !tumble && armed == 12 && !jump && !atk&&currentstamina>=10) {
			currentstamina -= 10;
			jumpcounter = 0;
			jump = true;

		}
		if (atkdelay > 0) {
			atkdelay++;

		}
		if (atkdelay > 12) {
			atkdelay = 0;
		}
		if (shotdelay > 0) {
			shotdelay++;

		}
		if (shotdelay > 20) {
			shotdelay = 0;
		}
		if (iframe > 0) {
			iframe++;
		}
		if (iframe > 8) {
			iframe = 0;
		}
		if (hppotbounce > 0) {
			hppotbounce++;
		}
		if (hppotbounce > 16) {
			hppotbounce = 0;
		}
	}
	
}

void player::update_action()
{
		sprite.setPosition(rect.getPosition());
		if (dead) {
			/*if (atk&&counter > 3) {
				counter = 0;
				sprite.move(75 + (direction * 15), 125);
				atk = false;
			}*/
			sprite.setTextureRect(IntRect((24 + (direction * 2)) * 160, 0, 160, 160));
			iframe = 1;
			counter = 0;
		}
		else {
			if (jump && y < 440) {
				sprite.setTextureRect(IntRect((43 * 160) + (340 * 8) + ((direction + jumpcounter) * 160 + ((1 - direction) * (jumpcounter + 1) * 5)), 0, 160, 190));
				jumpbuffer++;
				if (jumpbuffer == 2) {
					jumpcounter++;
					jumpbuffer = 0;
				}
				if (jumpcounter > 1) {
					jumpcounter = 1;
				}

				if (x > 700 || x < 55) {
					moving = false;

				}


			}
			else if (interact&&interactthing) {
				moving = false;
				sprite.setTextureRect(IntRect(42 * 160, 0, 160, 160));
				counter++;
				if (counter == 8) {
					counter = 0;
					interact = false;
					interactthing = false;
					/*switch (armed) {
					case 0: armed = 12; getbow = true; break;
					case 12: armed = 0;  break;
					}*/
				}
			}
			else if (atk) {
				if (counter == 0) {
					
					
					currentstamina -= 15;
				}
				sprite.move(-75 - (direction * 15), -125);
				sprite.setTextureRect(IntRect((43 * 160) + ((direction * 2 + counter) * 340), 0, 340, 375));
				counter++;
				if (counter > 3) {
					counter = 0;
					atk = false;

				}

			}
			else if (tumble) {
				if (counter == 0) {
					currentstamina -= 15;
				}
				sprite.setTextureRect(IntRect((24 + counter + (direction * 2)) * 160, 0, 160, 160));
				counter++;
				if (counter > 3) {
					counter = 0;
					tumble = false;

				}
			}

			else if (moving) {

				sprite.setTextureRect(IntRect((armed + 4 + direction * 2 + movecounter) * 160, 0, 160, 160));
				walking_buffer++;
				if (walking_buffer == 2) {
					movecounter++;
					walking_buffer = 0;
				}
				moving = false;
				if (movecounter > 3) {
					movecounter = 0;
				}

			}
			else if (block) {
				sprite.setTextureRect(IntRect((40 + direction / 2) * 160, 0, 160, 160));
			}
			else if (aim) {

				if (aimcount > 1) {
					aimcount = 1;
				}
				sprite.setTextureRect(IntRect((aimcount + 32 + direction * 2) * 160, 0, 160, 160));
				aimcount++;
			}
			else if (!aim && shot) {

				sprite.setTextureRect(IntRect((aimcount + 32 + direction * 2) * 160, 0, 160, 160));
				aimcount++;
				if (aimcount == 4) {
					aimcount = 0;
					shot = false;
					atkdelay = atkdelay + 8;
				}

			}

			else {
				blinkcounter++;
				if (blinkcounter > blinking - 1) {
					sprite.setTextureRect(IntRect((armed + direction + 1) * 160, 0, 160, 160));
					if (blinkcounter > blinking) {
						blinkcounter = 0;
						blinking = 20 + rand() % 50;
					}
				}
				else {
					sprite.setTextureRect(IntRect((armed + direction) * 160, 0, 160, 160));
				}
			}
		}
}
void player::move(){
	 if (tumble) {
		rect.move((1 - direction) * (4-counter)*movement_speed/2, 0);
		
	 }
	else if(moving){

		rect.move((1-direction)*movement_speed, 0);
		
	}
	
}
void player::minimove() {
	if (tumble) {
		rect.move((1 - direction) * (4 - counter) * movement_speed / 4, 0);
	}
	else if (moving) {
		rect.move((1 - direction) * movement_speed/2, 0);
	}
}
void player::updateposition() {
	
	this->x = rect.getPosition().x;
	this->y = rect.getPosition().y;
}
void player::movey() {
	if (jump) {
		fcount++;
		rect.move(0, (6-fcount)*jumpspeed);
		if (fcount == 11) {
			fcount = 0;
			jump = false;
		}
	}
	
	
}
void player::soundcontrol() {
	if (moving && (movecounter) % 2 != 1 && !jump) {
		buffer.loadFromFile("res/sound/player/move.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
	if (tumble) {
		buffer.loadFromFile("res/sound/player/move.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
	if (atk && counter == 0) {
		buffer.loadFromFile("res/sound/player/atk.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
	if (jump && fcount == 1) {
		buffer.loadFromFile("res/sound/player/jump.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
	if (interact && interactthing&&counter==0) {
		
		buffer.loadFromFile("res/sound/player/get.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
}
void player::reset() {
	/////////////////////////vector//////////////////////////////////
	 x = 120, y = 360;
	//////////////////////////stat////////////////////////////////
	 str = 5, agi = 5, dex = 5, vit = 5, statp = 0;
	levelnow = 1, exp = 0;
	/////////////////////////status///////////////////////////////////
	 movement_speed = 20;
	 tumblespeed = 0;
	 attack_damage = 10;
	 maxhp = 100;
	 currenthp = 100;
	 maxstamina = 100;
	 currentstamina = 100;
	 arrowremain = 0;
	 hppotremain = 0;
	 armed = 0;
	 getbow = false;
	 iframe = 0;
	 hpregen = 0;
	 staregen = 0;
	 stabperk = false;
	 firstaidperk = false;
	 slashperk = false;
	//////////////////////////counter/////////////////////////////
	 counter = 0;
	 movecounter = 0;
	 walking_buffer = 0;
	 direction = 0;
	 aimcount = 0;
	 atkdelay = 0;
	 shotdelay = 0;
	 fired = false;
	 blinkcounter = 0;
	 blinking = rand() % 30;
	 hppotbounce = 0;
	//////////////////////////////jump state/////////////////////////
	 jumpcounter = 0;
	 jumpspeed = -10;
	 jumpbuffer = 0;
	 fcount = 0;
	////////////////////////////animation/////////////////////////////
	 atk = false;
	 tumble = false;
	 block = false;
	 moving = false;
	 aim = false;
	 shot = false;
	 interact = false;
	 jump = false;
	 dead = false;
	 interactthing = false;
	 deadtime = 0;

}
