#include "entity.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"player.h"
using namespace std;

class player;
class object :public entity {
public:
	player* player;
	float x, y=440;
	int type = 0;
	float distance = 1000;
	bool open = false;
	int getweapon = 0;
	int scroll = rand()%3;
	object();
	void settypepos(int,float);
	void updateposition(class player* player);
	Texture texture,texture2;
	float position;
};
object::object() {
	texture.loadFromFile("res/object.png");
	texture2.loadFromFile("res/item.png");
	rect.setOrigin(80, 80);
	sprite.setOrigin(80, 80);
	sprite.setTexture(texture);
	signspr.setTexture(texture2);
	rect.setSize(Vector2f(200, 160));
	rect.setFillColor(Color::Color(120, 150, 180, 180));
	signspr.setOrigin(80, 80);
	signspr.setTextureRect(IntRect(0, 0, 160, 160));

}
void object::settypepos(int settype,float rex) {
	srand(time(NULL));
	type = settype;
	x = rex;
	rect.setPosition(x, y);
	signspr.setPosition(1000, 1000);
	scroll = rand() % 3;
}
void object::updateposition(class player* player) {
	
	x = rect.getPosition().x;
	y = rect.getPosition().x;
	sprite.setPosition(rect.getPosition().x, rect.getPosition().y);
	distance = x - player->x;
	
	if (type == 0 || type == 3||type==4) {
		sprite.setTextureRect(IntRect(200 * open, 0, 200, 160));
	}
	else if (type == 1||type==2) {
		sprite.setTextureRect(IntRect(200 * (type - 1)+open*(-400), 160, 200, 160));
	}
	if (player->interact&&distance<100&&distance>-100&&!open) {
		
		open = true;
		if (type == 0) {
			player->interactthing = true;
			player->hppotremain += 1 + rand() % 3;
			getweapon = 1;
			signspr.setTextureRect(IntRect(160, 640, 160, 160));
		}
		else if (type == 1) {
			player->interactthing = true;
			player->armed = 12;
			getweapon = 1;
			signspr.setTextureRect(IntRect(160, 320, 160, 160));
		}
		else if (type == 2) {
			player->interactthing = true;
			player->arrowremain+= 1 + rand() % 3;
			getweapon = 1;
			signspr.setTextureRect(IntRect(0, 0, 160, 160));
		}
		else if (type == 3) {
			player->interactthing = true;
			player->armed = 12;
			player->getbow = true;
			getweapon = 1;
			signspr.setTextureRect(IntRect(0, 320, 160, 160));
		}
		else if (type == 4) {
			player->interactthing = true;
			getweapon = 1;
			if (scroll == 0) {
				signspr.setTextureRect(IntRect(0, 480, 160, 160));
				player->stabperk = true;
				buffer.loadFromFile("res/sound/player/getscroll.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			else if (scroll == 1) {
				signspr.setTextureRect(IntRect(160, 480, 160, 160));
				player->slashperk = true;
				buffer.loadFromFile("res/sound/player/getscroll.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			else if (scroll == 2) {
				signspr.setTextureRect(IntRect(0, 640, 160, 160));
				player->firstaidperk = true;
				buffer.loadFromFile("res/sound/player/getscroll.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
		}
		
		
	}
	if (getweapon == 1) {
		
		signspr.setPosition(player->rect.getPosition().x, player->rect.getPosition().y - 80);
	}
	else {
		signspr.setPosition(1000,1000);
	}
	if (!player->interact) {
		getweapon = 0;
	}
}