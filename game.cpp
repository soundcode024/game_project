#include "game.h"
#include <cstdio>
#include <iostream>

#define gap_y_pos 35 // this will be the number of pixels from the top of the screen to the top of the lower wall
#define wall_gap 20
#define wall_speed 0

Game::Game() {}; //empty constructor

void Game::game(N5110 &lcd, Vector2D coord) {

    _wall1.draw_wall(lcd, gap_y_pos, wall_gap, wall_speed);
    //_wall2.draw_wall(lcd, gap_y_pos, wall_gap, 1);
    _bird.bird(lcd, coord);
    collision(_bird.get_bird_pos(), _wall1.get_wall_x_pos());
    //collision(_bird.get_bird_pos(), _wall2.get_wall_x_pos());

}

bool Game::collision (Vector2D bird_pos, float wall_x_pos) {

    _bird_y_pos = static_cast<int>(bird_pos.y);
    _bird_x_pos = static_cast<int>(bird_pos.x);
    
    printf("\nbird x pos=%f, rounded=%i ¦ bird y pos=%f, rounded=%i",bird_pos.x, _bird_x_pos, bird_pos.y, _bird_y_pos); // casts the y position as a integer to remove the decimal part

    if (_bird_x_pos + 12 > wall_x_pos and _bird_x_pos < wall_x_pos + 10) { // detects collisions of the x positions of the wall and bird
        printf("   x collision detected");

        for (int i = 0; i <= (48-gap_y_pos-wall_gap); i++) {
            if (i == _bird_y_pos or i == _bird_y_pos-11) {
                printf("   y collision detected");
                break;
            }
        }
    }

    return _collision;
}


