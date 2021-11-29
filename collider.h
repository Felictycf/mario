#pragma once
#include "global.h"
#include <algorithm>
class Collider
{
private:
	bool isrun = false;
	bool isshow = false;
	bool checkcollide(double x, double y, const Collider* b);
	bool move(double& x, double& y, double dx, double dy);
	double checkonfloor(double prex, double prey);
	double checkleftright();
protected:
	int id;
	bool freeze = true;
	bool is_jump = false;
	double width, height;
	double x, y;   //��ǰλ��
	double vx = 0, vy = 0; //��ǰ�ٶ�
	double fx = 0, fy = 0; //��ǰ����
	double f = 20; //Ħ����
	double m = 1;  //���������
	double maxwx = 20, maxwy = 20; //�����
	bool static_y;
	bool onfloor = false;
	bool out_of_range = true;
public:
	virtual Costume getcostume() = 0;
	virtual std::pair<int, int> getctpos() = 0;
	virtual bool update() = 0;
	void setpos(double x, double y, double width, double height);
	std::pair<double, double> getpos();
	int collider_layer = 0; //��ײͼ��
	//0 ���1 ש��
	void calc();
	bool operator < (const Collider& c);
	void start();
};

