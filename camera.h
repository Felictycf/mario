#pragma once
#include "graphics.h"
#include <vector>
class Camera
{
private:
	double nowx, nowy;
	double targetx, targety;
	int map_range;
	bool isshow = false, isrun = false;
	bool render();
	std::vector<std::vector<std::vector<PIMAGE>>>gp; //ͼƬ�ز�
	
public:
	bool update();
	void movecam(double x, double y);
	void start();
	void stop();
	bool finish_init = false;
	Camera();
};

extern Camera camera;

