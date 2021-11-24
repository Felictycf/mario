#pragma once
#include "global.h"
#include <algorithm>
class Collider
{
private:
	int width, height;
	bool isrun = false;
	bool isshow = false;
protected:
	int id;
	bool freeze = false;
	double x, y;   //��ǰλ��
	double vx, vy; //��ǰ�ٶ�
	double fx, fy; //��ǰ����
	double f; //Ħ����
	double m = 1;  //���������
	double maxwx = 20, maxwy = 20; //�����
	bool static_y;
public:
	virtual Costume getcostume() = 0;
	virtual std::pair<int, int> getctpos() = 0;
	virtual bool update() = 0;
	void setpos(int x, int y);
	std::pair<double, double> getpos();
	int collider_layer = 0;
	//0 ���1 ש��
	void calc();
	bool operator < (const Collider& c);
	void start();
};

