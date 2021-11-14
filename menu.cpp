#include "global.h"
#include "menu.h"
#include "graphics.h"	
#include "score.h"
#include "timer.h"
#include "coins.h"
#include "world_name.h"
#include <cstdio>
#include <iostream>

void Menu::reset()
{
	NOW_SCENR = 0;
	this->isshow = true;
	music.Play();
}

Menu::Menu()
{
	
	this->title = newimage();
	getimage(this->title, "resources\\graphics\\title_screen.png", 1, 60, 176, 88);
	zoomImage(this->title, 2.5);
	music.OpenFile("resources\\music\\start.mp3");
	music.Play();
}


bool Menu::render()
{
	if (!this->isshow) return false;
	score.update(); //��ʾ����
	timer.update(); //��ʾʱ��
	coins.update(); //��ʾ���
	world_name.update(); //��ʾ�ؿ���
	//putimage_withalpha(NULL, this->title, 170, 100, 2, 150, 440, 220); //��ʾ����
	putimage_withalpha(NULL, this->title, 170, 100); //��ʾ����
	xyprintf(272, 360, "1 PLAYER GAME");
	xyprintf(272, 405, "2 PLAYER GAME");
	char topscore[20];
	sprintf(topscore, "TOP - %06d" , TOP_SCORE);
	xyprintf(290, 465, topscore);

	return true;
}

bool Menu::update()
{
	if (!this->isshow) music.Stop();
	else {
		if (music.GetPlayStatus() == MUSIC_MODE_STOP) {
			//��ͷ��ʼ����
			music.Play(0);
		}
	}
	return this->render();
}

void Menu::setshowstate(bool show)
{
	if (show) this->reset();
	else {
		music.Stop();
		this->isshow = false;
	}
}
