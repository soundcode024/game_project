#include "bird.h"
#include <cstdio>

#define movement_multiplier 2
#define x_boundary_limit 84-12 // screen boundary - bird dimension
#define y_boundary_limit 48-11 // ^^

// add the dotted line when its at its position limit

Bird::Bird() : _bird_pos(0, 0) {}; // constructor defines initial values for _bird_pos strut, redundant due to init method

void Bird::init() { // Init method to reset bird position when needed, bird starting position
    _bird_pos.x = 8;
    _bird_pos.y = 18;
}

void Bird::bird(N5110 &lcd, Vector2D coord) {
    //printf("x=%f y=%f \t\t",_bird_pos.x, _bird_pos.y);
    //printf("x=%f y=%f Joystick \n",coord.x, coord.y);
    // y = -1 is up (1 is down), y = -1 is left (1 is right)

    if (coord.x < 0 && _bird_pos.x > 0) { // When the joystick is going left and the bird position is not at the boundary, Bird position decrements by the smaller value ( +2 or current bird position) 
        _bird_pos.x += min(coord.x * movement_multiplier, _bird_pos.x);
    } 
    
    else if (coord.x > 0 && _bird_pos.x < x_boundary_limit) { // Else if joystick is going right and bird is not at the right boundary. Bird position increments by the smaller value (absolue value of –2 or boundary minus the bird position) 
        _bird_pos.x += min(abs(coord.x) * movement_multiplier, x_boundary_limit - _bird_pos.x);
    }

    if (coord.y < 0 && _bird_pos.y > 0) { //When joystick is going up and bird pos is not at the boundary. Bird position decrements by smaller value (absolute value of –2 or current bird position) 
        _bird_pos.y -= min(abs(coord.y) * movement_multiplier, _bird_pos.y);
    } 
    
    else if (coord.y > 0 && _bird_pos.y < y_boundary_limit) { // Else if joystick is going down and bird is not at the bottom boundary. Bird position increments by smaller value of (+2 or boundary minus bird position) 
        _bird_pos.y += min(coord.y * movement_multiplier, y_boundary_limit - _bird_pos.y);
    }

    
    lcd.drawSprite(_bird_pos.x, _bird_pos.y, 11, 12, (int*)bird_sprite);
    //lcd.drawRect(_bird_pos.x, _bird_pos.y, 12, 11, FILL_TRANSPARENT);  // rectangle to draw bird hitbox

}

Vector2D Bird::get_bird_pos() {
    return _bird_pos;
}