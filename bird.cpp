#include "bird.h"
#include <cstdio>

float bird_x_pos = 21, bird_y_pos = 24; // initial position of the bird

#define movement_multiplier 2
#define x_boundary_limit 32 
#define y_boundary_limit 38 

void bird(N5110 &lcd, Vector2D coord) {
    printf("x=%f y=%f       ",bird_x_pos, bird_y_pos);
    printf("x=%f y=%f Joystick \n",coord.x, coord.y);

    // 1 is down on the y (-1 is up)    1 is left on the x (-1 is right)

    if (coord.x > 0 && bird_x_pos > 0) { // When the joystick is going left and the bird position is not at the boundary, Bird position decrements by the smaller value ( +2 or current bird position) 
        bird_x_pos -= min(coord.x * movement_multiplier, bird_x_pos);
    } 
    
    else if (coord.x < 0 && bird_x_pos < x_boundary_limit) { // Else if joystick is going right and bird is not at the right boundary. Bird position increments by the smaller value (absolue value of –2 or boundary minus the bird position) 
        bird_x_pos += min(abs(coord.x) * movement_multiplier, x_boundary_limit - bird_x_pos);
    }

    if (coord.y < 0 && bird_y_pos > 0) { //When joystick is going up and bird pos is not at the boundary. Bird position decrements by smaller value (absolute value of –2 or current bird position) 
        bird_y_pos -= min(abs(coord.y) * movement_multiplier, bird_y_pos);
    } 
    
    else if (coord.y > 0 && bird_y_pos < y_boundary_limit) { // Else if joystick is going down and bird is not at the bottom boundary. Bird position increments by smaller value of (+2 or boundary minus bird position) 
        bird_y_pos += min(coord.y * movement_multiplier, y_boundary_limit - bird_y_pos);
    }

    lcd.drawRect(bird_x_pos, bird_y_pos, 10, 10, FILL_BLACK);

}