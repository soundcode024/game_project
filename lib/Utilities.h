#pragma once

#include "mbed.h"

// data types (enum Direction, struct Vector2D, struct Polar) are moved here from the Joystick library so are technically not my code.
// this is done so they can be used throughtout the program

enum Direction {
    CENTRE,  // 0
    N,       // 1
    NE,      // 2
    E,       // 3
    SE,      // 4
    S,       // 5
    SW,      // 6
    W,       // 7
    NW      // 8
};

struct Vector2D {
    float x;
    float y;

    Vector2D(float X, float Y); // constructor
};

struct Polar {
    float mag;
    float angle;
};

enum vib_mode {
    ON,
    OFF,
    SHORT,
    MEDIUM,
    LONG
};

int rand_num();

void vibration_init();
void vibration(vib_mode mode);
void vibration_isr();