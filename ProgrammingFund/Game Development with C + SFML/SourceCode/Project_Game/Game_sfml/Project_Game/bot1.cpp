#include "entity.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"player.h"
#include"projectile.h"
extern int scorep;
class player;
class projectile;
class bot1 : public entity
{
public:
	player* player;
	projectile* projectile;
	////////////////////////////////position/////////////////////////////
	int x = 880, y = 440;
	////////////////////////////////status//////////////////////////////
	float movement_speed = 15;
	float sptodis = 0;
	float attack_damage = 20;
	float maxhp=50;
	float currenthp = maxhp;
	float maxar=50;
	float currentar = maxar;
	bool dead = false;
	int deadtime = 0;

	/////////////////////////////bar control////////////////////////
	float regenrate = 0.0625;;
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
	int atkdelay = 0;
	int signcounter = -1;
	int signdelay = 0;
	int knockback = 0;
	int knockdirection = 0;
	int selfknockback = 0;
	int selfknockdirection = 0;
	int parryeffect = -1;
	int stabeffect = -1;
	int jumpcount = 0;
	int ranmoveout = 4 + rand() % 16;
	int moveoutcount = 0;
	int moveoutdirection = 0;
	///////////////////////////bot reaction//////////////////////////
	int reaction = 24;
	int reactioncount = 0;
	int cooldown = 0;
	int rancooldown = 4+rand()%4;
	int parry = 0;
	int parrycount = 0;
	int parrylimit = 1+rand() % 3;
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
	int distance = 1000;
	int pjtshot = 0;
	int distancepjt = 1000;
	int distanceslash = 1000;
	int slashed = 0;
	/////////////////////////function//////////////////////////////////
	bot1();
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

bot1::bot1()
{
	srand(time(NULL));
	movement_speed = 10 +(1+ (rand() % 3)) * 5;
	caution.loadFromFile("res/sign.png");
	stun.loadFromFile("res/stun.png");
	efx.loadFromFile("res/parryeffect.png");
	signspr.setPosition(-400, 0);
	rect.setSize(Vector2f(160, 160));
	rect.setPosition(x, y);
	rect.setFillColor(Color::Color(150,150,150,180));
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

}
void bot1::control(class player* player) {
	if (!dead) {
		if (distance < 1200 && distance>-1200) {
			detect = true;


			if (!stuning) {

				if (distance > -200 && distance < 200&&(distance>100||distance<-100)) {
					inrange = true;
					moving = false;
				}
				else {
					inrange = false;
					if (cooldown == 0) {
						moving = true;
					}
					if (distance<100 && distance>-100&&moveoutcount==0&&!atk&&cooldown<10) {
						moveoutcount=1;
					}
				}


				if (!atk && (cooldown > rancooldown || cooldown == 0) && !atking) {
					if (this->x >= player->x) {

						this->direction = 2;
						if (distance<100 && distance>-100 && moveoutcount != 0) {
							moveoutdirection = 0;
						}
						if (moveoutcount != 0) {
							direction = moveoutdirection;
						}
					}
					else {

						this->direction = 0;
						if (distance<100 && distance>-100&&moveoutcount!=0) {
							moveoutdirection = 2;
						}
						if (moveoutcount != 0) {
							direction = moveoutdirection;
						}
					}
					rancooldown = 4 + rand() % 16;
					srand (time(NULL));
				}



				if (inrange && cooldown == 0 && !moving && !atk && !atking&&moveoutcount==0) {
					atking = true;

				}
				if (atking) {
					moving = false;
				}

			}
		}
		if (moveoutcount > 0) {
			moving = true;
			moveoutcount++;
		}
		if (moveoutcount >= ranmoveout) {
			moveoutcount = 0;
			ranmoveout = 4+ rand() % 16;
		}


		if (cooldown > 0 && !atk && !stuning) {
			cooldown++;

		}
		if (cooldown > 16) {
			cooldown = 0;
		}
	}
}

void bot1::update_action()
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
			sprite.setTextureRect(IntRect((direction / 2) * 160, 0, 160, 160));
		}
		else if (atk) {
			sprite.move(-(direction / 2) * 65, 0);
			sprite.setTextureRect(IntRect((10 * 160) + ((direction * 2 + counter) * 240), 0, 240, 160));
			rect.move((1 - direction) *sptodis-counter, 0);
			counter++;

			if (counter > 3 && atkdelay < 2) {
				counter = 3;
				atkdelay++;
			}
			if (counter > 3) {
				counter = 0;
				atkdelay = 0;
				sptodis = 0;
				atk = false;
			}

		}

		else if ((moving || movecounter != 0) && !stuning) {

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
void bot1::move() {
	if (dead) {

		rect.move((1 - selfknockdirection) * movement_speed,(4-jumpcount)*-5);
		jumpcount++;
	}
	else {
		if (moving && movecounter % 3 != 0) {

			rect.move((1 - direction) * movement_speed, 0);
			moving = false;
		}
	}
}
void bot1::calculate(class player* player)
{
	distance = (this->x)-(player->x);
	
	if (distance > 0) {
		if (player->direction == 0 && this->direction == 0) {
			backstab = true;
		}
		else {
			backstab = false;
		}
		if (atking) {

			sptodis = 5 + distance / 25;
		}
	}
	else if (distance < 0) {
		if (player->direction == 2 && this->direction == 2) {
			backstab = true;
		}
		else {
			backstab = false;
		}
		if (atking) {

			sptodis = (5 - distance / 25);
		}
			
		
	}

}
void bot1::updateposition() {
	this->x = rect.getPosition().x;
	this->y = rect.getPosition().y;
	
}
void bot1::checkdamage(class player* player){
	
	if (parry ==0&& player->atk && atk&&counter>0&&player->counter>1&&
		(((distance <= 195 && distance > 0) && player->direction == 0 && direction == 2) ||
		((distance >= -195 && distance < 0) && player->direction == 2 && direction == 0))) {
			
			currentar -= player->attack_damage*1.5 ;
			if (currentar <= 0) {
				currentar = 0;
				regenrate = 0;
				bptime = 1;
			}

			player->staregen += 10;
			//selfknockback = 2;
			selfknockdirection = player->direction;
			counter = 0;
			atk = false;
			parry = 1;
			cooldown = 10+rand()%6;
			parrycount++;
			parryeffect = 0;
			efx.loadFromFile("res/parryeffect.png");
			effect.setTexture(efx);
			effect.setPosition(x + (1 - direction) * 50, y);
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
			
	}
	else if(parry==0) {

		if (player->atk && player->counter == 3) {
			if (((distance <= 195 && distance > 0) && player->direction == 0) || ((distance >= -195 && distance < 0) && player->direction == 2)) {
				if (currentar > 0) {
					if (backstab) {
						
						
						if(player->stabperk) {
							currenthp -= player->attack_damage *3/4 ;
							if (bptime == 0) {
								currentar -= player->attack_damage * 9/4 ;
							}
							parryeffect = 0;
							efx.loadFromFile("res/stabperk.png");
							effect.setTexture(efx);
							effect.setPosition(rect.getPosition().x + -1*(1 - direction) * 10, y);
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
					
				}
				else if (!stuning) {
					selfknockback = 2;
					
				}
				selfknockdirection = player->direction;
				buffer2.loadFromFile("res/sound/effect/hit.wav");
				sound2.setBuffer(buffer2);
				sound2.setVolume(75.f);
				sound2.play();
			}

		}
		else if (atk && counter == 3 && atkdelay == 2) {
			if ((((distance <= 180 && distance > 0) && direction == 2) ||
			((distance >= -180 && distance < 0) && direction == 0)) && player->iframe == 0&&player->y>320) {
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
						player->currenthp -= (player->currentstamina-7/8*attack_damage );
						player->currentstamina = 0;
						knockback = 1;
						scorep -= 100;
					}

				}
				else {
					player->buffer2.loadFromFile("res/sound/player/hit.wav");
					player->sound2.setBuffer(player->buffer2);
					player->sound2.play();
					player->currenthp -= attack_damage;
					knockback = 1;
					scorep -= 100;
				}
				if (player->currenthp < 0) {
					player->currenthp = 0;
				}

				knockdirection = direction;
				
			}
		}
	}
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

void bot1::checkpjtdamage(class projectile* pjt ) {
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
					currentar -= pjt->atk * 3/2;
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
				currenthp -= pjt->atk *2/3;
				selfknockdirection = pjt->ldirection * 2;
				selfknockback = 1;
				buffer2.loadFromFile("res/sound/effect/arrowshot.wav");
				sound2.setBuffer(buffer2);
				sound2.play();
			}
		}
	}
	if (pjtshot > 0) {
		pjtshot++;

	}
	if (pjtshot > 16) {
		pjtshot = 0;
	}
	if (slashed > 0) {
		slashed++;
	}
	if (slashed > 16) {
		slashed = 0;
	}
}
void bot1::barcontrol() {
	if (currentar < maxar) {
		currentar += regenrate;
		if (currentar > maxar) {
			currentar = maxar;
			regenrate = 0.0125;
		}
		if (bptime > 0) {
			if (!dead) {
				bptime++;
			}
			stuning = true;
			moveoutcount = 0;
			cooldown = 1;
		}
		if (bptime > 40) {
			if (bptime == 41) {
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
	}
	if (deadtime > 0) {
		deadtime++;
		signspr.setPosition(-400, -400);
		if (parryeffect == -1) {
			effect.setPosition(-400, -400);
		}
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
		signspr.setTextureRect(IntRect(signcounter * 80, 0, 80, 80));
	}
	else {
		signspr.setPosition(-400, 0);
	}
}
void bot1::soundcontrol() {
	if (dead&&deadtime==2) {
		buffer.loadFromFile("res/sound/bot1/dead.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
	else {
		if (detect) {
			if (atk && counter == 1) {
				buffer.loadFromFile("res/sound/bot1/atk.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			else if (moving && (movecounter) % 3 == 1 && !stuning&&!dead) {
				buffer.loadFromFile("res/sound/bot1/move.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
		}
	}
}
void bot1::signcontrol() {
	if (!dead) {
		if (stuning) {
			signcounter = 0;
			caution.loadFromFile("res/stun.png");
			signspr.setTexture(caution);
			signspr.setTextureRect(IntRect(signcounter * 80, 0, 80, 80));
		}
		else if (atking && !stuning) {
			
			caution.loadFromFile("res/sign.png");
			signspr.setTexture(caution);
			
			
			signspr.setTextureRect(IntRect(signcounter * 80, 0, 80, 80));
			
			if (signcounter < 10) {
				signcounter++;
			}
			if (signcounter == 10) {
				signdelay++;

				signcounter++;
			}
			else if (signcounter > 10) {
				if (signdelay < 4) {
					signcounter = 10;
				}
				else if (signdelay >= 4) {
					atk = true;
					atking = false;
					cooldown = 1;
					signdelay = 0;
					signcounter = -1;
				}
			}

			/*if (signcounter == 10) {
				signdelay++;
				if (signdelay == 4) {
					signcounter++;;
					signdelay = 0;
				}
			}
			if (signcounter < 10) {
				signcounter++;
			}

			if (signcounter > 10) {
				atk = true;
				atking = false;
				cooldown = 1;
				signcounter = -1;
			}*/
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
	//signspr.setPosition(x - 35 + (1 - direction) * 5 * -1, y - 120);
}