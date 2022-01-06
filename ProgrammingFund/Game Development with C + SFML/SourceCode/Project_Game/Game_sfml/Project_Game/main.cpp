#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include "entity.h"
#include "player.h"
#include "bot1.h"
#include "bot2.h"
#include "bot3.h"
#include "projectile.h"
#include "gpui.h"
#include "object.h" 
#include "menu.h"
#include "button.h"
#include <math.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include<iostream>
/////////////////////////extern variable//////////////////////////////
bool fullscr = false;
int textscr = 0;
int scorep=0;
int dmgdone = 0;
int dmgrec = 0;
int parrytime = 0;
int timetoscore = 0;
float mousex;
float mousey;
float soundvol = 0;
bool pause = false;
bool menumode = true;
bool gameclear = false;
bool gameover = false;
bool reset = false;
int mapstate = -1;
int testtime = 0;
int second = 0;
using namespace std;
using namespace sf;


int main()
{	

	/////////////////////////////////////////////////////////////////////////////////
	int itercounter = 0;
	
	/////////////////////////////////spawn count/////////////////////////////////////
	int spawncount = 0;
	int randspawn;
	int itemcount = 0;
	////////////////////////////////map moving variable//////////////////////////////
	int mapx = 0, gndy = 0;
	int mapedge;
	
	bool mapchange = true;
	/*int testtime = 0;
	int second = 0;*/
	////////////////////////////////map locking/////////////////////////////////////
	bool insight = false;
	///////////////////////////////////pause game//////////////////////////////////

	
	int bounce = 0;
	/////////////////////////////////////////////////////////////////////////////////
	SoundBuffer buffer1;
	if (!buffer1.loadFromFile("res/sound/player/move.wav")) {
		return EXIT_FAILURE;
	}
	Sound sound;
	sound.setBuffer(buffer1);
	Music music;
	music.setLoop(true);
	/////////////////////////////////////soundtrack load///////////////////////////
	
	
	////////////////////////////////Render Window///////////////////////////////////
	RenderWindow window(VideoMode(800, 600), "OWF");
	window.setFramerateLimit(16);
	Event event;
	
	///////////////////////////////bg//////////////////////////////////
	
	
	////////////////////////Texture Load///////////////////////////// 
	
	Texture texture_Player1;
	if (!texture_Player1.loadFromFile("res/player.png"))
	{
		return EXIT_FAILURE;
	}
	Texture texture_bot1;
	if (!texture_bot1.loadFromFile("res/bot1.png"))
	{
		return EXIT_FAILURE;
	}
	Texture texture_bot2;
	if(!texture_bot2.loadFromFile("res/bot2.png"))
	{
		return EXIT_FAILURE;
	}
	Texture texture_bot3;
	if (!texture_bot3.loadFromFile("res/bot3.png"))
	{
		return EXIT_FAILURE;
	}
	//////////////////////////Font Load////////////////////////
	Font font;
	if (!font.loadFromFile("res/pixeled.ttf"))
	{
		return EXIT_FAILURE;
	}
	////////////////////////////map init///////////////////////
	Sprite map;
	Texture map1,map2,map3;
	map1.loadFromFile("res/bg1.png");
	map2.loadFromFile("res/bg2.png");
	map3.loadFromFile("res/bg3.png");
	map.setTexture(map1);
	Sprite gnd;
	Texture gnd1,gnd2,gnd3;
	gnd1.loadFromFile("res/gnd1.png");
	gnd2.loadFromFile("res/gnd2.png");
	gnd3.loadFromFile("res/gnd3.png");
	gnd.setTexture(gnd1);
	Sprite fg;
	Texture fg2;
	fg2.loadFromFile("res/fg2.png");
	fg.setTexture(fg2);
	fg.setPosition(-3200, 0);
	///////////////////////////////////text making///////////////////////////
	Text timeshow;
	timeshow.setFillColor(Color::White);
	timeshow.setOutlineColor(Color::Black);
	timeshow.setFont(font);
	timeshow.setOrigin(timeshow.getLocalBounds().width / 2, timeshow.getLocalBounds().height / 2);
	timeshow.setPosition(400, 40);
	timeshow.setCharacterSize(30);
	timeshow.setOutlineThickness(3);
	Text text;
	text.setFont(font);
	text.setCharacterSize(40); 
	text.setFillColor(Color::Red);
	text.setPosition(600,120 );
	
	Text score;
	score.setFillColor(Color::White);
	score.setOutlineColor(Color::Black);
	score.setFont(font);
	score.setCharacterSize(20);
	score.setPosition(560, 50);
	score.setOutlineThickness(3);
	////////////////////////////////player setup/////////////////////////////////
	class player Player1;
	Player1.sprite.setTexture(texture_Player1);
	Player1.sprite.setTextureRect(IntRect(0, 0, 160, 160));
	class gpui hpbar;
	hpbar.setupstat(&Player1, 1);
	class gpui stabar;
	stabar.setupstat(&Player1, 2);
	class gpui statusbar;
	statusbar.statuswindowsetup();
	class gpui statuswindow;
	statuswindow.statuswindowsetup();
	class gpui itemicon;
	itemicon.itemiconsetup();
	class gpui gamecontrol;
	gamecontrol.controlsetup();
	//////////////////////////////////////bot1 setup///////////////////////////////////

	class bot1 Bot1;
	Bot1.sprite.setTexture(texture_bot1);
	vector<bot1>::const_iterator iterbot;
	vector<bot1> bot1array;
	
	class bot2 Bot2;
	Bot2.sprite.setTexture(texture_bot2);
	Bot2.sprite.setTextureRect(IntRect(0, 0, 160, 160));
	vector<bot2>::const_iterator iterbot2;
	vector<bot2> bot2array;

	class bot3 Bot3;
	Bot3.sprite.setTexture(texture_bot3);
	vector<bot3>::const_iterator iterbot3;
	vector<bot3> bot3array;

	class object obj;
	vector<object>::const_iterator objiter;
	vector<object> objarray;
	
	//////////////////////////////////world setup/////////////////////////////////////
	class projectile arrow1;
	//////////////////////////////////////GUI setup/////////////////////////////////////
	class button click("EXIT");
	click.buttonset(100, 120);
	
	class menu Menu;

	///////////////////////test////////////////////////

	////////////////////////////////////Game Loop//////////////////////////////////////
	while (window.isOpen())
	{
		//////////////////////////////////////poll event////////////////////////////
		while (window.pollEvent(event))
		{
			mousex = Mouse::getPosition(window).x;
			mousey = Mouse::getPosition(window).y;
			cout << mousex << "," << mousey << endl;


		}
		/////////////////////////////////////Closed///////////////////////////// 
		if (event.type == Event::EventType::Closed)
		{
			window.close();
		}
		//////////////////////////////////////erase///////////////////////////////
		itercounter = 0;
		for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
			if (bot1array[itercounter].dead && bot1array[itercounter].deadtime > 10) {
				bot1array.erase(iterbot);
				scorep += 1000;
				Player1.exp += 4;
				break;
			}
			itercounter++;
		}

		itercounter = 0;
		for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
			if (bot2array[itercounter].dead && bot2array[itercounter].deadtime > 10) {
				bot2array.erase(iterbot2);
				scorep += 1500;
				Player1.exp += 7;
				break;
			}
			itercounter++;
		}
		itercounter = 0;
		for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
			if (bot3array[itercounter].dead && bot3array[itercounter].deadtime > 10) {
				bot3array.erase(iterbot3);
				scorep += 10000;
				gameclear = true;
				music.openFromFile("res/sound/bgtrack4.ogg");
				music.play();
				break;
			}
		}

		itercounter = 0;
		for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
			if (objarray[itercounter].type == 1 || objarray[itercounter].type == 2) {
				if (objarray[itercounter].open && objarray[itercounter].getweapon == 0) {
					objarray.erase(objiter);
					break;
				}
			}
			else {
				if (objarray[itercounter].x < -400) {
					objarray.erase(objiter);
					break;
				}
			}
			itercounter++;

		}
		///////////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::F11) && testtime % 8 == 0) {
			if(!fullscr){
				window.create(sf::VideoMode(800,600), "OWF", Style::Fullscreen);
				window.setFramerateLimit(16);
				fullscr = true;
			}
			else {
				window.create(sf::VideoMode(800, 600), "OWF", Style::Default);
				window.setFramerateLimit(16);
				fullscr = false;
			}
			

		}

		if (reset) {
			Player1.reset();
			bot1array.clear();
			bot2array.clear();
			bot3array.clear();
			objarray.clear();
			arrow1.rect.setPosition(-400, -400);
			arrow1.isfired = false;
			arrow1.rect2.setPosition(-400, -400);
			arrow1.isslash = false;
			second = 0;
			testtime = 0;
			scorep = 0;
			spawncount = 0;
			mapstate = -1;
			mapchange = true;
			Menu.texting = true;
			Menu.save = false;
			gameclear = false;
			reset = false;
		}


		Menu.menucontrol(music);
		Menu.textwindow(event);
		//click.recieve();
		/*if (click.press) {
			click.buttonset(rand() % 80 * 10, rand() % 60 * 10);
		}*/
		
		gamecontrol.kbcontrol(&music,&Player1);
		
		if (!pause && !menumode) {
			
			statuswindow.mousecontrol(&Player1);

			//////////////////////////////////recieve keyboard input//////////////////////////////
			Player1.keyboard_input();
			if (Mouse::isButtonPressed(Mouse::Right)) {
				if (Keyboard::isKeyPressed(Keyboard::N) && testtime % 8 == 0) {

					bot1array.push_back(Bot1);

				}
				if (Keyboard::isKeyPressed(Keyboard::M) && testtime % 8 == 0) {

					bot2array.push_back(Bot2);

				}
				if (Keyboard::isKeyPressed(Keyboard::B) && testtime % 8 == 0) {

					bot3array.push_back(Bot3);

				}
				if (Keyboard::isKeyPressed(Keyboard::T) && testtime % 8 == 0) {
					Player1.currenthp = 0;

				}
				if (Keyboard::isKeyPressed(Keyboard::K)) {
					itercounter = 0;
					for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
						bot1array[itercounter].currenthp = 1;
						itercounter++;
					}
					itercounter = 0;
					for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
						bot2array[itercounter].currenthp = 1;
						itercounter++;
					}
					itercounter = 0;
					for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
						bot3array[itercounter].currenthp = 1;
						itercounter++;
					}

				}
				
			}
			
			//////////////////////////////////////////////update sound////////////////////////////////////////
			Player1.soundcontrol();

			itercounter = 0;
			for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
				bot1array[itercounter].soundcontrol();
				itercounter++;
			}
			itercounter = 0;
			for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
				bot2array[itercounter].soundcontrol();
				itercounter++;
			}
			itercounter = 0;
			for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
				bot3array[itercounter].soundcontrol();
				itercounter++;
			}
			//////////////////////////////////////mapscrolling/////////////////////////////////////
			insight = false;
			itercounter = 0;
			for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
				if (bot2array[itercounter].detect && bot2array[itercounter].x < 800) {
					insight = true;
				}


				itercounter++;
			}
			itercounter = 0;
			for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
				if (bot1array[itercounter].detect && bot1array[itercounter].x > 40 && bot1array[itercounter].x < 760&&!insight) {
					insight = true;
				}
				itercounter++;
			}
			itercounter = 0;
			for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
				
				if (objarray[itercounter].x<300&&!objarray[itercounter].open) {
					
						insight = true;
					
					
				}
				itercounter++;
		
			}
			itercounter = 0;
			for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
				insight = true;
				break;
			}

			//////////////////////////////////////cutscene///////////////////////////////////////
			if (Player1.x > 720 && Player1.x < 940 && mapx <= mapedge && !insight && !mapchange) {
				Player1.moving = true;
				Player1.direction = 0;
				music.setVolume(--soundvol);

			}
			if (Player1.x >= 940) {
				music.stop();
				mapchange = true;
			}
			/////////////////////////////////////mapchanging/////////////////////////////////
			if (mapchange) {
				srand(time(NULL));
				mapstate += 1;
				if (mapstate > 2) {
					mapstate = -1;
					menumode = true;
					Menu.mode = 0;
					gameover = false;
					reset = true;
					music.openFromFile("res/sound/bgtrack0.ogg");
					music.setLoop(true);
					music.setVolume(75);
					music.play();
					outgame.buttonset(50, 50);
					Menu.ntext.setPosition(-400, -400);
					Menu.ttext.setPosition(-400, -400);
					Menu.stext.setPosition(-400, -400);
				}
				switch (mapstate) {
				case 0: music.openFromFile("res/sound/bgtrack1.ogg");
					soundvol = 25;
					music.setVolume(soundvol);
					//music.setLoop(true);
					music.play();
					map.setTexture(map1);
					mapedge = -2300;
					gnd.setTexture(gnd1);
					map.setPosition(0, 0);
					gnd.setPosition(0, 0);
					fg.setPosition(-3200, 0);
					Player1.rect.setPosition(120, 440);
					obj.settypepos(1, 300);
					objarray.push_back(obj);

					break;
				case 1:music.openFromFile("res/sound/bgtrack2.ogg");
					objarray.clear();
					soundvol = 75;
					music.setVolume(soundvol);					
					//music.setLoop(true);
					music.play();
					map.setTexture(map2);
					mapedge = -2300;
					gnd.setTexture(gnd2);
					map.setPosition(0, 0);
					gnd.setPosition(0, 0);
					fg.setPosition(0, 0);
					Player1.rect.setPosition(120, 440);
					obj.settypepos(4, 700);
					objarray.push_back(obj);
					break;
				case 2:
					objarray.clear();
					map.setTexture(map3);
					gnd.setTexture(gnd3);
					mapedge = -720;
					map.setPosition(0, 0);
					gnd.setPosition(0, 0);
					fg.setPosition(-3200, 0);
					Player1.rect.setPosition(120, 440);
					obj.settypepos(2, 150);
					objarray.push_back(obj);
					obj.settypepos(0, 300);
					objarray.push_back(obj);
					break;
				default: break;
				}

				mapchange = false;

			}



			//////////////////////////////////////position control//////////////////////////////////
			if (Player1.x >= 400 && Player1.direction == 0 && mapx > mapedge && !insight) {
				if (Player1.moving) {
					map.move(-Player1.movement_speed / 4, 0);
					fg.move(-Player1.movement_speed, 0);
					gnd.move(-Player1.movement_speed, 0);
					arrow1.rect.move(-Player1.movement_speed, 0);
					itercounter = 0;
					for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
						bot1array[itercounter].rect.move(-Player1.movement_speed, 0);
						bot1array[itercounter].signspr.move(-Player1.movement_speed, 0);
						itercounter++;
					}
					itercounter = 0;
					for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
						bot2array[itercounter].rect.move(-Player1.movement_speed, 0);
						bot2array[itercounter].signspr.move(-Player1.movement_speed, 0);
						bot2array[itercounter].arrow.move(-Player1.movement_speed, 0);
						itercounter++;
					}
					itercounter = 0;
					for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
						objarray[itercounter].rect.move(-Player1.movement_speed, 0);
						itercounter++;
						
					}

				}
				else if (Player1.tumble) {
					map.move(-(4 - Player1.counter)* Player1.movement_speed / 8, 0);
					fg.move(-(4 - Player1.counter) * Player1.movement_speed / 2, 0);
					gnd.move(-(4 - Player1.counter) * Player1.movement_speed / 2, 0);
					arrow1.rect.move(-(4 - Player1.counter) * Player1.movement_speed / 2, 0);
					itercounter = 0;
					for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
						bot1array[itercounter].rect.move(-(4 - Player1.counter) * Player1.movement_speed / 2, 0);
						bot1array[itercounter].signspr.move(-(4 - Player1.counter) * Player1.movement_speed / 2, 0);
						itercounter++;
					}
					itercounter = 0;
					for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
						bot2array[itercounter].rect.move(-(4 - Player1.counter) * Player1.movement_speed / 2, 0);
						bot2array[itercounter].signspr.move(-(4 - Player1.counter) * Player1.movement_speed / 2, 0);
						bot2array[itercounter].arrow.move(-(4 - Player1.counter) * Player1.movement_speed / 2, 0);
						itercounter++;
					}
					itercounter = 0;
					for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
						objarray[itercounter].rect.move(-(4 - Player1.counter)* Player1.movement_speed / 2, 0);
						itercounter++;
						
					}
				}
			}
			else if (Player1.x >= 200 && Player1.direction == 0 && (Player1.moving || Player1.tumble) && mapx > mapedge && !insight) {
				Player1.minimove();
				if (Player1.moving) {
					map.move(-Player1.movement_speed / 8, 0);
					fg.move(-Player1.movement_speed / 2, 0);
					gnd.move(-Player1.movement_speed / 2, 0);
					arrow1.rect.move(-Player1.movement_speed / 2, 0);
					itercounter = 0;
					for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
						bot1array[itercounter].rect.move(-Player1.movement_speed / 2, 0);
						bot1array[itercounter].signspr.move(-Player1.movement_speed / 2, 0);
						itercounter++;
					}
					itercounter = 0;
					for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
						bot2array[itercounter].rect.move(-Player1.movement_speed / 2, 0);
						bot2array[itercounter].signspr.move(-Player1.movement_speed / 2, 0);
						bot2array[itercounter].arrow.move(-Player1.movement_speed / 2, 0);
						itercounter++;
					}
					itercounter = 0;
					for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
						objarray[itercounter].rect.move(-Player1.movement_speed/2, 0);
						itercounter++;
					}

				}
				if (Player1.tumble) {
					map.move(-(4 - Player1.counter) * Player1.movement_speed / 16, 0);
					fg.move(-(4 - Player1.counter) * Player1.movement_speed / 4, 0);
					gnd.move(-(4 - Player1.counter) * Player1.movement_speed / 4, 0);
					arrow1.rect.move(-(4 - Player1.counter) * Player1.movement_speed / 4, 0);
					itercounter = 0;
					for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
						bot1array[itercounter].rect.move(-(4 - Player1.counter) * Player1.movement_speed / 4, 0);
						bot1array[itercounter].signspr.move(-(4 - Player1.counter) * Player1.movement_speed / 4, 0);
						itercounter++;
					}
					itercounter = 0;
					for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
						bot2array[itercounter].rect.move(-(4 - Player1.counter) * Player1.movement_speed / 4, 0);
						bot2array[itercounter].signspr.move(-(4 - Player1.counter) * Player1.movement_speed / 4, 0);
						bot2array[itercounter].arrow.move(-(4 - Player1.counter) * Player1.movement_speed / 4, 0);
						itercounter++;
					}
					itercounter = 0;
					for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
						objarray[itercounter].rect.move(-(4 - Player1.counter) * Player1.movement_speed / 4, 0);
						itercounter++;
					}
				}
			}
			else {
				Player1.move();
			}

			if (Player1.x >= 420 && mapx > mapedge+100 && !insight && !mapchange) {
				int distance = Player1.x - 400;

				Player1.rect.move(-distance / 10, 0);
				map.move(-distance / 40, 0);
				fg.move(-distance / 10, 0);
				gnd.move(-distance / 10, 0);
				arrow1.rect.move(-distance / 10, 0);
				itercounter = 0;
				for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
					bot1array[itercounter].rect.move(-distance / 10, 0);
					bot1array[itercounter].signspr.move(-distance / 10, 0);
					itercounter++;
				}
				itercounter = 0;
				for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
					bot2array[itercounter].rect.move(-distance / 10, 0);
					bot2array[itercounter].signspr.move(-distance / 10, 0);
					bot2array[itercounter].arrow.move(-distance / 10, 0);
					itercounter++;
				}
				itercounter = 0;
				for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
					objarray[itercounter].rect.move(-distance / 10, 0);
					itercounter++;
					
				}

			}
			Player1.movey();

			//////////////////////////////////////////bot1 controling//////////////////////////
			itercounter = 0;
			for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
				bot1array[itercounter].control(&Player1);
				bot1array[itercounter].signcontrol();
				bot1array[itercounter].move();
				itercounter++;
			}
			itercounter = 0;
			for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
				bot2array[itercounter].control(&Player1);
				bot2array[itercounter].signcontrol();
				bot2array[itercounter].move();
				itercounter++;
			}
			itercounter = 0;
			for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
				bot3array[itercounter].control(&Player1);
				bot3array[itercounter].signcontrol();
				bot3array[itercounter].move();
				itercounter++;
			}
			arrow1.checkshot(&Player1);
			arrow1.arrowshot();


			/////////////////////////////////////bot1direction//////////////////////////////////////////////////

			////////////////////////////////position changing receiver//////////////////////////////////////////


			mapx = gnd.getPosition().x;

			//////////////////////////////////////enemy&item spawn/////////////////////////////////

			if (mapstate == 0) {
				if (mapx < -400 && spawncount == 0) {
					bot1array.push_back(Bot1);
					spawncount++;
					obj.settypepos(0, 900);
					objarray.push_back(obj);
				}
				if (mapx < -700 && spawncount == 1) {
					bot1array.push_back(Bot1);
					spawncount++;
				}
				if (mapx < -1000 && spawncount == 2) {
					bot1array.push_back(Bot1);
					spawncount++;
					obj.settypepos(0, 900);
					objarray.push_back(obj);
				}
				if (mapx < -1200 && spawncount == 3) {
					bot1array.push_back(Bot1);
					bot1array.push_back(Bot1);
					bot1array[1].rect.move(300, 0);
					spawncount++;
				}
				if (mapx < -1800 && spawncount == 4) {
					bot2array.push_back(Bot2);
					obj.settypepos(3, 900);
					objarray.push_back(obj);
					obj.settypepos(2, 1100);
					objarray.push_back(obj);
					spawncount++;
				}
			}
			else if (mapstate == 1) {
				if (mapx < -400 && spawncount == 4) {
					bot2array.push_back(Bot2);
					spawncount++;
					obj.settypepos(2, 1000);
					objarray.push_back(obj);
				}
				if (mapx < -700&&spawncount == 5) {
					for (int i = 0; i < 2; i++) {
						randspawn = rand() % 2;
						switch (randspawn) {
						case 0: bot1array.push_back(Bot1); break;
						case 1: bot2array.push_back(Bot2); break;
						default: break;
						}
					}
					itercounter = 0;
					for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
						itercounter++;
						if (itercounter > 1) {
							bot1array[itercounter - 1].rect.move(300,0);
						}
					}
					itercounter = 0;
					for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
						itercounter++;
						if (itercounter > 1) {
							bot2array[itercounter - 1].rect.move(300, 0);
						}
					}
					for (int i = 0; i < 2; i++) {
						randspawn = rand() % 2;
						switch (randspawn) {
						case 0: obj.settypepos(0, 1000); break;
						case 1: obj.settypepos(2, 1000+i*200); break;
						default: break;
						}
						objarray.push_back(obj);
					}
					spawncount++;
				}
				if (mapx < -1100 && spawncount == 6) {
					for (int i = 0; i < 2; i++) {
						randspawn = rand() %10;
						if (randspawn < 7) {
							bot2array.push_back(Bot2);
						}
						else {
							bot1array.push_back(Bot1);
						}
					}
					itercounter = 0;
					for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
						itercounter++;
						if (itercounter > 1) {
							bot1array[itercounter - 1].rect.move(300, 0);
						}
					}
					itercounter = 0;
					for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
						itercounter++;
						if (itercounter > 1) {
							bot2array[itercounter - 1].rect.move(300, 0);
						}
					}
					spawncount++;
				}
				if (mapx < -1600 && spawncount == 7) {
					for (int i = 0; i < 3; i++) {
						randspawn = rand() % 10;
						if (randspawn < 3) {
							bot2array.push_back(Bot2);
						}
						else {
							bot1array.push_back(Bot1);
						}
					}
					itercounter = 0;
					for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
						itercounter++;
						if (itercounter > 1) {
							bot1array[itercounter - 1].rect.move(300, 0);
						}
					}
					itercounter = 0;
					for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
						itercounter++;
						if (itercounter > 1) {
							bot2array[itercounter - 1].rect.move(300, 0);
						}
					}
					spawncount++;
				}
			}
			else if (mapstate == 2) {
				if (mapx < -300 && spawncount == 8) {
					music.openFromFile("res/sound/bgtrack3.ogg");
					bot3array.push_back(Bot3);
					soundvol = 25;
					music.setVolume(soundvol);
					music.play();
					spawncount = 3;
				}
			}

			//////////////////////////////////////updateaction//////////////////////////////////////////

			Player1.updateposition();
			arrow1.updateposition();
			itercounter = 0;
			for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
				bot1array[itercounter].updateposition();
				bot1array[itercounter].calculate(&Player1);
				itercounter++;
			}
			itercounter = 0;
			for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
				bot2array[itercounter].updateposition();
				bot2array[itercounter].calculate(&Player1);
				itercounter++;
			}
			itercounter = 0;
			for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
				bot3array[itercounter].updateposition();
				bot3array[itercounter].calculate(&Player1);
				itercounter++;
			}
			Player1.update_action();
			itercounter = 0;
			for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
				bot1array[itercounter].update_action();
				itercounter++;
			}

			itercounter = 0;
			for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
				bot2array[itercounter].update_action();
				itercounter++;
			}
			itercounter = 0;
			for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
				bot3array[itercounter].update_action();
				itercounter++;
			}

			itercounter = 0;
			for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
				objarray[itercounter].updateposition(&Player1);

				itercounter++;
			}
			

			//////////////////////////////////test text//////////////////////////////////
			/*itercounter = 0;
			for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
				text.setString(to_string(bot1array[itercounter].parryeffect));
				itercounter++;
				break;
			}*/
			//text.setString(to_string(mapx));
			/*itercounter = 0;
			for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
				text.setString(to_string(objarray[itercounter].distance));
				itercounter++;
				break;
			}*/
			

			score.setString("SCORE : " + to_string(scorep));
			timeshow.setString(to_string(second));
			if (second % 10 == 0) {
				timeshow.setOrigin(timeshow.getLocalBounds().width / 2, timeshow.getLocalBounds().height / 2);
				timeshow.setPosition(400, 40);
			}

			hpbar.updatestat(&Player1, 1);
			stabar.updatestat(&Player1, 2);

			itercounter = 0;
			for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
				bot1array[itercounter].checkdamage(&Player1);
				bot1array[itercounter].checkpjtdamage(&arrow1);
				bot1array[itercounter].barcontrol();
				itercounter++;
			}

			
			itercounter = 0;
			for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
				bot2array[itercounter].checkdamage(&Player1);
				bot2array[itercounter].checkpjtdamage(&arrow1);
				bot2array[itercounter].barcontrol();
				itercounter++;
			}

			itercounter = 0;
			for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
				bot3array[itercounter].checkdamage(&Player1);
				bot3array[itercounter].checkpjtdamage(&arrow1);
				bot3array[itercounter].barcontrol();
				itercounter++;
			}

			

			///////////////////////////////////////////windowcontrol//////////////////////////////////
			statuswindow.statuswindow(&Player1);
			itemicon.itemicon(&Player1);

			/////////////////////////////////////////clock by frame counting//////////////////////////////////
			if (!Player1.dead && !gameclear) {
				testtime++;
			}
			if (testtime % 16 == 0&&!Player1.dead&&!gameclear) {
				second++;
				testtime = 0;
			}

		}
		
		//////////////////////////////////////////clearing recent frame///////////////////////////////
		window.clear();
		////////////////////////////////////////draw sprites ,shapes and texts/////////////////////////////////////////////
		
		window.draw(map);
		window.draw(gnd);
		if (!menumode) {
			itercounter = 0;
			for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
				///window.draw(objarray[itercounter].rect);////////
				window.draw(objarray[itercounter].sprite);
				itercounter++;
			}

			itercounter = 0;
			for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
				///window.draw(bot1array[itercounter].rect);////////
				window.draw(bot1array[itercounter].sprite);
				window.draw(bot1array[itercounter].rectbar1);
				window.draw(bot1array[itercounter].bar1);
				window.draw(bot1array[itercounter].rectbar2);
				window.draw(bot1array[itercounter].bar2);
				window.draw(bot1array[itercounter].signspr);

				itercounter++;
			}
			itercounter = 0;
			for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
				///window.draw(bot2array[itercounter].rect);////////
				window.draw(bot2array[itercounter].sprite);
				window.draw(bot2array[itercounter].rectbar1);
				window.draw(bot2array[itercounter].bar1);
				window.draw(bot2array[itercounter].rectbar2);
				window.draw(bot2array[itercounter].bar2);
				window.draw(bot2array[itercounter].signspr);
				window.draw(bot2array[itercounter].arrow);
				itercounter++;
			}

			itercounter = 0;
			for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
				//////window.draw(bot3array[itercounter].rect);////////
				window.draw(bot3array[itercounter].sprite);
				window.draw(bot3array[itercounter].rectbar1);
				window.draw(bot3array[itercounter].bar1);
				window.draw(bot3array[itercounter].rectbar2);
				window.draw(bot3array[itercounter].bar2);
				window.draw(bot3array[itercounter].signspr);
				window.draw(bot3array[itercounter].axe);
				itercounter++;
			}


			///window.draw(Player1.rect);////////////
			window.draw(Player1.sprite);
			window.draw(hpbar.effect);
			///window.draw(arrow1.rect);/////////
			window.draw(arrow1.sprite);
			//window.draw(arrow1.rect2);
			window.draw(arrow1.effect);


			itercounter = 0;
			for (iterbot = bot1array.begin(); iterbot != bot1array.end(); iterbot++) {
				window.draw(bot1array[itercounter].effect);
				itercounter++;
			}

			itercounter = 0;
			for (iterbot2 = bot2array.begin(); iterbot2 != bot2array.end(); iterbot2++) {
				window.draw(bot2array[itercounter].effect);
				itercounter++;
			}
			itercounter = 0;
			for (iterbot3 = bot3array.begin(); iterbot3 != bot3array.end(); iterbot3++) {
				window.draw(bot3array[itercounter].effect);
				itercounter++;
			}

			itercounter = 0;
			for (objiter = objarray.begin(); objiter != objarray.end(); objiter++) {
				window.draw(objarray[itercounter].signspr);
				itercounter++;
			}



			

		}
			window.draw(fg);
			window.draw(text);
		if (!menumode) {
		
		
			if (statuswindow.togglestate != 0 || statuswindow.showstate) {
				statuswindow.draw(window);
			}
			

			if (!Player1.dead && !gameclear) {
				window.draw(hpbar.rect);
				window.draw(hpbar.rect2);
				window.draw(stabar.rect);
				window.draw(stabar.rect2);
				window.draw(stabar.text);
				window.draw(hpbar.text);
				window.draw(score);
				window.draw(timeshow);
				if (Player1.getbow) {
					window.draw(itemicon.sp1);
					window.draw(itemicon.text);
				}
				window.draw(itemicon.sp2);
				window.draw(itemicon.sp3);
				window.draw(itemicon.sp4);
				window.draw(itemicon.sp5);
				
				window.draw(itemicon.value);
			}
		}
		/////////////////////////////////////////gamecontrol////////////////////////////////////////
		if (pause || Player1.dead||gameclear) {
			window.draw(gamecontrol.rect);
			window.draw(gamecontrol.text);
		}
		Menu.menudraw(window);
		//click.buttondraw(window); ///////////new things//////////
		///////////////////////////////////////display current frame/////////////////////////////////
		window.display(); 
		
	}
	return EXIT_SUCCESS;
}
