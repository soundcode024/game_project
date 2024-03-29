#include "walls.h"

int wall_gap = 20;
int gap_pos = 35;

void draw_walls(N5110 &lcd) {

    lcd.drawSprite( 30,  (gap_pos-wall_gap-48), 48, 10, (int*)top_wall);
    lcd.drawSprite( 30, gap_pos, 48, 10, (int*)bottom_wall);

}