#include "graphics.h"
#include "menu.h"
#include "global.h"
#include <cstdio>

int main()
{
	// ��ͼ���ڳ�ʼ��
	initgraph(800, 600);
	setbkcolor(EGERGB(107, 140, 255));
	setcaption("Super mario Bros");

	setfont(-30, 20, "FixedsysTTF");
	setcolor(WHITE);				//���ֵ���ɫ
	setbkmode(TRANSPARENT);			//�������ֱ���ɫΪ͸��	
	Menu menu;
	for (; is_run(); delay_fps(60)) {
		cleardevice();
		menu.update();
		SCORE += 1;
	}
}
