#include "game.h"
#include <cstdio>

#define gap_y_pos 35 // this will be the number of pixels from the top of the screen to the top of the lower wall
#define wall_gap 20
#define wall_speed 0

Game::Game() {}; //empty constructor

void Game::game(N5110 &lcd, Vector2D coord) {

    _wall1.draw_wall(lcd, gap_y_pos, wall_gap, wall_speed);
    collision(bird(lcd, coord), _wall1.get_wall_x_pos());

}

bool Game::collision (Vector2D bird_pos, float wall_x_pos) {
    
    //printf("wall x pos %f birdpos.x %f \n", wall_x_pos, bird_pos.x);

    if ((bird_pos.x > wall_x_pos and bird_pos.x < wall_x_pos+10) or (bird_pos.x+12 > wall_x_pos and bird_pos.x+12 < wall_x_pos+10)) {
        printf("\n collision \n");
    }

    return _collision;
}