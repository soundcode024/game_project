#pragma once

#include "mbed.h"
#include "N5110.h"
#include "struts.h"
#include "bird.h"
#include "walls.h"
#include <iostream>

class Game {

public:
    Game(); // constructor

    // Methods
    void init();
    void game(N5110 &lcd, Vector2D coord);
    void collision (float wall_x_pos, int gap_y_pos);
    bool get_collision();
    void score();
    int get_score();

private:
    // Methods
    int random_gap_y_pos();
    void score_ramping();

    // Object instantuations
    Bird _bird; 
    Wall _wall1;
    Wall _wall2;

    // Variables
    bool _collision;
    int _bird_y_pos;
    int _bird_x_pos;
    bool _run_once; // bool to run a section of code only once
    int _gap_y_pos;
    int _score;
    bool _set_score_enable_1; // bool for making the score settable
    bool _set_score_enable_2; // ^
    float _wall_speed;

};