#include "entity.h"
#include <SFML/Graphics.hpp>
#include"player.h"

class player;
//class bot2;
class projectile :public entity 
{
public:
	player* player;
	float atk = 10;
	float multiplier = 0.5;
	float x = -400 ,y = 280,lx,ly;
	int direction = 0;
	int movement_speed = 0;
	int lspeed = 0;
	int arrowremove = 0;
	bool isfired = false;
	bool isslash = false;
	int slashcooldown = 0;
	int ldirection = 0;
	void checkshot(class player* player);
	void arrowshot();
	void updateposition();
	projectile();
};
projectile::projectile()
{	
	efx.loadFromFile("res/slashperk.png");
	item.loadFromFile("res/item.png");
	rect2.setSize(Vector2f(240, 240));
	rect2.setPosition(x, y);
	rect2.setFillColor(sf::Color::Color(133, 133, 133, 180));
	rect2.setOrigin(80, 80);
	effect.setOrigin(80, 80);
	effect.setTexture(efx);
	effect.setTextureRect(IntRect(0, 0, 240, 240));
	rect.setSize(Vector2f(160, 160));
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color::Color(133, 133, 133, 180));
	rect.setOrigin(80, 80);
	sprite.setOrigin(80, 80);
	sprite.setTexture(item);
	sprite.setTextureRect(IntRect(0, 0, 160, 160));
}

void projectile::checkshot(class player* player) {
	atk = 10 + (multiplier * player->dex);
	if (player->aim&&player->aimcount==2) {
		this->direction = player->direction / 2;
		this->x = (player->x) + (1 - direction * 2) * 45;
		this->y = (player->y)+25;
		arrowremove = 1;
		rect.setPosition(x, y);

	}
	else if (!player->aim && player->shot) {
		isfired = true;
		movement_speed = 45;
		if (arrowremove == 1) {
			player->arrowremain -= 1;
			player->shotdelay = 1;
			arrowremove = 0;
			buffer2.loadFromFile("res/sound/player/shoot.wav");
			sound2.setBuffer(buffer2);
			sound2.play();
		}
	}else if(!isfired) {
		this->x = -400;
		this->y = 0;
		rect.setPosition(x, y);
	}
	sprite.setTextureRect(IntRect(direction*160, 0, 160, 160));
	sprite.setPosition(rect.getPosition());

	if (player->slashperk) {
		if (player->atk && player->counter == 2&&slashcooldown==0) {
			this->ldirection = player->direction / 2;
			isslash = true;
			lspeed = 35;
			this->lx = (player->x) + (1 - ldirection * 2) * 60;
			this->ly = (player->y)-50;
			slashcooldown = 1;
			rect2.setPosition(lx, ly);
			buffer2.loadFromFile("res/sound/effect/slash.wav");
			sound2.setBuffer(buffer2);
			sound2.play();
		}
		if (slashcooldown > 0) {
			slashcooldown++;
		}
		if (slashcooldown > 80) {
			slashcooldown = 0;
		}
	}
}
void projectile::arrowshot() {
	if (isfired) {
		if (x < 1000&&x>-160) {
			rect.move((1-direction*2)*movement_speed,0);
		}
		else {
			isfired = false;
		}
	}
	if (isslash) {
		if (lx < 1000 && lx>-160) {
			rect2.move((1 - ldirection * 2) * lspeed, 0);
		}
		else {
			isslash = false;
		}
	}
	effect.setTextureRect(IntRect(ldirection * 240, 0, 240, 240));
	effect.setPosition(rect2.getPosition());
	
	sprite.setTextureRect(IntRect(direction * 160, 0, 160, 160));
	sprite.setPosition(rect.getPosition());
}
void projectile::updateposition() {
	x = rect.getPosition().x;
	y = rect.getPosition().y;
	lx = rect2.getPosition().x;
	ly = rect2.getPosition().y;
}