#include "graphics.h"
#include "menu.h"
#include "headers.h"
#include "load_screen.h"
#include "global.h"
#include <cstdio>

int main()
{
	// ��ͼ���ڳ�ʼ��
	initgraph(800, 600);
	setbkcolor(EGERGB(107, 140, 255));
	setfillcolor(EGERGB(0, 0, 0));
	setcaption("Super mario Bros");

	setfont(-30, 20, "FixedsysTTF");
	setcolor(WHITE);				//���ֵ���ɫ
	setbkmode(TRANSPARENT);			//�������ֱ���ɫΪ͸��	
	
	for (; is_run(); delay_fps(60)) {
		cleardevice();
		menu.update();
		load_screen.update();
		score.update(); //��ʾ����
		timer.update(); //��ʾʱ��
		coins.update(); //��ʾ���
		world_name.update(); //��ʾ�ؿ���
	}
}
