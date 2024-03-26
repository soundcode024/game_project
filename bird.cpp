#include "bird.h"
#include <cstdio>

float bird_x_pos = 21;
float bird_y_pos = 24;


void bird(N5110 &lcd, Vector2D coord) {
    //printf("x=%f y=%f \n",bird_x_pos, bird_y_pos);

    if (abs(coord.x) >= 0.01) {
        bird_x_pos -= coord.x*2;
    }

    if (abs(coord.y) >= 0.01) {
        bird_y_pos += coord.y*2;
    }

    lcd.drawRect(bird_x_pos, bird_y_pos, 16, 16, FILL_BLACK);

}