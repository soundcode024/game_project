#include "bird.h"
#include <cstdio>

#define movement_multiplier 2
#define x_boundary_limit 80
#define y_boundary_limit 38

// make the bird_pos variable in Bird class a private variable]
// add the dotted line when its at its position limit

Vector2D bird_pos(21,24); // initial position of the bird

Bird::Bird() {}; // default empty constructor

void Bird::bird(N5110 &lcd, Vector2D coord) {
    //printf("x=%f y=%f       ",bird_pos.x, bird_pos.y);
    //printf("x=%f y=%f Joystick \n",coord.x, coord.y);
    // 1 is down on the y (-1 is up)    1 is left on the x (-1 is right)

    if (coord.x > 0 && bird_pos.x > 0) { // When the joystick is going left and the bird position is not at the boundary, Bird position decrements by the smaller value ( +2 or current bird position) 
        bird_pos.x -= min(coord.x * movement_multiplier, bird_pos.x);
    } 
    
    else if (coord.x < 0 && bird_pos.x < x_boundary_limit) { // Else if joystick is going right and bird is not at the right boundary. Bird position increments by the smaller value (absolue value of –2 or boundary minus the bird position) 
        bird_pos.x += min(abs(coord.x) * movement_multiplier, x_boundary_limit - bird_pos.x);
    }

    /*if (bird_pos.x >= x_boundary_limit-2) {     // when the bird is at x_boundary_limit it will draw a dotted line at the boundary
        lcd.drawLine(x_boundary_limit, 0, x_boundary_limit, 48, FILL_WHITE); // note the width of the sprite will need to be addded to the boundary
    }
    */

    if (coord.y < 0 && bird_pos.y > 0) { //When joystick is going up and bird pos is not at the boundary. Bird position decrements by smaller value (absolute value of –2 or current bird position) 
        bird_pos.y -= min(abs(coord.y) * movement_multiplier, bird_pos.y);
    } 
    
    else if (coord.y > 0 && bird_pos.y < y_boundary_limit) { // Else if joystick is going down and bird is not at the bottom boundary. Bird position increments by smaller value of (+2 or boundary minus bird position) 
        bird_pos.y += min(coord.y * movement_multiplier, y_boundary_limit - bird_pos.y);
    }

    
    lcd.drawSprite(bird_pos.x, bird_pos.y, 11, 12, (int*)bird_sprite);
    lcd.drawRect(bird_pos.x, bird_pos.y, 12, 11, FILL_TRANSPARENT);  // rectangle to draw bird hitbox

}

Vector2D Bird::get_bird_pos() {
    return bird_pos;
}