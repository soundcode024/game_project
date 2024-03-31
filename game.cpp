#include "game.h"

Game::Game() {};

void Game::game(N5110 &lcd, Vector2D coord) {

    _wall1.draw_wall(lcd, 35, 20, 1);
    bird(lcd, coord);

}

void Game::collision (Vector2D bird_pos) {
    //
}