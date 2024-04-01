#include "walls.h"

// LCD pointer, x_pos, gap_y_pos, wall_gap, wall_speed

Wall::Wall() {}; //empty constructor

// LCD pointer, gap_y_pos, wall_gap, wall_speed
void Wall::draw_wall(N5110 &lcd, int gap_y_pos, int wall_gap, float wall_speed) {

    if (_wall_x_pos >= 0-10) {  //detects when the wall leaves the screen and makes it loop around again
        _wall_x_pos = _wall_x_pos - wall_speed;
    }
    
    else {
        _wall_x_pos = 84;
    }

    lcd.drawSprite( _wall_x_pos, (gap_y_pos-wall_gap-48), 48, 10, (int*)top_wall);
    lcd.drawSprite( _wall_x_pos, gap_y_pos, 48, 10, (int*)bottom_wall);

}

float Wall::get_wall_x_pos() {
    return _wall_x_pos;
}