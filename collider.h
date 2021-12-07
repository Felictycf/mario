#pragma once
#include "global.h"
#include <algorithm>
#include <iostream>
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3
class Collider
{
private:
	bool isrun = false;
	bool isshow = false;
	bool checkcollide(double x, double y, const Collider* b);
	bool move(double& x, double& y, double dx, double dy);
	double checkonfloor(double prex, double prey);
	double checkceiling(double prex, double prey);
	double checkleftright();
	const int collide_re[10][10] = {
		{3, 3, 1}, 
		{3, 0, 3},
		{1, 3, 0}
	};
	//0����⣬1��1��⣬2���ų⣬3�ų��Ҽ��
	//0 ���1 ש�飬2 ����
	//-1��ͼ�㣬���κ����岻������ײ
protected:
	int id;
	bool freeze = true;
	bool is_jump = false;
	double width, height;
	double vx = 0, vy = 0; //��ǰ�ٶ�
	double fx = 0, fy = 0; //��ǰ����
	double f = 15; //Ħ����
	double m = 1;  //���������
	double maxwx = 20, maxwy = 20; //�����
	bool static_y;
	bool onfloor = false;
	bool out_of_range = true;
	bool last_direction = false; // false��, true ��
	virtual bool report_collision(int direction, Collider* target, int target_collider_layer) = 0;
public:
	double x, y;   //��ǰλ��
	virtual Costume getcostume() = 0;
	virtual std::pair<double, double> getctpos() = 0;
	virtual bool update() = 0;
	void setpos(double x, double y, double width, double height);
	std::pair<double, double> getpos();
	int collider_layer = 0; //��ײͼ��
	void calc();
	bool operator < (const Collider& c);
	void start();
	std::string name;
};

