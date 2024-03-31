#include "game.h"

void game(N5110 &lcd, Vector2D coord) {

    draw_walls(lcd, 30, 35, 20);
    bird(lcd, coord);

}

void collision () {
    //
}