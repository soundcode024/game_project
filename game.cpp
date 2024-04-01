#include "game.h"
#include <cstdio>
#include <iostream>

#define gap_y_pos 35 // this will be the number of pixels from the top of the screen to the top of the lower wall
#define wall_gap 20
#define wall_speed 0
#define wall_length 10
#define bird_length 12

//can optimise the collisions on y axis by writting code to find a number to divide the wall height by so the edge of the wall will always have collision detection
// could further optimise by having the for loops run only if the y pos is right to save clock cycles
// need to look into how to make the hitbox smaller maybe for loop with the sprite 

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
    
    printf("\n_bird_x_pos=%i ¦ _bird_y_pos=%i",_bird_x_pos, _bird_y_pos); // casts the y position as a integer to remove the decimal part

    if (_bird_x_pos + bird_length > wall_x_pos and _bird_x_pos < wall_x_pos + wall_length) { // detects collisions of the x positions of the wall and bird
        //printf("   x collision detected");

        for (_i = 0; _i < (48-(48-gap_y_pos+wall_gap)); _i++) { // collision detection of upper wall
            if (_i == _bird_y_pos or _i == _bird_y_pos+11) {
                printf("u");
                break;
            }  
        }

        for (_j = 48; _j > gap_y_pos; _j--) { // collision detection of lower wall
            if (_j == _bird_y_pos or _j == _bird_y_pos+11) {
                printf("l");
                break;
            }  
        }

    }

    return _collision;
}


