#include "game.h"

void game(N5110 &lcd, Vector2D coord) {

    draw_walls(lcd, 35, 20, 1);
    bird(lcd, coord);

}

void collision () {
    //
}