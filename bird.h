#pragma once

#include "mbed.h"
#include "N5110.h"
#include "struts.h"
#include <cstdlib>
#include <algorithm> // maybe done need this?

class Bird {

public:
    Bird();
    void bird(N5110 &lcd, Vector2D coord);
    Vector2D get_bird_pos();
private:

};



const int bird_sprite[11][12]= {
	{ 0,0,0,0,0,0,0,0,1,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,0,0 },
	{ 0,0,0,0,0,0,1,1,1,1,1,0 },
	{ 0,0,0,0,0,1,1,1,1,0,1,1 },
	{ 0,0,0,0,1,1,1,1,1,1,1,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,0 },
	{ 0,0,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,0,0 },
	{ 1,1,0,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,0,1,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,1,0,0,0 }
};
