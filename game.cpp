#include "game.h"
#include <cstdio>
#include <iostream>

#define wall_gap 20
#define wall_speed 1
#define wall_length 10
#define bird_length 12

// NEED TO ADD A POINTS COUNTER THAT WORKS ON THE COLLISION STUFF WHEN THE X COLLISION GOES FROM 1 TO 0 IT WILL GIVE A POINT

    // NOTES:
    // can optimise the collisions on y axis by writting code to find a number to divide the wall height by so the edge of the wall will always have collision detection
    // could further optimise by having the for loops run only if the y pos is right to save clock cycles
    // need to look into how to make the hitbox smaller maybe for loop with the sprite 

Game::Game() {}; //empty constructor

void Game::init() {
    _collision = 0;
    _score = 0;
    _run_once = 1;
    _bird.init();
    _wall1.init();
    _wall2.init();
}

void Game::game(N5110 &lcd, Vector2D coord) {

    if (_run_once) { // temporary for testing with multiple walls NOT YET WORKING
        _wall2.set_x_offset(40);
        _run_once = 0;
    }

    _wall1.draw_wall(lcd, random_gap_y_pos() , wall_gap, wall_speed); // variables temporarily defined above for testing
    _wall2.draw_wall(lcd, random_gap_y_pos() , wall_gap, 1);
    _bird.bird(lcd, coord);
    collision(_bird.get_bird_pos(), _wall1.get_wall_x_pos(), _wall1.get_wall_gap_pos());
    collision(_bird.get_bird_pos(), _wall2.get_wall_x_pos(), _wall2.get_wall_gap_pos());

}

// collision, function to detect collisions between the bird and moving wall.
void Game::collision (Vector2D bird_pos, float wall_x_pos, int gap_y_pos) { 

    _bird_y_pos = static_cast<int>(bird_pos.y); // casts the bird position float as a integer to remove the decimal points
    _bird_x_pos = static_cast<int>(bird_pos.x);
    
    //printf("\n_bird_x_pos=%i ¦ _bird_y_pos=%i",_bird_x_pos, _bird_y_pos);

    if (_bird_x_pos + bird_length > wall_x_pos and _bird_x_pos < wall_x_pos + wall_length) { // detects collisions of the x positions of the wall and bird

        for (_i = 0; _i < (48-(48-gap_y_pos+wall_gap)); _i++) { // collision detection of upper wall
            if (_i == _bird_y_pos or _i == _bird_y_pos+11) { // _i scans across the wall y coordinates, if its a match with the birds y position at the left or right edge, collision is set true.
                _collision = 1;
                break; 
            }  
        }

        for (_j = 48; _j > gap_y_pos; _j--) { // collision detection of lower wall
            if (_j == _bird_y_pos or _j == _bird_y_pos+11) {
                _collision = 1;
                break;
            }  
        }

        if ((_bird_x_pos + bird_length + 1 > wall_x_pos and _bird_x_pos + 1 < wall_x_pos + wall_length) == 0) {_score++;} // when the bird is in the wall's x coordinates, this checks if its position + 1 pixel is not in the wall's bounds, if its not it increments the score

    }
}

// random_gap_y_pos, function that returns a random value for a wall
int Game::random_gap_y_pos () { 
    return (wall_gap+(rand_num()%(48-wall_gap))); // this ensures the gap is never out of bounds making the level impassable
}

// get_collision, returns a boolean value, 1 = collision detected, 0 = no collision detected, resets collision bool
bool Game::get_collision(){ 
    return _collision;
    _collision = 0; // resets collision bool only when get_collision is called, so when multiple walls are present they dont pull collision low if they are checked later in line
}

// get_score, return the score value, number of times the bird passes the wall without collision
int Game::get_score() {return _score;}