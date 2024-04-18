#pragma once

#include "mbed.h"
#include "N5110.h"
#include "struts.h"

class Wall {
public:
    Wall();
    void init();
    void draw_wall(N5110 &lcd, int gap_y_pos, int wall_gap, float wall_speed);
    float get_wall_x_pos();
    int get_wall_gap_pos();
    bool get_wall_lifetime();
    void set_x_offset(int offset);

private:

    float _wall_x_pos;
    float _gap_y_pos;
    bool _wall_lifetime;
};

const int bottom_wall[48][10]= {
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 }
};

const int top_wall[48][10]= {
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 }
};