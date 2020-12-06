#include<stdio.h>
#include<bangtal>
#include <iostream>
#include <cstdlib>

using namespace bangtal;

int gamestart = 0;
int movable = 0;


int bx = 600, by = 150, b = 50;
int px = 1280, py = 0, showp = 0;

class Meteor {
public :
	int size;
	int x, y;
	int	dualibility;
	int speed;
	ObjectPtr obj;

	Meteor(int _s, int _x, int _y, int _d, int _p) {
		size = _s;
		x = _x;
		y = _y;
		dualibility = _d;
		speed = _p;
	};
};
Meteor m1(40, 1300, 300, 1, 20);
Meteor m2(40, 1300, 200, 1, 40);
Meteor m3(40, 1300, 100, 1, 50);
Meteor m4(70, 1300, 500, 3, 30);
Meteor m5(70, 1400, 150, 3, 40);

class SpaceShip {
public :
	int sizex;
	int sizey;
	int x, y;
	int dualibility;
	int speed;
	ObjectPtr obj;

	SpaceShip(int _sx, int _sy, int _x, int _y, int _d, int _p) {
		sizex = _sx;
		sizey = _sy;
		x = _x;
		y = _y;
		dualibility = _d;
		speed = _p;
	};
};
SpaceShip spaceship(250, 130, 100, 300, 1, 20);


//폭발제어, 폭발 시간차
int exm1 = 0;
int expt1 = 0;

int exm2 = 0;
int expt2 = 0;
int showm2 = 0;

int exm3 = 0;
int expt3 = 0;
int showm3 = 0;

int exm4 = 0;
int expt4 = 0;
int showm4 = 0;

int exm5 = 0;
int expt5 = 0;
int showm5 = 0;



int main() {
	
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	auto scene0 = Scene::create("배경", "Images/게임설명배경.png");
	auto scene1 = Scene::create("배경", "Images/우주배경.png");

	auto gametimer = Timer::create(30);

	auto planet = Object::create("Images/planet.png", scene1, px, py, 0); 

	m1.obj = Object::create("Images/운석.png", scene1, m1.x, m1.y, 1); m1.obj->setScale(0.1f);
	m2.obj = Object::create("Images/운석.png", scene1, m2.x, m2.y, 0); m2.obj->setScale(0.1f);
	m3.obj = Object::create("Images/운석.png", scene1, m3.x, m3.y, 0); m3.obj->setScale(0.1f);
	m4.obj = Object::create("Images/운석.png", scene1, m4.x, m4.y, 0); m4.obj->setScale(0.2f);
	m5.obj = Object::create("Images/운석.png", scene1, m5.x, m5.y, 0); m5.obj->setScale(0.2f);
	
	auto explode1 = Object::create("Images/폭발2.png", scene1, m1.x, m1.y, 0); explode1->setScale(0.1f);
	auto explode2 = Object::create("Images/폭발2.png", scene1, m2.x, m2.y, 0); explode2->setScale(0.1f);
	auto explode3 = Object::create("Images/폭발2.png", scene1, m3.x, m3.y, 0); explode3->setScale(0.1f);
	auto explode4 = Object::create("Images/폭발2.png", scene1, m4.x, m4.y, 0); explode4->setScale(0.2f);
	auto explode5 = Object::create("Images/폭발2.png", scene1, m5.x, m5.y, 0); explode5->setScale(0.2f);

	spaceship.obj = Object::create("Images/우주선.png", scene1, spaceship.x, spaceship.y, 1); spaceship.obj->setScale(0.3f);

	auto startbutton = Object::create("Images/start.png", scene0, bx, by, 1);
	auto endbutton = Object::create("Images/end.png", scene0, bx, by - b, 1);
	auto clear = Object::create("Images/clear.png", scene1, bx - 400, by + 200, 0); clear->setScale(2);


	//우주선 이동
	scene1->setOnKeyboardCallback([&](ScenePtr scene, int key, bool pressed)->bool {
		if (movable) {
			switch (key)
			{
			case 4:
				if (spaceship.x < 1100) {
					spaceship.x += 20;
					spaceship.obj->locate(scene1, spaceship.x, spaceship.y);
				}
				break;//right
			case 1:
				if (spaceship.x > 100) {
					spaceship.x -= 20;
					spaceship.obj->locate(scene1, spaceship.x, spaceship.y);
				}
				break;//left
			case 23:
				if (spaceship.y < 560) {
					spaceship.y += 20;
					spaceship.obj->locate(scene1, spaceship.x, spaceship.y);
				}
				break;//up
			case 19:
				if (spaceship.y > 0) {
					spaceship.y -= 20;
					spaceship.obj->locate(scene1, spaceship.x, spaceship.y);
				}
				break; //down
			default:
				break;
			}
		}
		return true;
	});

	//게임 플레이
	static int count = 0;
	auto timer1= Timer::create(0.1f);
	timer1->setOnTimerCallback([&](TimerPtr t)->bool {

		//등장시간 제어
		if (count == 50) {
			showm2 = 1; m2.obj->show();
		}
		else if (count == 100) {
			showm3 = 1; m3.obj->show();
			m1.speed += 10; m2.speed += 10; m3.speed += 10;
		}
		else if (count == 170) {
			showm4 = 1; m4.obj->show();
			showm5 = 1; m5.obj->show();
		}
		else if (count == 260) {
			showp = 1; planet->show();
		}

		m1.x = m1.x - m1.speed;
		m1.obj->locate(scene1, m1.x, m1.y);		

		if (showm2) {
			m2.x = m2.x - m2.speed;
			m2.obj->locate(scene1, m2.x, m2.y);
		}
		if (showm3) {
			m3.x = m3.x - m3.speed;
			m3.obj->locate(scene1, m3.x, m3.y);
		}
		if (showm4) {
			m4.x = m4.x - m4.speed;
			m4.obj->locate(scene1, m4.x, m4.y);
		}
		if (showm5) {
			m5.x = m5.x - m5.speed;
			m5.obj->locate(scene1, m5.x, m5.y);
		}
		if (showp) {
			px -= 20;
			planet->locate(scene1, px, py);
		}


		
		//폭발 모션
		if (exm1) {
			explode1->show();
			explode1->locate(scene1, m1.x, m1.y);
			expt1++;
				if (expt1 > 3) {
					explode1->hide();
					expt1 = 0;
					exm1 = 0;
					m1.x = -50;
				}
		}
		if (exm2) {
			explode2->show();
			explode2->locate(scene1, m2.x, m2.y);
			expt2++;
			if (expt2 > 3) {
				explode2->hide();
				expt2 = 0;
				exm2 = 0;
				m2.x = -50;
			}
		}
		if (exm3) {
			explode3->show();
			explode3->locate(scene1, m3.x, m3.y);
			expt3++;
			if (expt3 > 3) {
				explode3->hide();
				expt3 = 0;
				exm3 = 0;
				m3.x = -50;
			}
		}
		if (exm4) {
			explode4->show();
			explode4->locate(scene1, m4.x, m4.y);
			expt4++;
			if (expt4 > 3) {
				explode4->hide();
				expt4 = 0;
				exm4 = 0;
				m4.x = -50;
			}
		}
		if (exm5) {
			explode5->show();
			explode5->locate(scene1, m5.x, m5.y);
			expt5++;
			if (expt5 > 3) {
				explode5->hide();
				expt5 = 0;
				exm5 = 0;
				m5.x = -50;
			}
		}



		//충돌 
		if (m1.x < spaceship.x + spaceship.sizex && m1.x + m1.size > spaceship.x  && m1.y + m1.size > spaceship.y && m1.y < spaceship.y + spaceship.sizey) {
			spaceship.obj->setImage("Images/폭발1.png");
			
			timer1->stop();
			gametimer->stop();
			movable = 0;

			startbutton->show();
			endbutton->show();

			//실패 
		}
		else if (m1.x < -50) {
			m1.obj->show();
			m1.x = 1500 + rand()%100; m1.y = 500 + rand() % 100; //운석 위치 초기화
			m1.obj->locate(scene1, m1.x, m1.y);
		
			t->set(0.1f);
			t->start(); 
		}
		else if (m2.x < spaceship.x + spaceship.sizex && m2.x + m2.size > spaceship.x && m2.y + m2.size > spaceship.y && m2.y < spaceship.y + spaceship.sizey) {
			spaceship.obj->setImage("Images/폭발1.png");
			//실패 

			timer1->stop();
			gametimer->stop();
			movable = 0;

			startbutton->show();
			endbutton->show();
		}
		else if (m2.x < -50) {
			m2.obj->show();
			m2.x = 1300 + rand() % 100; m2.y = 1100 + rand() % 150;
			m2.obj->locate(scene1, m2.x, m2.y);
			t->set(0.1f);
			t->start();
		}
		else if (m3.x < spaceship.x + spaceship.sizex && m3.x + m3.size > spaceship.x && m3.y + m3.size > spaceship.y && m3.y < spaceship.y + spaceship.sizey) {
			spaceship.obj->setImage("Images/폭발1.png");
			//실패 
			movable = 0;

			timer1->stop();
			gametimer->stop();

			
			startbutton->show();
			endbutton->show();
		}
		else if (m3.x < -50) {
			m3.obj->show();
			m3.x = 1300 + rand() % 100; m3.y = 500 - rand() % 150;
			m3.obj->locate(scene1, m3.x, m3.y);
			t->set(0.1f);
			t->start();
		}
		else if (m4.x < spaceship.x + spaceship.sizex && m4.x + m4.size > spaceship.x && m4.y + m4.size > spaceship.y && m4.y < spaceship.y + spaceship.sizey) {
			spaceship.obj->setImage("Images/폭발1.png");
			//실패 
			movable = 0;

			timer1->stop();
			gametimer->stop();

						startbutton->show();
			endbutton->show();
		}
		else if (m4.x < -50) {
			m4.obj->show();
			m4.x = 1300 + rand() % 100; m4.y = 100 + rand() % 150;
			m4.obj->locate(scene1, m4.x, m4.y);
			t->set(0.1f);
			t->start();
		}
		else if (m5.x < spaceship.x + spaceship.sizex && m5.x + m5.size > spaceship.x && m5.y + m5.size > spaceship.y && m5.y < spaceship.y + spaceship.sizey) {
			spaceship.obj->setImage("Images/폭발1.png");
			//실패 
			movable = 0;

			timer1->stop();
			gametimer->stop();

			startbutton->show();
			endbutton->show();
		}
		else if (m5.x < -50) {
			m5.obj->show();
			m5.x = 1300 + rand() % 100; m5.y = 500 - rand() % 150;
			m5.obj->locate(scene1, m5.x, m5.y);
			t->set(0.1f);
			t->start();
		}
		else {
			t->set(0.1f);
			t->start(); //게임 진행
		}
		
		count += 1;

		return true;
	});

	//클릭으로 운석 파괴	
	m1.obj->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction) -> bool{
		if (gamestart) {
			m1.obj->hide();
			exm1 = 1;
		}
		return true;
	});
	m2.obj->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction) -> bool {
		if (gamestart) {
			m2.obj->hide();
			exm2 = 1;
		}
		return true;
		});
	m3.obj->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction) -> bool {
		if (gamestart) {
			m3.obj->hide();
			exm3 = 1;
		}
		return true;
		});
	m4.obj->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction) -> bool {
		if (gamestart) {
			m4.dualibility -= 1;
			if (!m4.dualibility) {
				m4.obj->hide();
				m4.dualibility = 3;
				exm4 = 1;
			}
		}
		return true;
		});
	m5.obj->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction) -> bool {
		if (gamestart) {
			m5.dualibility -= 1;
			if (!m5.dualibility) {
				m5.obj->hide();
				m5.dualibility = 3;
				exm5 = 1;
			}
		}
		return true;
		});



	gametimer->setOnTimerCallback([&](TimerPtr t)->bool {
		
		gamestart = 0;
		movable = 0;

		timer1->stop();

		startbutton->show();
		endbutton->show();
		clear->show();
		return true;
		});

	startbutton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (!gamestart) {
			gamestart = 1;
			movable = 1;

			startbutton->locate(scene1, bx, by);
			endbutton->locate(scene1, bx, by - b);
			startbutton->hide();
			endbutton->hide();
		
			scene1->enter();
			timer1 -> set(0.1f);
			timer1->start();
			showTimer(gametimer);
			gametimer->start();

		}
		else {
			movable = 1;
			spaceship.obj->setImage("Images/우주선.png");
			bx = 600, by = 150, b = 50;
			px = 1280, py = 0, showp = 0, planet->hide();
			m1.x = 1300, m1.y = 300;
			m2.x = 1300, m2.y = 200, m2.obj->hide();
			m3.x = 1300, m3.y = 100, m3.obj->hide();
			m4.x = 1300, m4.y = 500, m4.obj->hide();
			m5.x = 1300, m5.y = 150, m5.obj->hide();
			spaceship.x = 100, spaceship.y = 300;
			spaceship.obj->locate(scene1, spaceship.x, spaceship.y);
	
			exm1 = 0;
			expt1 = 0;
			exm2 = 0;
			expt2 = 0;
			showm2 = 0;
			exm3 = 0;
			expt3 = 0;
			showm3 = 0;
			exm4 = 0;
			expt4 = 0;
			showm4 = 0;
			exm5 = 0;
			expt5 = 0;
			showm5 = 0;
			count = 0;
			gamestart = 1;

			startbutton->hide();
			endbutton->hide();
			gametimer->set(30);
			gametimer->start();
			timer1->set(0.1f);
			timer1->start();

		}
		return true;
	});
	endbutton->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		showMessage("Clear Game");
		endGame();

		return true;
	});



	startGame(scene0);
}