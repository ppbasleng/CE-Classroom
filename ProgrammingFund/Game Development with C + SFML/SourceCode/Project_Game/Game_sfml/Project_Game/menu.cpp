#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"button.h"
#include"entity.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>

extern bool gameclear;
extern bool menumode;
extern int mapstate;
extern bool reset;
extern int testtime;
extern int second;
//class button;
class button newgame("NEWGAME", 180, 50);
class button ready("GO", 80, 50);
class button outgame("EXIT", 80, 50);
class button back("BACK", 80, 50);
class button highscore("HIGHSCORE", 180, 50);
class button about("ABOUT", 180, 50);
class button tomenu("TO MENU", 150, 50);

class menu :public entity{
public:
	bool initgame = true;
	int initdelay = 0;
	int inittime = 0;
	int menutime = 0;
	int mode = -1;
	bool modechange = true;
	bool texting = true;
	bool save = false;
	string name = "player";
	string time = "";
	string score = "";
	void menucontrol(Music&);
	void menudraw(RenderWindow&);
	void highscoreshow();
	void scoreshow();
	void scorewrite();
	void textwindow(Event&);
	menu();
	Text ntext, stext, ttext,label,texted,label2;
	char lastchar;
};
menu::menu() {
	texted.setFont(font);
	texted.setCharacterSize(20);
	texted.setFillColor(sf::Color::White);
	texted.setOutlineColor(Color::Black);
	texted.setOutlineThickness(3);
	texted.setString(name);
	texted.setOrigin(texted.getLocalBounds().width / 2, 0);
	texted.setPosition(400, 200);
	bar1.setSize(Vector2f(5.f, 54.f));
	bar1.setOrigin(Vector2f(2.5f, 19.f));
	bar1.setPosition(texted.getPosition().x + texted.getGlobalBounds().width / 2 + 5, 200);
	bar1.setFillColor(Color::White);
	rectbar1.setSize(Vector2f(380, 64));
	rectbar1.setOrigin(Vector2f(190, 24));
	rectbar1.setPosition(400, 200);
	rectbar1.setFillColor(Color::Color(0,0,0,180));
	label2.setFont(font);
	label2.setCharacterSize(20);
	label2.setFillColor(sf::Color::White);
	label2.setOutlineColor(Color::Black);
	label2.setOutlineThickness(3);
	label2.setString("KING MONGKUT'S INSTITUTE OF TECHNOLOGY \n                              LADKRABANG");
	label2.setOrigin(label2.getLocalBounds().width / 2, label2.getLocalBounds().height / 2);
	label2.setPosition(400, 450);
	label.setFont(font);
	label.setCharacterSize(20);
	label.setFillColor(sf::Color::White);
	label.setOutlineColor(Color::Black);
	label.setOutlineThickness(3);
	ntext.setFont(font);
	ntext.setCharacterSize(20);
	ntext.setFillColor(sf::Color::White);
	ntext.setOutlineColor(Color::Black);
	ntext.setOutlineThickness(3);
	stext.setFont(font);
	stext.setCharacterSize(20);
	stext.setFillColor(sf::Color::White);
	stext.setOutlineColor(Color::Black);
	stext.setOutlineThickness(3);
	ttext.setFont(font);
	ttext.setCharacterSize(20);
	ttext.setFillColor(sf::Color::White);
	ttext.setOutlineColor(Color::Black);
	ttext.setOutlineThickness(3);
	back.rect.setFillColor(Color::Color(0, 0, 0, 0));
	back.rect.setOutlineThickness(0);
	
	outgame.rect.setFillColor(Color::Color(0, 0, 0, 0));
	outgame.rect.setOutlineThickness(0);
	rect.setSize(Vector2f(800, 600));
	rect.setOrigin(400, 300);
	rect.setPosition(400, 300);
	rect.setFillColor(Color::Color(0, 0, 0));
	rect2.setSize(Vector2f(700, 450));
	rect2.setOrigin(350, 200);
	rect2.setPosition(400, 300);
	rect2.setFillColor(Color::Color(123, 134, 145,180));

	text.setCharacterSize(40);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(5);
	text.setString("OTHER WORLD\n     FANTASY");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(400, 150);
	
}
void menu::menucontrol(Music& music) {
	if (menumode) {
		newgame.recieve();
		highscore.recieve();
		about.recieve();
		back.recieve();
		outgame.recieve();
		ready.recieve();

		if (highscore.press) {
			mode = 2;
			modechange = true;
			highscoreshow();
		}
		if (back.press) {
			mode = 0;
			modechange = true;
		}
		if (about.press) {
			mode = 3;
			modechange = true;
		}
		if (newgame.press) {
			mode = 1;
			modechange = true;
		}
		if (ready.press||(mode==1&&Keyboard::isKeyPressed(Keyboard::Enter))) {
			mode = 0;
			modechange = true;
			menumode = false;
			if (name == "" || name == " ") {
				name = "UNNAMED";
			}
		}
		
		if (modechange) {
			newgame.buttonmoveout();
			highscore.buttonmoveout();
			about.buttonmoveout();
			outgame.buttonmoveout();
			back.buttonmoveout();
			ready.buttonmoveout();
			if (mode == -1) {
				label.setString("KMITL");
				label.setCharacterSize(80);
				label.setOrigin(label.getLocalBounds().width / 2, label.getLocalBounds().height / 2);
				label.setPosition(400, 300);
				label.setOutlineColor(Color::Black);
				label.setOutlineThickness(3);
			}
			if (mode == 0) {
				if (initgame) {
					music.openFromFile("res/sound/bgtrack0.ogg");
					music.setLoop(true);
					music.play();
					initgame = false;
				}
				newgame.buttonset(400, 300);
				highscore.buttonset(400, 400);
				about.buttonset(400, 500);
			}
			else if (mode == 1) {
				name = "player";
				texted.setString(name);
				texted.setOrigin(texted.getLocalBounds().width / 2, 0);
				texted.setPosition(400, 200);
				texting = true;
				bar1.setPosition(texted.getPosition().x + texted.getGlobalBounds().width / 2 + 5, 200);
				ready.buttonset(400, 400);
			}
			else if (mode == 3) {
				label.setString("     OWF ASSIGNMENT VER.\nDEVELOP BY\n     PONLAPAT SANGUANSIRIKUL  [62010602]\n     01076002   PROGRAMING  FUNDAMENTAL \n     COMPUTER ENGINEERING, KMITL\n\nSPECIAL THANKS\n     PAT PATPUM [62010615]");
				//label.setString("ASSIGNMENT VER.\nDEVELOP BY\n     PONLAPAT SANGUANSIRIKUL  [62010602]\n     01076002   PROGRAMING  FUNDAMENTAL \n     KING'S MONGKUT INSTITUTE\n     OF TECHNOLOGY  LADKRABANG\n\n SPECIAL THANKS\n PAT PATPUM [62010615]");
				label.setOrigin(label.getLocalBounds().width / 2, label.getLocalBounds().height / 2);
				label.setPosition(400, 335);
			}
			if (mode != 0) {
				back.buttonset(750, 50);
			}
			if (menumode) {
				outgame.buttonset(50, 50);
			}
			
			modechange = false;
		}
		

		
	}
	else if (pause) {
		tomenu.recieve();
		tomenu.buttonset(80, 50);
		tomenu.rect.setFillColor(Color::Color(0, 0, 0, 0));
		tomenu.rect.setOutlineThickness(0);
		if (tomenu.press) {
			menumode = true;
			mode = 0;
			pause = false;
			reset = true;
			music.openFromFile("res/sound/bgtrack0.ogg");
			music.setLoop(true);
			music.setVolume(75);
			music.play();
			outgame.buttonset(50, 50);
		}
	}
	else if (gameover||gameclear) {
		tomenu.recieve();
		tomenu.buttonset(400, 500);
		tomenu.rect.setFillColor(Color::Color(255, 209, 101));
		tomenu.rect.setOutlineThickness(3);
		if (!save) {
			scoreshow();
			scorewrite();
			save = true;
		}
		if (tomenu.press) {
			menumode = true;
			mode = 0;
			gameover = false;
			reset = true;
			music.openFromFile("res/sound/bgtrack0.ogg");
			music.setLoop(true);
			music.setVolume(75);
			music.play();
			outgame.buttonset(50, 50);
			ntext.setPosition(-400, -400);
			ttext.setPosition(-400, -400);
			stext.setPosition(-400, -400);
		}

		
	}
	else {
		mode = 0;
		tomenu.buttonmoveout();
		scoreshow();
	}
	
}
void menu::menudraw(RenderWindow& window) {
	if (menumode) {
	
		outgame.buttondraw(window);
		newgame.buttondraw(window);
		highscore.buttondraw(window);
		about.buttondraw(window);
		back.buttondraw(window);
		ready.buttondraw(window);
		if (mode == 0) {
			window.draw(text);
		}
		else if (mode == 1) {
			window.draw(rectbar1);
			menutime++;
			if (menutime >= 160) {
				menutime = 0;
			}
			if (menutime % 16 >0) {
				window.draw(bar1);
			}
			window.draw(texted);
		}
		else if (mode == 2) {
			window.draw(rect2);
			window.draw(stext);
			window.draw(ntext);
			window.draw(ttext);
			window.draw(label);
			
		}
		else if (mode == 3) {
			window.draw(rect2);
			window.draw(label);
		}
		if (outgame.press) {
			window.close();
		}
		if (mode == -1) {
			label.setFillColor(sf::Color::Color(227, 82, 5, inittime * 8));
			label2.setFillColor(sf::Color::Color(255, 255, 255, inittime * 8));
			if(initgame){
				initdelay++;
				if (initdelay > 16) {
					inittime++;
				}
				if (inittime > 30) {
					initgame = false;
					initdelay = 0;
				}
			}
			else if (!initgame) {
				if (inittime == 0) {
					initdelay++;
				}
				if (initdelay > 32) {
					initdelay = 0;
				}
				if (initdelay == 0) {
					inittime--;
				}
				if (inittime < 0) {
					mode = 0;
					modechange = true;
					label.setCharacterSize(20);
					label.setFillColor(sf::Color::White);
					label.setOutlineColor(Color::Black);
					label.setOutlineThickness(3);
					initgame = true;
					label.setPosition(-400, -400);
				}
			}
			
			
			window.draw(rect);
			window.draw(label);
			window.draw(label2);

			
		}
	}
	else if(pause||gameover||gameclear){
		tomenu.buttondraw(window);
	}
	if (gameover || gameclear) {
		window.draw(stext);
		window.draw(ntext);
		window.draw(ttext);
	}
}
void menu::highscoreshow() {
	int counter = 0;
	ifstream name, score,time;
	string line,N,S,T;
	/*vector<pair<int, pair<string, string>>> vec;
	vector<pair<int, pair<string, string>>>::const_iterator itervec;
	vector<pair<string, string>> vecstr;*/
	vector<tuple<int, string, string>> vec;
	vector<tuple<int, string, string>>::const_iterator iter;
	vector<int> vecint;
	vector<int>::const_iterator iterint;
	vector<string> vecname;

	vector<string> vectime;
	name.open("name.txt");
	score.open("score.txt");
	time.open("time.txt");
	while (getline(score,line)) {
		vecint.push_back((stoi(line)));
	}
	while (getline(name, line)) {
		vecname.push_back(line);
	}
	while (getline(time, line)) {
		vectime.push_back(line);
	}
	for (iterint = vecint.begin(); iterint != vecint.end(); iterint++) {
		vec.push_back(make_tuple(vecint[counter],vecname[counter], vectime[counter]));
		counter++;
	}
	/*for (itername = vecname.begin(); itername != vecname.end(); itername++) {
		vecstr.push_back(make_pair(vecname[counter], vectime[counter]));
		counter++;
	}
	counter = 0;
	for (iterint = vecint.begin(); iterint != vecint.end(); iterint++) {
		vec.push_back(make_pair(vecint[counter],))
	}*/
	sort(vec.begin(), vec.end(), greater<>());
	while (counter > 6) {
		vec.pop_back();
		counter--;
	}
	counter = 0;
	for (iter = vec.begin(); iter != vec.end(); iter++) {
		S += (to_string(get<0>(vec[counter]))) + "\n";
		N += get<1>(vec[counter]) + "\n";
		T += get<2>(vec[counter]) + "\n";
		counter++;
	}
	stext.setString(S);
	ntext.setString(N);
	ttext.setString(T);
	stext.setOrigin(stext.getLocalBounds().width/2, 0);
	ntext.setOrigin(ntext.getLocalBounds().width/2, 0);
	ttext.setOrigin(ttext.getLocalBounds().width/2, 0);
	ntext.setPosition(200, 200);
	ttext.setPosition(400, 200);
	stext.setPosition(600, 200);
	label.setString("NAME              TIME              SCORE");
	label.setOrigin(label.getLocalBounds().width/2, label.getLocalBounds().height/2);
	label.setPosition(400, 150);
	name.close();
	score.close();
	time.close();
}
void menu::textwindow(Event& event) {
	if (mode == 1) {
		if (event.type == Event::EventType::TextEntered) {
			if (texting) {
				name = "";
				texting = false;
				texted.setString(name);
			}
			if (lastchar != event.text.unicode && event.text.unicode == 8 && name.length() > 0)
			{
				lastchar = event.text.unicode;
				name.erase(name.length() - 1);
				texted.setString(name);
				
			}
			else if (lastchar != event.text.unicode &&
				(event.text.unicode >= 'a' && event.text.unicode <= 'z' ||
					event.text.unicode >= 'A' && event.text.unicode <= 'Z' ||
					event.text.unicode >= '0' && event.text.unicode <= '9') && name.length() <= 13)
			{
				lastchar = event.text.unicode;
				name += event.text.unicode;
				texted.setString(name);
				buffer.loadFromFile("res/sound/game/text.wav");
				sound.setBuffer(buffer);
				sound.play();
			}
			texted.setOrigin(texted.getLocalBounds().width / 2, 0);
			texted.setPosition(400, 200);
			bar1.setPosition(texted.getPosition().x + texted.getGlobalBounds().width/2 + 5, 200);
			
		}
		if (event.type == Event::EventType::KeyReleased && lastchar != ' ') {
			lastchar = ' ';
		}

	}
}
void menu::scoreshow() {
	if (gameclear) {
		scorep += 5000;
	}
	ntext.setString("NAME : "+name);
	time = to_string(second);
	ttext.setString("TIME : "+time);
	score = to_string(scorep);
	stext.setString("SCORE : "+score);
	stext.setOrigin(stext.getLocalBounds().width / 2, 0);
	ntext.setOrigin(ntext.getLocalBounds().width / 2, 0);
	ttext.setOrigin(ttext.getLocalBounds().width / 2, 0);
	ntext.setPosition(400, 250);
	ttext.setPosition(400, 320);
	stext.setPosition(400, 390);
}
void menu::scorewrite() {
	ofstream timess, namess, scoress;
	scoress.open("score.txt",ios::app);
	timess.open("time.txt", ios::app);
	namess.open("name.txt", ios::app);
	namess << name << endl;
	timess << time << endl;
	scoress << score << endl;
	cout << "save success" << endl;

	scoress.close();
	timess.close();
	namess.close();
}