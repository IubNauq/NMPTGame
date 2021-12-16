#ifndef _SOPHIA_H
#define _SOPHIA_H

class SOPHIA {
public:
	int x, y;
	int width, height;
	int movex, movey;
	int animdelay, animcount;
	int direction;	//  4: left, 6: right, 48: left-up, 68: right-up
	int hp;

	int gun_x, gun_y;
	int wheelleft_x, wheelleft_y;
	int wheelright_x, wheelright_y;
	int midwheel_x, midwheel_y;
	int body_x, body_y;

	int wheelcurframe, wheellastframe;

	void Update_wheel();
	void Update_body();

	void move_left();
	void move_right();
	void move_left_up();
	void move_right_up();
};

#endif