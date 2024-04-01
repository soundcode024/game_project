#pragma once

#include "mbed.h"
#include "N5110.h"
#include "struts.h"
#include "bird.h"
#include "walls.h"
#include <iostream>

class Game {

public:
    Game();
    void game(N5110 &lcd, Vector2D coord);
    bool collision (Vector2D bird_pos, float wall_x_pos);
    bool get_collision();

private:
    Bird _bird;
    Wall _wall1;
    bool _collision = 0;
    int _bird_y_pos;
    int _bird_x_pos;
    int _i;
    int _j;
};