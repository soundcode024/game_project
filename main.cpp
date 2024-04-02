/*        Embed game project
*        ========================
*
*        Function:               Flappy bird game
*        Required Libraries:     Joystick : https://github.com/ELECXJEL2645/Joystick
*                                N5110    : https://github.com/ELECXJEL2645/N5110
                                 * note these are not my libraries and are shown here for referencing reasons, they are used throughtout the program
*
*        Authored by:            Filip Zawalski
*        Version:                1.0
*        MBED Studio Version:    1.4.5
*        Board:	                 NUCLEO L476RG  */

#include "mbed.h"
#include "Joystick.h" 
#include "N5110.h"
#include "struts.h"
#include "game.h"
#include <cstdio>

#define FPS 15

Joystick joystick(PC_1, PC_0); // y     x   attach and create joystick object
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10); // Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)

Game flappy;

void init();
void render(Vector2D coord);
Vector2D read_joystick();
void game_over();

int main(){

    init(); // initialise the lcd and joystick
    // probably going to want a function for the start screen and menu

    while (true) {

        render(read_joystick());
        thread_sleep_for(1000/FPS); // delay to set frame rate of the game

        if (flappy.get_collision()) {
            break;
        }

    }

    game_over();

}

void init() {

    joystick.init();        // set centre of the joystick
    lcd.init(LPH7366_1);    // initialise the lcd
    lcd.setContrast(0.55);  // set contrast to 55%
    lcd.setBrightness(0.5); // set brightness

}

void render(Vector2D coord) {

    lcd.clear();
    flappy.game(lcd, coord);
    lcd.refresh();

}

Vector2D read_joystick() {

    Vector2D coord = joystick.get_mapped_coord();

    if (abs(coord.x) < 0.01) {
        coord.x = 0;
    }

    if (abs(coord.y) < 0.01) {
        coord.y = 0;
    }
    return coord;
}

void game_over(){
    lcd.clear();
    char buffer[14]={0};  // each character is 6 pixels wide, screen is 84 pixels (84/6 = 14)
    sprintf(buffer,"GAME OVER"); // print formatted data to buffer
    lcd.printString(buffer,0,0);     // display on screen
    lcd.refresh();
    sleep();
}
    /* // this is just here as reference
        char buffer[14]={0};  // each character is 6 pixels wide, screen is 84 pixels (84/6 = 14)
        sprintf(buffer,"x = %.3f",coord.x); // print formatted data to buffer
        lcd.printString(buffer,0,0);     // display on screen
        sprintf(buffer,"y = %.3f",coord.y); // print formatted data to buffer
        lcd.printString(buffer,0,1);     // display on screen
    */