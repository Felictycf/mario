#pragma once
#include "global.h"
#include "camera.h"
#include "graphics.h"
#include <algorithm>
#include <vector>
#include <iostream>
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3
class Collider
{
private:
	bool checkcollide(double x, double y, const Collider* b);
	bool move(double& x, double& y, double dx, double dy);
	std::pair<double, bool> checkonfloor(double prex, double prey);
	std::pair<double, bool> checkceiling(double prex, double prey);
	std::pair<double, bool> checkleftright();
	const int collide_re[10][10] = {
		{3, 3, 1, 1, 1, 1},
		{3, 0, 3, 0, 3, 0},
		{1, 3, 1, 0, 0, 0},
		{1, 0, 0, 0, 0, 0},
		{1, 3, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0}
	};
	//0���ųⲻ��⣬1����⣬2���ų⣬3�ų��Ҽ��
	//0 ���1 ש�飬2 ���3 ��ˣ�4 Ģ��/����ש, 5 ���
	//-1��ͼ�㣬���κ����岻������ײ
protected:
	bool is_jump = false;
	double vx = 0, vy = 0; //��ǰ�ٶ�
	double f = 15; //Ħ����
	double m = 1;  //���������
	double maxwx = 20, maxwy = 20; //�����
	bool static_y;
	bool onfloor = false;
	bool out_of_range = true;
	bool last_direction = false; // false��, true ��
	std::vector<Collider*> get_all_contacts();
	virtual bool report_collision(int direction, Collider* target, int target_collider_layer);
	//������ײ (��ײ������ײ������ײ������ײͼ��)
public:
	int id;
	bool isrun = true;  //�Ƿ�����
	bool isshow = true; //�Ƿ���ʾ
	double x, y;   //��ǰλ��
	double width, height; //��ײ����
	double fx = 0, fy = 0; //��ǰ����
	bool freeze = true; //�Ƿ��ڶ���״̬
	virtual Costume getcostume();
	virtual std::pair<double, double> getctpos() = 0;
	virtual bool update();
	virtual void render(double x, double y);
	void setpos(double x, double y, double width, double height);
	std::pair<double, double> getpos();
	int collider_layer = 0; //��ײͼ��
	int show_layer = 0; //��ʾͼ��
	void calc();
	bool operator < (const Collider& c);
	void start();
	std::string name;
};