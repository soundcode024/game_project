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
#include "bird.h"
#include "struts.h"

#define FPS 12

Joystick joystick(PC_1, PC_0); // y     x   attach and create joystick object
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10); // Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  

void init();
void render(Vector2D coord);

float x_pos;
float y_pos;

int main(){

    init(); // initialise the lcd and joystick
    // probably going to want a function for the start screen and menu

    while (true) {
    
        Vector2D coord = joystick.get_mapped_coord();
        render(coord);
        thread_sleep_for(1000/FPS);

    }
}

void init() {

    joystick.init();        // set centre of the joystick
    lcd.init(LPH7366_1);    // initialise the lcd
    lcd.setContrast(0.55);  // set contrast to 55%
    lcd.setBrightness(0.5); // set brightness

}

void render(Vector2D coord) {

    lcd.clear();  
    bird(lcd, coord);
    lcd.refresh();

}

    /*while (1) {
          // read the joystick to get the x- and y- values
        Vector2D coord = joystick.get_mapped_coord(); 
        printf("Coord = %f | %f\n",coord.x,coord.y);    
        
        lcd.clear();  // clear buffer at the start of the loop
        char buffer[14]={0};  // each character is 6 pixels wide, screen is 84 pixels (84/6 = 14)
        sprintf(buffer,"x = %.3f",coord.x); // print formatted data to buffer
        lcd.printString(buffer,0,0);     // display on screen
        sprintf(buffer,"y = %.3f",coord.y); // print formatted data to buffer
        lcd.printString(buffer,0,1);     // display on screen
        lcd.drawCircle(42, 23, 20, FILL_TRANSPARENT);

        x_pos = (coord.x*20)+42;
        y_pos = -(coord.y*20)+23;
        lcd.drawCircle(x_pos, y_pos, 2, FILL_BLACK);




        lcd.refresh();  // need to fresh the screen to get the message to appear
        
        ThisThread::sleep_for(30ms);
    } */