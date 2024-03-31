#include "walls.h"


// LCD pointer, x_pos, y_pos, wall_gap
void draw_walls(N5110 &lcd, int x_pos, int gap_y_pos, int wall_gap) {

    lcd.drawSprite( x_pos, (gap_y_pos-wall_gap-48), 48, 10, (int*)top_wall);
    lcd.drawSprite( x_pos, gap_y_pos, 48, 10, (int*)bottom_wall);

}