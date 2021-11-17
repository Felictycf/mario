#pragma once
#include "graphics.h"
#include <vector>
class Camera
{
private:
	double now, target;
	int map_range;
	bool isshow = false, isrun = false;
	bool render();
	std::vector<std::vector<std::vector<PIMAGE>>>gp; //ͼƬ�ز�
	
public:
	bool update();
	void movecam(int target);
	void start();
	void stop();
	Camera();
};

extern Camera camera;

