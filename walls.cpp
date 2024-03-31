#include "walls.h"

float wall_x_pos = 84;

// LCD pointer, x_pos, gap_y_pos, wall_gap, wall_speed
void draw_walls(N5110 &lcd, int gap_y_pos, int wall_gap, float wall_speed) {

    if (wall_x_pos >= 0-10) {
        wall_x_pos = wall_x_pos - wall_speed;
    }
    
    else {
        wall_x_pos = 84;
    }

    lcd.drawSprite( wall_x_pos, (gap_y_pos-wall_gap-48), 48, 10, (int*)top_wall);
    lcd.drawSprite( wall_x_pos, gap_y_pos, 48, 10, (int*)bottom_wall);

}