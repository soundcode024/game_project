#include "walls.h"
#include <cstdio>

Wall::Wall() {}; //empty constructor

void Wall::init() {
    _wall_x_pos = 85; // screen width plus one pixel, as it will be decremented by the if statement straight away.
    _wall_lifetime = 0;
}

// LCD pointer, gap_y_pos, wall_gap, wall_speed
void Wall::draw_wall(N5110 &lcd, int gap_y_pos, int wall_gap, float wall_speed) {

    if (!_wall_lifetime) { // if statement to set the gap_y_pos and hold it for the lifetime of the wall on the screen
        _wall_lifetime = 1;
        _gap_y_pos = gap_y_pos;
    }

    if (_wall_x_pos >= -10) {  //detects when the wall leaves the screen and makes it loop around again
        _wall_x_pos = _wall_x_pos - wall_speed; // changes wall x position based on given wall speed
    }
    
    else {
        _wall_x_pos = 84; // sets wall position to out of the screen on the right side
        _wall_lifetime = 0;
    }

    lcd.drawSprite( _wall_x_pos, (_gap_y_pos-wall_gap-48), 48, 10, (int*)top_wall); // the wall sprites are the height of the entire screen so they can be drawn partly out of the screen depending on required gap size and gap position
    lcd.drawSprite( _wall_x_pos, _gap_y_pos, 48, 10, (int*)bottom_wall);

}

float Wall::get_wall_x_pos() {return _wall_x_pos;} // returns wall x position

int Wall::get_wall_gap_pos() {return _gap_y_pos;} // returns gap y position

bool Wall::get_wall_lifetime() {return _wall_lifetime;} // returns wall lifetime

// Make sure this only runs once at the start of each gamemode
void Wall::set_x_offset(int offset) {_wall_x_pos = _wall_x_pos + offset;} // sets inital wall offset to make the walls not render on top of eachother