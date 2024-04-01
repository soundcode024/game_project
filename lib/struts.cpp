#include "struts.h"

AnalogIn noise(A0); 

int rand_num() {
    srand(noise.read_u16());
    int random_num = rand();
    return random_num;
}

Vector2D::Vector2D(float X, float Y) {
    x = X;
    y = Y;
}