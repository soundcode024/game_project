#include "Utilities.h"

AnalogIn noise(A0); // unused analog pin

DigitalOut vibration_motor(PB_4);
Timeout vibration_timeout;
volatile bool vibration_en = 1;

int rand_num() {
    srand(noise.read_u16()); // this seeds the random num generator with noise on the pin
    int random_num = rand(); // rand function used from cstdlib.
    return random_num;
}

Vector2D::Vector2D(float X, float Y) {
    x = X;
    y = Y;
}

void vibration_init() {
    vibration_motor.write(0); // initialises vibration motor as off
}

// Function to run the vibration motor, options are ON, OFF, SHORT, MEDIUM, LONG. 
void vibration(vib_mode mode) {
    
    if (mode == ON or vibration_en) { // this will only run if vibration is enabled or is being enabled 

        switch (mode) {
            case ON:
                vibration_en = 1; // enables vibration
                break;
            case OFF:
                vibration_en = 0; // disables vibration
                break;
            case SHORT:
                vibration_motor.write(1); // turns on vibration motor
                vibration_timeout.attach(&vibration_isr, 20ms); // sets time after which ISR function will turn off motor
                break;
            case MEDIUM:
                vibration_motor.write(1);
                vibration_timeout.attach(&vibration_isr, 50ms);
                break;
            case LONG:
                vibration_motor.write(1);
                vibration_timeout.attach(&vibration_isr, 500ms);
                break;
        } 
    }
}

void vibration_isr() {
    vibration_motor.write(0); // turns off vibration motor after set time
}