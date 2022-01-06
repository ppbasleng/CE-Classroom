#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace sf;

class entity 
{
public :
	RectangleShape rect,rect2;
	RectangleShape rectbar1, bar1, rectbar2, bar2;
	Sprite sprite,signspr,signstun,effect,effect2;
	Text text,value;
	Font font;
	Texture caution,stun,efx,item;
	Sound sound,sound2;
	SoundBuffer buffer,buffer2;
	entity();
	void setup();
};
entity::entity() {
	sound.setVolume(50);
	sound2.setVolume(50);
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	value.setFont(font);
	value.setCharacterSize(20);
	value.setFillColor(sf::Color::Black);
	signspr.setTexture(caution);
	effect.setTexture(efx);
	effect.setOrigin(80, 80);
	font.loadFromFile("res/pixeled.ttf");
	//stab.loadFromFile("res/stabperk.png");
	
}

	
	
