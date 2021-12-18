#include "mario.h"
#include "keymsg.h"
#include "load_screen.h"
#include "level.h"
#include "musicplayer.h"
Mario::Mario()
{
	id = ++COLLIDER_ID;
	setpos(2, 12, 1, 1);
	freeze = false;
	maxwx = 100, maxwy = 1000;
	out_of_range = false;
	animation_time = level.now_time;
	name = "mario";
	show_layer = 3;
}

void Mario::downgrade()
{
	if (mario_level == 3) {
		change_level(1);
	}
	else if (mario_level == 1) {
		change_level(2);
	}
	else {
		level.death();
		return;
	}
	invincible_time = level.now_time;
}

void Mario::change_level(int target)
{
	//change_time = level.now_time;
	//freeze = true;
	if (mario_level == target) return;
	if (target == 1 || target == 3) {
		y -= 0.5;
		height = 2;
	}
	else {
		y += 0.5;
		height = 1;
	}
	ct.a = target;
	mario_level = target;
}

bool Mario::standup() 
{
	if (mario_level == 2) return false;
	if (!is_squat) false;
	double lsty = y;
	y -= 9.0 / 16.0;
	sy = 0;
	height = 2;
	auto c = get_all_contacts();
	for (auto b : c) {
		if (b->y >= y) continue; //如果碰撞体在人物下方，则忽略
		y = max(y, b->y + (height + b->height) / 2);
	}
	c = get_all_contacts();
	if (!c.empty()) { //起立失败
		y = lsty;
		sy = -18.0 / 16.0;
		height = 14.0 / 16.0;
		return false;
	}
	is_squat = false;
	return true;
}

void Mario::squat() 
{
	if (mario_level == 2) return;
	if (is_squat) false;
	is_squat = true;
	ct.c = 5;
	input_direction = 0;
	y += 9.0 / 16.0;
	sy = -18.0 / 16.0;
	height = 14.0 / 16.0;
}

bool Mario::update()
{
	if (y > 20) {
		level.death();
		return false;
	}
	//摸旗动画
	if (level.finish_time) {
		if (level.finish_move && level.now_time - level.finish_time > 1800) {
			state = "walk";
			fx = 30, fy = 0;
		}else if (level.now_time - level.finish_time > 1500 && !pole_direction) {
			pole_direction = true;
			x = level.map_range - 9.5 - 0.375 + 0.75 * pole_direction;
			ct.b = pole_direction;
		}
		return true;
	}
	//无敌时间判断
	if (level.now_time - invincible_time > 2000) {
		invincible_time = 0;
	}
	key_msg keyMsg;
	//下蹲
	bool flag = keymsg.getmsg(keyMsg, key_down);
	if ((mario_level == 1 || mario_level == 3) && flag) {
		if (keyMsg.msg == key_msg_down && !is_squat) 
			squat();
	}
	if (is_squat && !keymsg.is_down[key_down])
		standup();
	if (onfloor && is_squat) fx = 0, input_direction = 0;
	//向左移动
	flag = keymsg.getmsg(keyMsg, key_left);
	if (flag || keymsg.is_down[key_left]) {
		if (keyMsg.msg == key_msg_down || keymsg.is_down[key_left]) {
			if (input_direction == 0) {
				if ((!onfloor || !is_squat)) {
					input_direction = -1;
					fx = -30;
				}
				else {
					last_direction = true;
				}
				
			}
		}
		if (keyMsg.msg == key_msg_up) {
			if (input_direction == -1) {
				input_direction = 0;
				fx = 0;
			}
		}
	}
	//向右移动
	flag = keymsg.getmsg(keyMsg, key_right);
	if (flag || keymsg.is_down[key_right]) {
		if (keyMsg.msg == key_msg_down || keymsg.is_down[key_right]) {
			if (input_direction == 0) {
				if (!onfloor || !is_squat) {
					input_direction = 1;
					fx = 30;
				}
				else {
					last_direction = false;
				}
				
			}
		}
		if (keyMsg.msg == key_msg_up) {
			if (input_direction == 1) {
				input_direction = 0;
				fx = 0;
			}
		}
	}
	flag = keymsg.getmsg(keyMsg, 'X');
	if (onfloor && state != "jump") state = "walk";
	if (!onfloor && state == "walk") state = "fall";
	if (state == "jump" && level.now_time - jump_time > 200){
		state = "fall";
		is_jump = false;
		fy = 0;
	}
	if (state == "jump" && !jump_sound && level.now_time - jump_time >= 150) {
		musicplayer.play("sound-big_jump");
		jump_sound = true;
	}
	if (flag) {
		if (keyMsg.msg == key_msg_down && !jump_key) {
			if (state != "jump" && state != "fall") {
				jump_key = true;
				fy = -128 - min((fabs(vx) * 1.65), 10);
				jump_sound = false;
				jump_time = level.now_time;
				state = "jump";
				is_jump = true;
			}
		}
		if (keyMsg.msg == key_msg_up) {
			jump_key = false;
			if (state == "jump") {
				if (level.now_time - jump_time < 150 && !jump_sound) {
					jump_sound = true;
					musicplayer.play("sound-small_jump");
				}
				state = "fall";
				is_jump = false;
				fy = 0;
				jump_time = 0;
				
			}
		}
	}
	return false;
}

std::pair<double, double> Mario::getctpos()
{
	return std::make_pair(sx, sy);
}

Costume Mario::getcostume()
{
	int change_time = 150 - maxwx / 2;
	if (state == "pole_fall") {
		if (level.now_time - animation_time >= change_time && fabs(vy) > 1) {
			animation_time = level.now_time;
			ct.c = (ct.c == 7) ? 8 : 7;
		}
	}else if (level.death_time) {
		ct = Costume{ 2, 0, 5 };
		double c = (level.now_time - level.death_time - 800) / 1000.0;
		if (c > 0) {
			sy = ( c * c - c) * 15;
		}
		
	}
	else if (is_squat && mario_level != 2) {
		ct = Costume{ mario_level, last_direction, 5 };
	}
	else if (state == "walk") {
		if (fabs(vx) < 1 && fabs(fx) < f) ct = Costume{ mario_level, last_direction, 6 };
		else {
			if ((vx < 0) ^ (fx < 0) && fabs(fx) > 1 && fabs(vx) > 1) ct = Costume{ mario_level, last_direction, 3 }, animation_time = level.now_time;
			else {
				if (ct.c >= 0 && ct.c <= 2) {
					if (level.now_time - animation_time >= change_time)
						ct = Costume{ mario_level, last_direction, (ct.c + 1) % 3 }, animation_time = level.now_time;
				}
				else {
					ct = Costume{ mario_level, last_direction, 0 };
					animation_time = level.now_time;
				}

			}
		}
	}
	else if (state == "jump" || state == "fall") {
		ct = Costume{ mario_level, last_direction, 4 };
	}
	if (invincible_time) {
		int c = level.now_time - invincible_time;
		if (c > 1000) {
			if ((c / 50) & 1) return Costume{ -1, -1, -1 };
		}
		else {
			if ((c / 100) & 1) return Costume{ -1, -1, -1 };
		}
	}
	
	return ct;
}


bool Mario::report_collision(int direction, Collider* target, int target_collider_layer)
{
	switch (target_collider_layer) {
	case 1:
		if (direction == TOP && target->collider_layer == 1 && state == "jump") {
			if (!jump_sound) {
				jump_sound = true;
				musicplayer.play("sound-small_jump");
			}
			state = "fall";
			is_jump = false;
			fy = 0;
		}
		break;
	case 2:
		if (direction == BOTTOM) {
			vy = -20;
			musicplayer.play("sound-stomp");
		}
		else if (!invincible_time) {
			downgrade();
		}
		break;
	case 3:
		if (level.finish_time) break;
		pole_direction = (x > target->x);
		animation_time = level.now_time;
		x = level.map_range - 9.5 - 0.375 + 0.75 * pole_direction;
		state = "pole_fall";
		fy = -50, fx = 0;
		vy = 7, vx = 0;
		ct = Costume{ mario_level, pole_direction, 7 };
		level.finish();
		break;
	case 4:
		change_level(1);
	}
	return true;
}