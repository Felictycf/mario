#pragma once
#include "collider.h"
#include "global.h"
#include <vector>
#include <iostream>
class Mario :
	public Collider
{
private:
	int jump_time = 0;
	std::string state = "walk";
	double sx = 0, sy = 0;
	Costume ct = Costume{2, 0, 6};
	int input_direction = 0; //输入方向键方向
	int mario_level = 2;     //马里奥等级
	int animation_time = 0;      //动画时间戳
	int change_time = 0;         //改变等级时间戳
	int invincible_time = 0;     //无敌时间戳
	int invincible_animation_time = 0; //无敌动画闪烁时间戳
	bool jump_key = false;   
	bool jump_sound = false;
	bool pole_direction;     //摸旗方向
	bool is_squat = false; //是否下蹲
	bool is_dash = false; //是否处于冲刺状态
	void downgrade(); //丢失状态
	bool standup();   //尝试起立
	void squat(); //下蹲
	void change_level(int target);
protected:
	bool report_collision(int direction, Collider* target, int target_collider_layer);
public:
	Costume getcostume();
	std::pair<double, double> getctpos();
	bool update();
	std::vector<Costume>costumes;
	Mario();
	int show_layer = 0;
};

