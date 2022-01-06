#include "entity.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"player.h"
#include"projectile.h"
#include<iostream>
extern int scorep;

class player;
class projectile;
class bot2 : public entity
{
public:
	player* player;
	projectile* projectile;
	Sprite arrow;
	////////////////////////////////position/////////////////////////////
	int x = 880, y = 440;
	////////////////////////////////status//////////////////////////////

	float movement_speed = 10+(rand()%3)*5;
	float sptodis = 0;
	float attack_damage = 30;
	float maxhp=35;
	float currenthp = maxhp;
	float maxar=25;
	float currentar = maxar;
	bool dead = false;
	int deadtime = 0;

	/////////////////////////////bar control////////////////////////
	float regenrate = 0.125;
	float percentmax=85;
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
	//////////////////////////bot arrow control///////////////////////
	bool shot = false;
	int arrowdirection = 0;
	float arrowx = 0;
	
	///////////////////////////standposition////////////////////////////
	bool backstab = false;
	
	int chkstate = 0;
	///////////////////////////animation////////////////////////////////
	bool detect = false;
	bool atking = false;
	bool atk = false;
	bool moving = false;
	bool stuning = false;
	
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

	bot2();
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

bot2::bot2()
{
	srand(time(NULL));
	movement_speed = 10 + (rand() % 4) * 5;
	caution.loadFromFile("res/sign.png");
	stun.loadFromFile("res/stun.png");
	
	arrow.setTextureRect(IntRect(0, 160, 160, 160));
	arrow.setOrigin(80, 80);
	arrow.setPosition(1000, 800);
	signspr.setPosition(-400, 0);
	rect.setSize(Vector2f(160, 160));
	rect.setPosition(x, y);
	rect.setFillColor(Color::Color(0,120,150,180));
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
	//signspr.setTextureRect(IntRect(0, 0, 80, 80));
	rect.setOrigin(80,80);
	sprite.setOrigin(80,80);
	signspr.setOrigin(40, 40);
	//effect.setPosition(-400, -400);
}
void bot2::control(class player* player) {
	if (!dead) {
		if (distance < 1200 && distance>-1200) {
			detect = true;


			if (!stuning) {

				if (distance > -800 && distance < 800) {
					inrange = true;
				}
				else {
					inrange = false;
				}


				if (!atk && (cooldown > rancooldown || cooldown == 0) && !atking) {
					if (this->x >= player->x) {
						
							this->direction = 2;
							
						
					}
					else {
						
							this->direction = 0;
							
					}
					srand (time(NULL));

				}
				if (inrange && cooldown == 0 && !atk && !atking) {
					atking = true;
					moving = false;
					moveoutcount = 0;
				}
				if (moveoutcount > 0) {
					moveoutcount++;
					direction = moveoutdirection;

				}


				
				
				if ((distance <= 700 || distance >= -700) && cooldown > 0 && !atk && (moveoutcount == 0 || moveoutcount > 16)) {
					moveoutdirection = rand() % 3;
					if (distance<200) {
						moveoutdirection = 0;
					}
					else if (distance > -200) {
						moveoutdirection = 2;
					}
					if (x > 700) {
						moveoutdirection = 2;
					}
					else if (x < 20) {
						moveoutdirection = 0;
					}
					
					moveoutcount = 1;

				}
				if (moveoutcount > 0) {
					moving = true;
				}
				if ((x < 20 || x>840) && !atking && !atk) {
					moveoutcount = 0;
					moving = true;
				}

			}
		}
		
		

		if (cooldown > 0 && !atk && !stuning) {
			cooldown++;

		}
		if (cooldown > rancooldown) {
			cooldown = 0;
			shot = false;
			rancooldown = 36 + rand() % 16;
		}
		
	}
}

void bot2::update_action()
{

	sprite.setPosition(rect.getPosition());
	if (dead) {
		sprite.setTextureRect(IntRect((direction / 2) * 160, 0, 160, 160));
	}
	else {
		if (stuning) {
			atk = false;
			atking = false;
			counter = 0;
			atkdelay = 0;
			signcounter = 0;
			sprite.setTextureRect(IntRect((direction / 2) * 160, 0, 160, 160));
			if (!shot) {
				arrow.setPosition(1000, 800);
			}
		}
		else if (atking) {
			item.loadFromFile("res/item.png");
			arrow.setTexture(item);
			sprite.setTextureRect(IntRect((10 * 160) + ((direction * 2 + counter) * 160), 0, 160, 160));
			

			if (counter >= 0 && atkdelay <= 2) {
				atkdelay++;
			}
			if (atkdelay > 2) {
				counter++;
				atkdelay = 0;
			}
			if (counter > 1) {
				counter = 1;
				arrowdirection = direction;
				arrowx = x + (1 - arrowdirection) * 45;
				arrow.setPosition(arrowx, y +25);
				arrow.setTextureRect(IntRect(arrowdirection / 2 * 160, 160, 160, 160));
			}
			
		}
		else if (atk) {
			sprite.setTextureRect(IntRect((10 * 160) + ((direction * 2 + counter) * 160), 0, 160, 160));
			if (counter == 2) {
				shot = true;
			}
			counter++;
			
			if (counter > 3 && atkdelay < 2) {
				counter = 3;
				atkdelay++;
				
			}
			if (counter > 3) {
				
				counter = 0;
				atkdelay = 0;
				atk = false;
			}

		}

		else if ((moving || movecounter != 0) && !stuning&&direction!=1) {

			sprite.setTextureRect(IntRect((2 + direction * 2 + movecounter) * 160, 0, 160, 160));
			walkbuffer++;
			if (walkbuffer == 2) {
				movecounter++;
				walkbuffer = 0;
			}

			if (movecounter > 3) {
				movecounter = 0;
			}

		}
		else {
			sprite.setTextureRect(IntRect((direction / 2) * 160, 0, 160, 160));


		}
	}
}
void bot2::move() {
	arrow.move((1 - arrowdirection) * 45 * shot, 0);
	if (dead) {

		rect.move((1 - selfknockdirection) * movement_speed,(4-jumpcount)*-5);
		jumpcount++;
		if (!shot) {
			arrow.setPosition(1000, 800);
		}

	}
	else {
		
		
		
		if (moving && movecounter % 3 != 0&&!atk) {
			
			rect.move((1 - direction) * movement_speed, 0);
			
			moving = false;
		}
	}
}
void bot2::calculate(class player* player)
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
void bot2::updateposition() {
	this->x = rect.getPosition().x;
	this->y = rect.getPosition().y;
	arrowx = arrow.getPosition().x;
}
void bot2::checkdamage(class player* player){
	
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
				selfknockback = 2;

			}
			else if (!stuning) {
				selfknockback = 1;

			}
			selfknockdirection = player->direction;
			buffer2.loadFromFile("res/sound/effect/hit.wav");
			sound2.setBuffer(buffer2);
			sound2.setVolume(75.f);
			sound2.play();
		}

	}
	if (shot) {
		botdpjt = arrowx - player->x;
		if (player->atk && player->counter == 3&&((botdpjt > 0 && arrowdirection == 2 && botdpjt < 200)
			|| (botdpjt < 0 && arrowdirection == 0 && botdpjt>-200))) {
			scorep += 300;
			arrow.setPosition(1000, 800);
			shot = false;
			buffer2.loadFromFile("res/sound/effect/parry.wav");
			sound2.setBuffer(buffer2);
			sound2.play();
		}
		else if ((botdpjt > 0 && arrowdirection == 2 && botdpjt < 90)
			|| (botdpjt < 0 && arrowdirection == 0 && botdpjt>-90)) {
			
			
				if (player->iframe == 0 && player->y > 320) {
					player->currenthp -= attack_damage;
					knockback = 1;
					knockdirection = arrowdirection;
					scorep -= 100;
					arrow.setPosition(1000, 800);
					shot = false;
					buffer2.loadFromFile("res/sound/effect/arrowshot.wav");
					sound2.setBuffer(buffer2);
					sound2.play();
				}
			
		}
	}


/*
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
			selfknockback = 2;
			selfknockdirection = player->direction;
			counter = 0;
			atk = false;
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

		
		else if (atk && counter == 3 && atkdelay == 2) {
			if ((((distance <= 150 && distance > 0) && direction == 2) ||
			((distance >= -150 && distance < 0) && direction == 0)) && player->iframe == 0) {
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
					player->buffer2.loadFromFile("res/sound/player/hit.wav");
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
	}*/
	if (selfknockback > 0) {
		rect.move((1 - selfknockdirection) * (3 - selfknockback) * 25, 0);
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

void bot2::checkpjtdamage(class projectile* pjt ) {
	distancepjt = pjt->x - this->x;
	distanceslash = pjt->lx - this->x;
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
				selfknockback = 1;
				buffer2.loadFromFile("res/sound/effect/arrowshot.wav");
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
					}

				}
				else if (currentar == 0 && stuning) {
					slashed = 1;
					bptime = 1;
				}
				currenthp -= pjt->atk * 2 / 3;
				selfknockdirection = pjt->ldirection * 2;
				selfknockback = 1;
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
void bot2::barcontrol() {
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
		}
		if (bptime > 36) {
			if (bptime == 37) {
				signcounter = -1;
			}
			regenrate = 8.1;
			stuning = false;
			if (currentar >= maxar) {
				currentar = maxar;
				regenrate = 0.0125;
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
		effect.setPosition(-400, -400);
		signspr.setPosition(-400, 1000);
	}
	if (deadtime > 0) {
		deadtime++;
	}
	percenthp = currenthp / maxhp * percentmax;
	percentar = currentar / maxar * percentmax;

	rectbar1.setPosition(x , y + 80);
	rectbar1.setSize(Vector2f(percentmax, 18));
	bar1.setPosition(x, y + 80);
	bar1.setSize(Vector2f(percenthp, 18));
	rectbar2.setPosition(x , y + 100);
	rectbar2.setSize(Vector2f(percentmax, 15));
	bar2.setPosition(x, y + 100);
	bar2.setSize(Vector2f(percentar, 15));

	if (signcounter != -1) {
		signspr.setPosition(x - (1 - direction) * 5, y - 100);
	}
	else {
		signspr.setPosition(-400,  1000);
	}
	if (!stuning) {
		if (x > 780) {
			signspr.move(780 - x,0);
		}
		else if (x < 20) {
			signspr.move(20-x,0);
		}
	}
	signspr.setTextureRect(IntRect(signcounter * 80, 0, 80, 80));
}
void bot2::soundcontrol() {
	if (dead&&deadtime==2) {
		buffer.loadFromFile("res/sound/bot2/dead.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
	else {
		if (detect) {
			if (atk && counter == 2) {
				buffer.loadFromFile("res/sound/bot2/atk.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			else if (moving && (movecounter) % 3 == 1 && !stuning&&!dead) {
				buffer.loadFromFile("res/sound/bot2/move.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
		}
	}
}
void bot2::signcontrol() {
	if (!dead) {
		if (stuning) {
			signcounter = 0;
			caution.loadFromFile("res/stun.png");
			signspr.setTexture(caution);
			signspr.setTextureRect(IntRect(signcounter * 80, 0, 80, 80));
		}
		else if (atking ||signcounter!=-1) {

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
					cooldown = 1;
					signdelay = 0;
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
		signspr.setPosition(-400, -400);
	}
}
