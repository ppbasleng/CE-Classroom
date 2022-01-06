#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"entity.h"
#include<iostream>
//RenderWindow window;
extern float mousex, mousey;
//using namespace sf;
class button :public entity{
public:
	
	bool bon = false;
	bool press = false;
	int bouncetime = 17;
	float buttonsizex = 80;
	float buttonsizey = 40;
	int bxmin, bxmax, bymin, bymax;
	button(string, int, int);
button(string);
button();
void buttonset(int,int);
void buttonmoveout();
void recieve();
void buttondraw(RenderWindow&);

};
button::button(string word) {
	text.setFillColor(Color::White);
	text.setOutlineColor(Color::Black);
	rect.setFillColor(Color::Color(255, 209, 101));
	rect.setOutlineColor(Color::Black);
	rect.setOutlineThickness(3);
	text.setOutlineThickness(3);
	rect.setSize(Vector2f(buttonsizex, buttonsizey));
	text.setString(word);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	rect.setOrigin(rect.getLocalBounds().width/2,rect.getLocalBounds().height/2);
	
}
button::button(string word,int sizex,int sizey) {
	text.setFillColor(Color::White);
	text.setOutlineColor(Color::Black);
	rect.setFillColor(Color::Color(255, 209, 101));
	rect.setOutlineColor(Color::Black);
	rect.setOutlineThickness(3);
	text.setOutlineThickness(3);
	buttonsizex = sizex;
	buttonsizey = sizey;
	rect.setSize(Vector2f(buttonsizex, buttonsizey));
	text.setString(word);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);

}
button::button() {
	rect.setSize(Vector2f(buttonsizex, buttonsizey));
	text.setOrigin(buttonsizex / 2, buttonsizey / 2);
	rect.setOrigin(buttonsizex / 2, buttonsizey / 2);
}
void button::buttonset(int x, int y) {
	rect.setPosition(x, y);
	text.setPosition(rect.getPosition().x, rect.getPosition().y);
	bxmin = rect.getPosition().x - buttonsizex / 2;
	bxmax = rect.getPosition().x + buttonsizex / 2;
	bymin = rect.getPosition().y - buttonsizey / 2;
	bymax = rect.getPosition().y + buttonsizey / 2;
	//cout << bxmin << " " << bymin << endl;
	//cout << bxmax << " " << bymax << endl;
	bon = true;
}
void button::buttonmoveout() {
	bon = false;
	rect.setPosition(1000, 1000);
	text.setPosition(rect.getPosition().x, rect.getPosition().y);
}
void button::recieve() {


	if (bon) {
		
			if (mousex >= bxmin && mousex <= bxmax && mousey >= bymin && mousey <= bymax && bouncetime == 0 && !press) {
				//cout << "inrangetopress" <<bxmin<<" "<<bymin<< endl;
				if (Mouse::isButtonPressed(Mouse::Left) ) {
					
					
					bouncetime = 1;
					buffer.loadFromFile("res/sound/game/click.wav");
					sound.setBuffer(buffer);
					sound.play();
				}
			}
		
		
	}
	if (bouncetime == 2) {
		press = true;
	}
	if (bouncetime == 3) {
		//std::cout << "release" << std::endl;
		press = false;
	}
	if (bouncetime > 0) {
		bouncetime++;
	}
	
	if (bouncetime > 8) {
		bouncetime = 0;
		
	}
}
void button::buttondraw(RenderWindow& window) {
	
	window.draw(rect);
	window.draw(text);
}
