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
    bool collision (Vector2D bird_pos, float wall_x_pos, int gap_y_pos);
    bool get_collision();
    int random_gap_y_pos();

private:
    Bird _bird; // Object instantuations
    Wall _wall1;
    Wall _wall2;

    bool _collision = 0;
    int _bird_y_pos;
    int _bird_x_pos;
    int _i; // variable for "for" loop
    int _j; // variable for "for" loop
    bool _run_once = 1; // bool to run a section of code only once

    int _gap_y_pos;

    
};