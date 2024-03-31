#pragma once

#include "mbed.h"
#include "N5110.h"
#include "struts.h"
#include "bird.h"
#include "walls.h"

class Game {

public:
    Game();
    void game(N5110 &lcd, Vector2D coord);
    void collision (Vector2D bird_pos);

private:
    Wall _wall1;

};