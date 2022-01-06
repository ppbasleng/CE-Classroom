#include "entity.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"player.h"
#include"projectile.h"
#include<iostream>
#include<math.h>
extern int scorep;

class player;
class projectile;
class bot3 : public entity
{
public:
	player* player;
	projectile* projectile;
	Sprite axe;
	////////////////////////////////position/////////////////////////////
	int x = 880, y = 400;
	////////////////////////////////status//////////////////////////////
	float movement_speed = 20;
	//float sptodis = 0;
	float attack_damage = 30;
	float maxhp=150;
	float currenthp = maxhp;
	float maxar=100;
	float currentar = maxar;
	bool dead = false;
	int deadtime = 0;

	/////////////////////////////bar control////////////////////////
	float regenrate = 0.003125;
	float percentmax=700;
	float percenthp=percentmax;
	float percentar = percentmax;
	
	int currenttime = 0;
	int bptime = 0;
	int fcount = 0;
	///////////////////////////counter/////////////////////////////////
	int counter = 0;
	int barcounter = 0;
	int movecounter = 0;
	int walkbuffer = 0;
	int direction = 2;
	int tmpdirection = 2;
	int actdelay = 16;
	int actcnt = 0;
	int pi = 1;
	int atkdelay = 0;
	int signcounter = -1;
	int signdelay = 0;
	int knockback = 0;
	int knockdirection = 0;
	int selfknockback = 0;
	int selfknockdirection = 0;
	int parryeffect = -1;
	int jumpcount = 0;
	int ranmoveout = 4 + rand() % 16;
	int moveoutcount = 0;
	int moveoutdirection = 0;
	int warnsign = 0;
	///////////////////////////bot reaction//////////////////////////
	int reaction = 24;
	int reactioncount = 0;
	int cooldown = 0;
	int rancooldown = 36 + rand() % 16;
	int parry = 0;
	int parrycount = 0;
	int parrylimit = 1+rand() % 3;
	int randomatk = 0;
	//////////////////////////bot axe control///////////////////////
	int shot = 0;
	int shoted = 0;
	int axegravity = 0;
	int axedirection = 0;
	float axespeed = 0;
	float axex = 0;
	float axey = 0;
	int axespin = 0;
	///////////////////////////standposition////////////////////////////
	bool backstab = false;
	
	int chkstate = 0;
	///////////////////////////animation////////////////////////////////
	bool detect = false;
	bool atking = false;
	bool atk = false;
	int atk2 = 0;
	bool moving = false;
	bool stuning = false;
	bool movingtoatk = false;
	////////////////////////autostate//////////////////////////////////
	bool movetoplayer = false;
	bool inrange = false;

	/////////////////////////////damage calculate////////////////////////
	int distance = 1500;
	int pjtshot = 0;
	int distancepjt = 1000;
	int botdpjt = 0;
	int slashed = 0;
	int distanceslash = 1000;
	/////////////////////////function//////////////////////////////////
	bot3();
	void calculate(class player* player);
	void control(class player* player);
	void move();
	void update_action();
	void updateposition();
	void barcontrol();
	void signcontrol();
	void checkdamage(class player* player);
	void checkpjtdamage(class projectile* pjt);
	void soundcontrol();
};
bot3::bot3()
{
	caution.loadFromFile("res/sign.png");
	stun.loadFromFile("res/stun.png");
	
	axe.setTextureRect(IntRect(0, 0, 80, 80));
	axe.setOrigin(40, 40);
	axe.setPosition(-400, -400);
	signspr.setPosition(-400, 0);
	rect.setSize(Vector2f(160, 240));
	rect.setPosition(x, y);
	rect.setFillColor(Color::Color(100,0,30,180));
	rectbar1.setFillColor(Color::Color(0,0,0,180));
	bar1.setFillColor(Color::Color(255,0,0));
	rectbar2.setFillColor(Color::Color(0,0,0,180));
	bar2.setFillColor(Color::Color(169, 169, 169,180));

	rectbar1.setOutlineColor(Color::Color(255, 255, 255, 120));
	rectbar1.setOutlineThickness(2);
	rectbar2.setOutlineColor(Color::Color(255,255,255,120));
	rectbar2.setOutlineThickness(2);
	rectbar1.setOrigin(percentmax / 2, 0);
	rectbar2.setOrigin(percentmax / 2, 0);
	bar1.setOrigin(percentmax / 2, 0);
	bar2.setOrigin(percentmax / 2, 0);
	effect.setPosition(-400, -400);
	//signspr.setTextureRect(IntRect(0, 0, 80, 80));
	rect.setOrigin(80,120);
	sprite.setOrigin(80,120);
	signspr.setOrigin(40, 40);
	
}
void bot3::control(class player* player) {
	if (!dead) {
		
		if (distance < 1200 && distance>-1200) {
			detect = true;


			if (!stuning) {

				if (distance > -600 && distance < 600&&x<760&&x>40) {
					inrange = true;
					moving = false;
				}
				else {
					inrange = false;
					if (cooldown == 0) {
						moving = true;
					}
					if (distance<100 && distance>-100 && moveoutcount == 0 && !atk && cooldown < 10) {
						moveoutcount = 1;
					}
				}


				if (((cooldown > rancooldown/2 || cooldown == 0)||atk2==1||(atking&&counter<3)||movingtoatk)) {
					if (this->x >= player->x) {
						this->direction = 2;
					}
					else {

						this->direction = 0;
					}
					srand(time(NULL));
				}

				if (inrange) {
					if (cooldown == 0 && !moving && !atk && !atking && moveoutcount == 0 && atk2 != 2 && !movingtoatk && signcounter == -1) {
						srand(time(NULL));
						randomatk = rand() % 2;
						//randomatk = 1;
						switch (randomatk) {
						case 0: movingtoatk = true; break;
						case 1: atk2 = 1; break;
						default: break;
						}


					}
				}
				


				if (movingtoatk) {
					moving = true;
				}
				if (atking || atk || atk2 == 2) {
					moving = false;
					//movingtoatk = false;
				}
			}
		}
		

		if (cooldown > 0 && !atk && !stuning&&atk2==0) {
			cooldown++;

		}
		if (cooldown > rancooldown) {
			cooldown = 0;
			shot = false;
			rancooldown = 36 + rand() % 16;
		}
		
	}
}

void bot3::update_action()
{

	sprite.setPosition(rect.getPosition());
	if (dead) {
		sprite.setTextureRect(IntRect((direction / 2) * 160, 0, 160, 240));
	}
	else {
		if (stuning) {
			atk = false;
			atking = false;
			atk2 = 0;
			counter = 0;
			atkdelay = 0;
			signcounter = 0;
			sprite.setTextureRect(IntRect((direction / 2) * 160, 0, 160, 240));
			if (!shot) {
				axe.setPosition(-400, -400);
			}
		}
		else if (atking) {
			
			sprite.setTextureRect(IntRect((6 * 160) + ((direction * 2 + counter) * 320), 0, 320, 320));
			sprite.move(-40-(direction*40), -80);

			if (counter >= 0 && atkdelay <= 2) {
				atkdelay++;
			}
			if (atkdelay > 2) {
				counter++;
				atkdelay = 0;
			}
			if (counter > 3) {
				counter = 3;
			}
			
			
		}
		else if (atk2 == 2) {
			
			sprite.move(-40 - (direction * 40), -80);
			sprite.setTextureRect(IntRect((6 * 160) + ((direction * 2 + counter) * 320), (shot*2)*320, 320, 320));

			counter++;
			if (counter > 3 && shot == 0) {
				item.loadFromFile("res/bot3axe.png");
				axe.setTexture(item);
				counter = 0;
				if (shoted == 0) {
					axespeed = distance / 16;
					shot = 1;
					axedirection = direction;
					axex = x + (1 - axedirection) * 50;
					axe.setPosition(axex, y - 25);
					axe.setTextureRect(IntRect(axespin * 160, 160 * (direction / 2), 160, 160));
					shoted = 1;
					buffer2.loadFromFile("res/sound/bot3/axethrow.wav");
					sound2.setBuffer(buffer2);
					sound2.play();
				}
			}
			if (counter > 3 && shot==1) {
				counter = 0;
				
				atk2 = 0;
			}
		

		
		}
		else if (atk) {
			sprite.move(-40 - (direction * 40), -80);
			sprite.setTextureRect(IntRect((6 * 160) + ((direction * 2 + counter) * 320), 320, 320, 320));
			
			counter++;
			
			if (counter > 3 && atkdelay <= 2) {
				counter = 3;
				atkdelay++;
				
			}
			if (counter > 3) {
				
				counter = 0;
				atkdelay = 0;
				atk = false;
				cooldown = 1;
			}

		}

		else if ((moving || movecounter != 0) && !stuning&&direction!=1) {

			sprite.setTextureRect(IntRect(320+( direction + movecounter) * 160, 0, 160, 240));
			walkbuffer++;
			if (walkbuffer == 4) {
				movecounter++;
				walkbuffer = 0;
			}

			if (movecounter > 1) {
				movecounter = 0;
			}

		}
		else {
			sprite.setTextureRect(IntRect((direction / 2) * 160, 0, 160, 240));


		}
	}
	if (shoted > 0) {
		shoted++;
	}
	if (shoted > 16) {
		shoted = 0;
	}
}
void bot3::move() {
	if (shot == 1) {
		axegravity++;
	}
	else {
		axegravity = 0;
	}
	axe.move(0, -(8 - axegravity) * 10);
	axe.move(-1 * axespeed * shot, 0);
	axe.setTextureRect(IntRect(axespin * 160, 160 * (direction / 2), 160, 160));
	axespin++;
	if (axespin > 3) {
		axespin = 0;
	}
	if (axey >= 400) {
		std::cout << axey << std::endl;
		atk2 = 0;
		shot = 0;
		axe.setPosition(-400, -400);
	}
	if (dead) {

		rect.move((1 - selfknockdirection) * movement_speed,(4-jumpcount)*-5);
		jumpcount++;
		if (!shot) {
			axe.setPosition(-400, -400);
		}
	}
	else {
		
		
		
		if (moving && movecounter ==1 &&!atk) {

			rect.move((1 - direction) * movement_speed, 0);
			moving = false;
			if (movingtoatk&&distance<=200&&distance>=-200) {
				movingtoatk = false;
				atking = true;
			}
		}
	}
}
void bot3::calculate(class player* player)
{
	distance = (this->x)-(player->x);
	
	if (distance > 0) {
		if (player->direction == 0 && this->direction == 0) {
			backstab = true;
		}
		else {
			backstab = false;
		}
		
	}
	else if (distance < 0) {
		if (player->direction == 2 && this->direction == 2) {
			backstab = true;
		}
		else {
			backstab = false;
		}
		
		
	}

}
void bot3::updateposition() {
	this->x = rect.getPosition().x;
	this->y = rect.getPosition().y;
	axex = axe.getPosition().x;
	axey = axe.getPosition().y;
}
void bot3::checkdamage(class player* player){
	
	
	if (shot) {
		botdpjt = sqrt(pow(axex - player->x, 2) + pow(axey - player->y,2));
		if (player->atk && player->counter == 3&&botdpjt<200&&(axedirection!=player->direction)) {
			scorep += 300;
			axe.setPosition(-400, -400);
			shot = false;
			buffer2.loadFromFile("res/sound/effect/parry.wav");
			sound2.setBuffer(buffer2);
			sound2.play();
		}
		else if (botdpjt < 80 ) {
			
			
				if (player->iframe == 0) {
					player->currenthp -= attack_damage;
					knockback = 1;
					knockdirection = axedirection;
					scorep -= 100;
					axe.setPosition(1000, 800);
					shot = false;
					buffer2.loadFromFile("res/sound/effect/axeshot.wav");
					sound2.setBuffer(buffer2);
					sound2.play();
				}
			
		}
	}
	if (parry ==0&& player->atk && atk&&counter>1&&player->counter>1&&
		(((distance <= 195 && distance > 0) && player->direction == 0 && direction == 2) ||
		((distance >= -195 && distance < 0) && player->direction == 2 && direction == 0))) {
			
			currentar -= player->attack_damage ;
			if (currentar <= 0) {
				currentar = 0;
				regenrate = 0;
				bptime = 1;
			}

			player->staregen += 10;
			selfknockback = 3;
			selfknockdirection = player->direction;
			counter = 0;
			atk = false;
			efx.loadFromFile("res/parryeffect.png");
			effect.setTexture(efx);
			parry = 1;
			cooldown = 10+rand()%6;
			parrycount++;
			parryeffect = 0;
			if (parrycount>=parrylimit) {
				parrycount = 0;
				parrylimit = 1+rand() % 3;
				cooldown = 1;
			}
			buffer2.loadFromFile("res/sound/effect/parry.wav");
			sound2.setBuffer(buffer2);
			sound2.setVolume(100.f);
			sound2.play();
			scorep += 200;
			effect.setPosition(x + (1 - direction) * 50, y);
	}
	else if(parry==0) {
		if (player->atk && player->counter == 3) {
			if (((distance <= 195 && distance > 0) && player->direction == 0) || ((distance >= -195 && distance < 0) && player->direction == 2)) {
				if (currentar > 0) {
					if (backstab) {


						if (player->stabperk) {
							currenthp -= player->attack_damage * 3 / 4;
							if (bptime == 0) {
								currentar -= player->attack_damage * 9 / 4;
							}
							parryeffect = 0;
							efx.loadFromFile("res/stabperk.png");
							effect.setTexture(efx);
							effect.setPosition(rect.getPosition().x + -1 * (1 - direction) * 10, y);
						}
						else {
							currenthp -= player->attack_damage / 2;
							if (bptime == 0) {
								currentar -= player->attack_damage * 3 / 2;
							}
						}
					}
					else {
						currenthp -= player->attack_damage / 4;
						if (bptime == 0) {
							currentar -= player->attack_damage * 3 / 4;
						}
					}

					if (currentar <= 0) {
						currentar = 0;
						regenrate = 0;
						bptime = 1;
					}
				}
				else {
					if (backstab) {
						if (player->stabperk) {
							currenthp -= player->attack_damage * 3;
							parryeffect = 0;
							efx.loadFromFile("res/stabperk.png");
							effect.setTexture(efx);
							effect.setPosition(rect.getPosition().x + -1 * (1 - direction) * 10, y);
						}
						else {
							currenthp -= player->attack_damage * 2;
						}

					}
					else {
						currenthp -= player->attack_damage;
					}
				}

				if (atk || atking) {
					selfknockback = 3;

				}
				else if (!stuning) {
					selfknockback = 3;

				}
				selfknockdirection = player->direction;
				buffer2.loadFromFile("res/sound/effect/hit.wav");
				sound2.setBuffer(buffer2);
				sound2.setVolume(75.f);
				sound2.play();
			}

		}else if (atk && counter == 3 && atkdelay == 2) {
			if ((((distance <= 200 && distance > 0) && direction == 2) ||
			((distance >= -200 && distance < 0) && direction == 0)) && player->iframe == 0) {
				if (player->block && direction != player->direction) {
					player->buffer2.loadFromFile("res/sound/player/block.wav");
					player->sound2.setBuffer(player->buffer2);
					player->sound2.play();
					player->currenthp -= attack_damage / 8;
					if (player->currentstamina > attack_damage) {
						player->currentstamina -= attack_damage;
						knockback = 2;
					}
					else {
						player->currenthp -= (7/8*attack_damage - player->currentstamina);
						player->currentstamina = 0;
						knockback = 1;
					}

				}
				else {
					player->buffer2.loadFromFile("res/sound/player/axehit.wav");
					player->sound2.setBuffer(player->buffer2);
					player->sound2.play();
					player->currenthp -= attack_damage;
					knockback = 1;
				}
				if (player->currenthp < 0) {
					player->currenthp = 0;
				}

				knockdirection = direction;
				scorep -= 100;
			}
		}
	}
	if (selfknockback > 0) {
		rect.move((1 - selfknockdirection) * (4 - selfknockback) * 15, 0);
		selfknockback++;
	}
	if (selfknockback > 2) {
		selfknockback = 0;
	}
	if (knockback > 0) {
		
		player->rect.move((1 - knockdirection) * (3 - knockback) * 25,0);
		int playerpos = player->rect.getPosition().x;
		if (playerpos < 40) {
			player->rect.setPosition(40, player->y);
		}
		else if (playerpos > 740) {
			player->rect.setPosition(740, player->y);
		}
			knockback++;
	}
	if (knockback > 2) {
		knockback = 0;
	}
	if (parry > 0) {
		parry++;
	}
	if (parry > 3) {
		parry = 0;
	}
}

void bot3::checkpjtdamage(class projectile* pjt ) {
	distanceslash = pjt->lx - this->x;
	distancepjt = pjt->x - this->x;
	if (!dead) {
		if (pjt->isfired && pjtshot == 0) {
			if ((distancepjt > 0 && pjt->direction == 0 && distancepjt < 90) || (distancepjt < 0 && pjt->direction == 1 && distancepjt>-90)) {
				if (currentar > 0) {
					currentar -= pjt->atk * 2;
					pjtshot = 1;
					if (currentar <= 0) {
						currentar = 0;
						regenrate = 0;
						bptime = 1;
					}

				}
				else if (currentar == 0 && stuning) {
					pjtshot = 1;
					bptime = 1;
				}
				currenthp -= pjt->atk / 2;
				selfknockdirection = pjt->direction * 2;
				selfknockback = 3;
				buffer2.loadFromFile("res/sound/effect/axeshot.wav");
				sound2.setBuffer(buffer2);
				sound2.play();
			}
		}
		if (pjt->isslash && slashed == 0) {
			if ((distanceslash > 0 && pjt->ldirection == 0 && distanceslash < 90) || (distanceslash < 0 && pjt->ldirection == 1 && distanceslash>-90)) {
				if (currentar > 0) {
					currentar -= pjt->atk * 3 / 2;
					slashed = 1;
					if (currentar <= 0) {
						currentar = 0;
						regenrate = 0;
						bptime = 1;
						selfknockdirection = pjt->ldirection * 2;
						selfknockback = 3;
					}

				}
				else if (currentar == 0 && stuning) {
					slashed = 1;
					bptime = 1;
				}
				currenthp -= pjt->atk * 2 / 3;

				buffer2.loadFromFile("res/sound/effect/arrowshot.wav");
				sound2.setBuffer(buffer2);
				sound2.play();
			}
		}
	}
	if (slashed > 0) {
		slashed++;
	}
	if (slashed > 16) {
		slashed = 0;
	}
	if (pjtshot > 0) {
		pjtshot++;

	}
	if (pjtshot > 16) {
		pjtshot = 0;
	}
}
void bot3::barcontrol() {
	if (currentar < maxar) {
		currentar += regenrate;
		if (currentar > maxar) {
			currentar = maxar;
			regenrate = 0.003125;
		}
		if (bptime > 0) {
			if (!dead) {
				bptime++;
			}
			stuning = true;
			moveoutcount = 0;
			cooldown = 1;
			counter = 0;
		}
		if (bptime > 36) {
			if (bptime == 37) {
				signcounter = -1;
			}
			regenrate = 8.1;
			stuning = false;
			if (currentar >= maxar) {
				currentar = maxar;
				regenrate = 0.003125;
				bptime = 0;
			}
		}
	}
	if (currenthp <= 0&&!dead) {
		currenthp = 0;
		dead = true;
		deadtime = 1;
		regenrate = 0;
		counter = 0;
		atkdelay = 0;
		atk = false;
		
	}
	if (deadtime > 0) {
		deadtime++;
	}
	percenthp = currenthp / maxhp * percentmax;
	percentar = currentar / maxar * percentmax;

	rectbar1.setPosition(400 , 540);
	rectbar1.setSize(Vector2f(percentmax, 20));
	bar1.setPosition(400, 540);
	bar1.setSize(Vector2f(percenthp, 20));
	rectbar2.setPosition(400 , 565);
	rectbar2.setSize(Vector2f(percentmax, 15));
	bar2.setPosition(400, 565);
	bar2.setSize(Vector2f(percentar, 15));

	if (signcounter != -1) {
		signspr.setPosition(x - (1 - direction) * 5, y - 140);
	}
	else {
		signspr.setPosition(-400,  1000);
	}
	signspr.setTextureRect(IntRect(signcounter * 80, 0, 80, 80));
}
void bot3::soundcontrol() {
	if (dead&&deadtime==2) {
		buffer.loadFromFile("res/sound/bot3/dead.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
	else {
		if (detect) {
			if (atk && counter == 2) {
				buffer.loadFromFile("res/sound/bot3/atk.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			else if (moving && (movecounter) % 2 == 1 && !stuning&&!dead) {
				buffer.loadFromFile("res/sound/bot3/move.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
		}
	}
}
void bot3::signcontrol() {
	if (!dead) {
		if (stuning) {
			signcounter = 0;
			caution.loadFromFile("res/stun.png");
			signspr.setTexture(caution);
			signspr.setTextureRect(IntRect(signcounter * 80, 0, 80, 80));
		}
		else if (atking) {

			caution.loadFromFile("res/sign.png");
			signspr.setTexture(caution);
			

			
			if (signcounter < 10) {
				signcounter++;
			}
			if (signcounter == 10) {
				signdelay++;
				
				signcounter++;
			}else if (signcounter > 10) {
				if (signdelay < 8) {
					signcounter = 10;
				}
				else if (signdelay >= 8) {
					atk = true;
					atking = false;
					signdelay = 0;
					counter = 0;
					signcounter = -1;
				}
			}

			
		}
		else if (atk2==1) {
			caution.loadFromFile("res/sign.png");
			signspr.setTexture(caution);



			if (signcounter < 10) {
				signcounter++;
			}
			if (signcounter == 10) {
				signdelay++;

				signcounter++;
			}
			else if (signcounter > 10) {
				if (signdelay < 8) {
					signcounter = 10;
				}
				else if (signdelay >= 8) {
					atk2=2;
					cooldown = 1;
					signdelay = 0;
					counter = 0;
					signcounter = -1;
				}
			}
		}
		else {
			signcounter = -1;
		}
	}
	else {
		signcounter = -1;
	}
	effect.setTextureRect(IntRect(parryeffect * 160, 0, 160, 160));
	if (parryeffect > -1) {
		parryeffect++;
	}
	if (parryeffect > 4) {
		parryeffect = -1;
	}
	if (parryeffect == -1) {
		effect.setPosition(-400, -400);
	}
	if (signcounter == -1) {
		signspr.setPosition(-400, 0);
	}
	
}
