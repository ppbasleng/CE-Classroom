#include "entity.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"player.h"
#include<string>
using namespace std;
extern bool gameclear;
extern bool pause;
extern bool gameover;
extern float mousex, mousey;
extern bool menumode;
class player;
//class bot1;
class gpui :public entity
{
public:
//bot1* bot1;
	int fontsize = 15;
player* player;
float regenrate = 0;
float bonusregen = 0;
float regencount = 0;
int bouncefix = 0;
int clickbounce = 0;
bool regen = false;
int available = 0;
bool showstate = false;
int togglestate = 0;
int effectcount = -1;
int effecttime = 0;
void setupstat(class player* player,int);
void updatestat(class player* player,int);
void statuswindowsetup();
void statuswindow(class player* player);
void itemiconsetup();
void itemicon(class player* player);
void mousecontrol(class player* player);
void controlsetup();
void kbcontrol(class Music* music,class player* player);
void draw(RenderWindow&);
gpui();
Text mousepos;
Text str, agi, dex, vit, level,remain,exp;
Sprite sp1, sp2, sp3, sp4,sp5;
Texture button,show;
};
gpui::gpui() {
	mousepos.setFont(font);
	mousepos.setCharacterSize(15);
	mousepos.setFillColor(sf::Color::Black);

	str.setFont(font);
	str.setCharacterSize(fontsize);
	str.setFillColor(sf::Color::Black);
	agi.setFont(font);
	agi.setCharacterSize(fontsize);
	agi.setFillColor(sf::Color::Black);
	dex.setFont(font);
	dex.setCharacterSize(fontsize);
	dex.setFillColor(sf::Color::Black);
	vit.setFont(font);
	vit.setCharacterSize(fontsize);
	vit.setFillColor(sf::Color::Black);
	level .setFont(font);
	level .setCharacterSize(fontsize);
	level.setFillColor(sf::Color::Black);
	remain.setFont(font);
	remain.setCharacterSize(fontsize);
	remain.setFillColor(sf::Color::Black);
	exp.setFont(font);
	exp.setCharacterSize(fontsize);
	exp.setFillColor(sf::Color::Black);
	exp.setCharacterSize(fontsize);
	effect.setOrigin(80, 80);
}
void gpui::statuswindowsetup() {
	button.loadFromFile("res/button.png");
	sp1.setTexture(button);
	sp2.setTexture(button);
	sp3.setTexture(button);
	sp4.setTexture(button);
	
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setString("STATUS");
	rect.setOutlineThickness(4);
	rect.setOutlineColor(Color::Color(0, 0, 0, 180));
	rect.setSize(Vector2f(400, 300));
	rect.setFillColor(Color::Color(255, 209, 101, 220));

	rect.setPosition(804, 100);
	text.setPosition(950, 120);
	str.setPosition(820, 260);
	agi.setPosition(915, 260);
	dex.setPosition(1010, 260);
	vit.setPosition(1105, 260);
	rectbar1.setPosition(850, 200);
	bar1.setPosition(850, 200);
	value.setPosition(820, 160);
	level.setPosition(970, 230);
	remain.setPosition(820, 370);
	sp1.setPosition(822, 290);
	sp2.setPosition(912, 290);
	sp3.setPosition(1012, 290);
	sp4.setPosition(1107, 290);

	rectbar1.setFillColor(Color::Black);
	rectbar1.setSize(Vector2f(300, 20));
	rectbar1.setOutlineThickness(2);
	rectbar1.setOutlineColor(Color::White);
	
	bar1.setFillColor(Color::Green);
	
}
void gpui::mousecontrol(class player* player) {


	mousepos.setPosition(mousex, mousey);
	mousepos.setString(to_string((int)mousex) + "," + to_string((int)mousey));
	if (Mouse::isButtonPressed(Mouse::Left) && clickbounce == 0) {
		if (showstate&&player->statp>0) {
			if (mousex >= 422 && mousex <= 486 && mousey>=290 && mousey <= 354) {
				player->str++;
				player->statp--;
				buffer.loadFromFile("res/sound/gui/upstat.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			if (mousex >= 512 && mousex <= 576 && mousey >= 290 && mousey <= 354) {
				player->agi++;
				player->statp--;
				buffer.loadFromFile("res/sound/gui/upstat.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			if (mousex >= 612 && mousex <= 676 && mousey >= 290 && mousey <= 354) {
				player->dex++;
				player->statp--;
				buffer.loadFromFile("res/sound/gui/upstat.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			if (mousex >= 707 && mousex <= 774 && mousey >= 290 && mousey <= 354) {
				player->vit++;
				player->statp--;
				player->hpregen += 10;
				buffer.loadFromFile("res/sound/gui/upstat.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			player->maxhp = 50 + player->vit * 10;
			player->maxstamina = 70 + player->agi * 6;
			player->movement_speed = 19 + float(player->agi)/5;
			player->attack_damage = 4 + player->str * 6 / 5;
		}
		clickbounce = 1;
	}
	if (clickbounce > 0) {
		clickbounce++;
	}
	if (clickbounce > 4) {
		clickbounce = 0;
	}
	//////////////////////////cheat/////////////////////////
	if (Mouse::isButtonPressed(Mouse::Right) && clickbounce == 0) {
		if (Mouse::isButtonPressed(Mouse::Middle)) {
			player->statp += 10;
			player->hppotremain += 10;
			player->arrowremain += 10;
			player->stabperk = true;
			player->firstaidperk = true;
			player->slashperk = true;
			clickbounce = 1;
		}
	}

}
void gpui::statuswindow(class player* player) {
	
	if (player->statp > 0) {
		available = 1;
	}
	else {
		available = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::P) && bouncefix==0) {
		bouncefix = 1;
		togglestate = 1;
		buffer.loadFromFile("res/sound/gui/statuswindow.wav");
		sound.setBuffer(buffer);
		sound.play();
	}
	if (togglestate !=0) {
		togglestate++;
		if (showstate) {

			rect.move((16-togglestate)*4, 0);
			text.move((16 - togglestate) * 4, 0);
			str.move((16 - togglestate) * 4, 0);
			agi.move((16 - togglestate) * 4, 0);
			dex.move((16 - togglestate) * 4, 0);
			vit.move((16 - togglestate) * 4, 0);
			rectbar1.move((16 - togglestate) * 4, 0);
			bar1.move((16 - togglestate) * 4, 0);
			value.move((16 - togglestate) * 4, 0);
			level.move((16 - togglestate) * 4, 0);
			remain.move((16 - togglestate) * 4, 0);
			sp1.move((16 - togglestate) * 4, 0);
			sp2.move((16 - togglestate) * 4, 0);
			sp3.move((16 - togglestate) * 4, 0);
			sp4.move((16 - togglestate) * 4, 0);
			if (rect.getPosition().x >= 800) {
				rect.setPosition(804, 100);
				text.setPosition(950, 120);
				str.setPosition(820, 260);
				agi.setPosition(915, 260);
				dex.setPosition(1010, 260);
				vit.setPosition(1105, 260);
				rectbar1.setPosition(850, 200);
				bar1.setPosition(850, 200);
				value.setPosition(820, 160);
				level.setPosition(970, 230);
				remain.setPosition(820, 370);
				sp1.setPosition(822, 290);
				sp2.setPosition(912, 290);
				sp3.setPosition(1012, 290);
				sp4.setPosition(1107, 290);
				showstate = false;
				togglestate = 0;
			}
		}
		else if (!showstate) {
			rect.move(-(16 - togglestate) * 4, 0);
			text.move(-(16 - togglestate) * 4, 0);
			str.move(-(16 - togglestate) * 4, 0);
			agi.move(-(16 - togglestate) * 4, 0);
			dex.move(-(16 - togglestate) * 4, 0);
			vit.move(-(16 - togglestate) * 4, 0);
			rectbar1.move(-(16 - togglestate) * 4, 0);
			bar1.move(-(16 - togglestate) * 4, 0);
			value.move(-(16 - togglestate) * 4, 0);
			level.move(-(16 - togglestate) * 4, 0);
			remain.move(-(16 - togglestate) * 4, 0);
			sp1.move(-(16 - togglestate) * 4, 0);
			sp2.move(-(16 - togglestate) * 4, 0);
			sp3.move(-(16 - togglestate) * 4, 0);
			sp4.move(-(16 - togglestate) * 4, 0);
			if (rect.getPosition().x <= 400) {
				rect.setPosition(400, 100);
				text.setPosition(550, 120);
				str.setPosition(420, 260);
				agi.setPosition(515, 260);
				dex.setPosition(610, 260);
				vit.setPosition(705, 260);
				rectbar1.setPosition(450, 200);
				bar1.setPosition(450, 200);
				value.setPosition(420, 160);
				level.setPosition(570, 230);
				remain.setPosition(420, 370);
				sp1.setPosition(422, 290);
				sp2.setPosition(512, 290);
				sp3.setPosition(612, 290);
				sp4.setPosition(707, 290);

				showstate = true;
				togglestate = 0;
			}
		}
		
	}
	if (bouncefix > 0) {
		bouncefix++;
	}
	if (bouncefix > 16) {
		bouncefix = 0;
	}
	if (player->exp >= player->levelcap[player->levelnow - 1]) {
		player->exp -= player->levelcap[player->levelnow - 1];
		player->levelnow++;
		player->statp++;
		sound.stop();
		buffer.loadFromFile("res/sound/player/levelup.wav");
		sound.setBuffer(buffer);
		sound.play();
	}

	

	str.setString("STR  "+to_string(player->str));
	agi.setString("AGI  " + to_string(player->agi));
	dex.setString("DEX  " + to_string(player->dex));
	vit.setString("VIT  " + to_string(player->vit));
	level.setString(to_string(player->exp) + "/" + to_string(player->levelcap[player->levelnow - 1]));
	value.setString("LEVEL: "+to_string(player->levelnow));
	remain.setString("POINT(S): " + to_string(player->statp));
	bar1.setSize(Vector2f(float(player->exp) / float(player->levelcap[player->levelnow-1]) * 300, 20));

	sp1.setTextureRect(IntRect(available * 64, 0, 64, 64));
	sp2.setTextureRect(IntRect(available * 64, 0, 64, 64));
	sp3.setTextureRect(IntRect(available * 64, 0, 64, 64));
	sp4.setTextureRect(IntRect(available * 64, 0, 64, 64));
}
void gpui::itemiconsetup() {
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(3);
	text.setOutlineColor(sf::Color::Black);
	value.setCharacterSize(20);
	value.setFillColor(sf::Color::White);
	value.setOutlineThickness(3);
	value.setOutlineColor(sf::Color::Black);
	button.loadFromFile("res/itemicon.png");
	show.loadFromFile("res/perkicon.png");

	sp1.setTexture(button);
	sp2.setTexture(button);
	sp3.setTexture(show);
	sp4.setTexture(show);
	sp5.setTexture(show);
	sp3.setPosition(50, 0);
	sp4.setPosition(100, 0);
	sp5.setPosition(150, 0);
	sp1.setPosition(-20, 180);
	sp2.setPosition(-20, 120);
	text.setPosition(56, 224);
	value.setPosition(56, 168);

}
void gpui::itemicon(class player* player) {
	sp1.setTextureRect(IntRect(0, 0, 96, 96));
	sp2.setTextureRect(IntRect(96, 0, 96, 96));
	text.setString("X " + to_string(player->arrowremain));
	value.setString("X " + to_string(player->hppotremain));
	sp3.setTextureRect(IntRect(48 * player->stabperk, 0, 48, 48));
	sp4.setTextureRect(IntRect(48 * player->slashperk, 48, 48, 48));
	sp5.setTextureRect(IntRect(48 * player->firstaidperk, 96, 48, 48));

}

void gpui::controlsetup() {
	text.setCharacterSize(60);
	text.setString("PAUSE");
	text.setOutlineThickness(3);
	text.setFillColor(sf::Color::White);
	text.setPosition(-1000, 0);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	rect.setSize(Vector2f(800, 600));
	rect.setOrigin(400, 300);
	rect.setPosition(-1000, 0);
	rect.setFillColor(Color::Color(0, 0, 153, 180));
}

void gpui::kbcontrol(class Music* music,class player* player) {
	if (Keyboard::isKeyPressed(Keyboard::Escape) && bouncefix == 0) {
		if (!player->dead&&!menumode) {
			if (pause) {
				pause = false;
				buffer.loadFromFile("res/sound/game/pauseout.wav");
				sound.setBuffer(buffer);
				sound.play();
				music->play();
				music->setLoop(true);
			}
			else if (!pause) {
				pause = true;
				buffer.loadFromFile("res/sound/game/pausein.wav");
				sound.setBuffer(buffer);
				sound.play();
				music->pause();
			}
			bouncefix = 1;
		}
	}
	if (pause) {
		text.setString("PAUSE");
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setFillColor(sf::Color::White);
		rect.setSize(Vector2f(800, 600));
		rect.setFillColor(Color::Color(0, 0, 153, 180));
		rect.setSize(Vector2f(800, 600));
		rect.setOrigin(400, 300);
		rect.setPosition(400, 300);
		text.setPosition(400, 300);
	}
	else if (player->dead) {
		if (player->deadtime == 2) {
			text.setString("GAMEOVER");
			text.setOutlineColor(Color::Black);
			text.setFillColor(sf::Color::White);
			text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
			text.setPosition(400, 300);
			rect.setSize(Vector2f(800, 600));
			rect.setOrigin(400, 300);
			rect.setPosition(400, 300);

		}
		
		if (player->deadtime < 18&&player->deadtime!=0) {
			text.move(0, -8);
			music->setVolume(50 - 2* player->deadtime);
			rect.setFillColor(Color::Color(0, 0, 0, float(player->deadtime) * 180/16));
		}
		if (player->deadtime==18) {
			text.setPosition(400, 172);
			rect.setFillColor(Color::Color(0, 0, 0, 180));
			rect.setPosition(400, 300);
			music->openFromFile("res/sound/game/over.ogg");
			music->setVolume(60);
			music->play();
			player->deadtime = 0;
			gameover = true;
		}
		if (player->deadtime > 0) {
			player->deadtime++;
		}
	}
	else if (gameclear) {
		text.setString("VICTORY");
		text.setFillColor(Color::Color(248 ,222, 126));
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		rect.setFillColor(Color::Color(0, 0, 0, 180));
		rect.setSize(Vector2f(800, 150));
		rect.setOrigin(400, 100);
		rect.setOutlineThickness(5);
		text.setPosition(400, 150);
		rect.setPosition(400, 150);
	}
	else {
		text.setPosition(-1000, 0);
		rect.setPosition(-1000, 0);
	}
	if (bouncefix > 0) {
		bouncefix++;
	}
	if (bouncefix > 8) {
		bouncefix = 0;
	}
	
	
}
void gpui::setupstat(class player* player, int type) {
	
	if (type == 1) {
		text.setPosition(5, 60);
		text.setString("HP");
		text.setOutlineThickness(3);
		rect.setPosition(50, 50);
		rect.setSize(Vector2f(player->maxhp * 32 / 15, 32));
		rect.setFillColor(Color::Color(0,0,0,180));
		rect.setOutlineColor(Color::Color(0, 0, 0, 180));
		rect.setOutlineThickness(3);
		
		rect2.setPosition(50, 50);
		rect2.setSize(Vector2f(player->currenthp* 32 / 15, 32));
		rect2.setFillColor(Color::Red);

	}
	else if (type == 2) {
		
		text.setPosition(5, 105);
		text.setCharacterSize(14);
		text.setString("STA");
		text.setOutlineThickness(3);
		rect.setPosition(50, 100);
		rect.setSize(Vector2f(player->maxstamina * 32 / 20, 20));
		rect.setFillColor(Color::Color(0,0,0,180));
		rect.setOutlineColor(Color::Color(0, 0, 0, 180));
		rect.setOutlineThickness(3);
		rect2.setPosition(50, 100);
		rect2.setSize(Vector2f(player->currentstamina * 32 / 20, 20));
		rect2.setFillColor(Color::Yellow);
		regen = true;
		regenrate = 0.375;
	}
}
void gpui::updatestat(class player* player, int type) {
	if (type == 1) {
		
		if (player->hpregen > 0) {
			bonusregen = player->hpregen / 10;
			player->hpregen -= bonusregen;
			if (player->hpregen < 1) {
				player->hpregen = 0;
			}
			player->currenthp += bonusregen;
		}
			
			if (player->currenthp > player->maxhp) {
				player->currenthp = player->maxhp;
				player->hpregen = 0;
			}
		if (player->currenthp <= 0&&!player->dead) {
			if (player->firstaidperk) {
				player->iframe = 1;
				player->currenthp += player->maxhp/2;
				efx.loadFromFile("res/firstaidperk.png");
				effect.setTexture(efx);
				effectcount = 0;
				player->firstaidperk = false;
				buffer.loadFromFile("res/sound/player/powerup.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			else {
				player->currenthp = 0;
				player->dead = true;
				player->moving = false;
				player->deadtime = 1;
			}
			
		}

		rect.setSize(Vector2f(player->maxhp * 32 / 15, 32));
		rect2.setSize(Vector2f(player->currenthp * 32 / 15, 32));
	}
	else if (type == 2) {
		
		if (player->staregen > 0) {
			bonusregen = player->staregen/10;
			player->staregen -= bonusregen;
			if (player->staregen < 1) {
				player->staregen = 0;
			}
		}
		if (player->currentstamina < player->maxstamina) {
			player->currentstamina += regenrate*float(100+player->agi)/100+bonusregen;
		}
		if (player->currentstamina > player->maxstamina) {
			player->currentstamina = player->maxstamina;
		}
		if (player->currentstamina < 0) {
			player->currentstamina = 0;
		}

		rect.setSize(Vector2f(player->maxstamina * 32 / 20, 20));
		rect2.setSize(Vector2f(player->currentstamina * 32 / 20, 20));

	}
	if (effectcount > -1) {
		effect.setTextureRect(IntRect(effectcount * 160, 0,160,160));
		effect.setPosition(player->rect.getPosition().x, player->rect.getPosition().y);
		effectcount++;
		player->iframe = 1;
	}
	if (effectcount > 7) {
		effectcount = 0;
		effecttime++;
	}
	if (effecttime>2) {
		effectcount = -1;
		effecttime = 0;
		player->iframe = 0;
		effect.setPosition(1000, 1000);
	}
	
}

void gpui::draw(RenderWindow& window) {
	window.draw(rect);
	window.draw(text);
	window.draw(str);
	window.draw(agi);
	window.draw(dex);
	window.draw(vit);
	window.draw(level);
	window.draw(value);
	window.draw(remain);
	window.draw(rectbar1);
	window.draw(bar1);
	window.draw(sp1);
	window.draw(sp2);
	window.draw(sp3);
	window.draw(sp4);
}