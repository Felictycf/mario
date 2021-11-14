#include "graphics.h"
#include "menu.h"
#include "score.h"
#include "timer.h"
#include "coins.h"
#include "world_name.h"
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
	
	for (; is_run(); delay_fps(60)) {
		cleardevice();
		menu.update();
		score.update(); //��ʾ����
		timer.update(); //��ʾʱ��
		coins.update(); //��ʾ���
		world_name.update(); //��ʾ�ؿ���
	}
}
