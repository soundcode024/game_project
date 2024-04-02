#include "struts.h"

AnalogIn noise(A0); // unused analog pin

int rand_num() {
    srand(noise.read_u16()); // this seeds the random num generator with noise on the pin
    int random_num = rand(); // rand function used from cstdlib.
    return random_num;
}

Vector2D::Vector2D(float X, float Y) {
    x = X;
    y = Y;
}