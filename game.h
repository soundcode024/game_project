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

private:
    Bird _bird;
    Wall _wall1;
    Wall _wall2;
    bool _collision;
    int _bird_y_pos;
    int _bird_x_pos;
};