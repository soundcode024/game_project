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

//                  y     x
Joystick joystick(PC_1, PC_0);  //attach and create joystick object

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

float x_pos;
float y_pos;

int main(){
    joystick.init();
    lcd.init(LPH7366_1);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd.setContrast(0.55);      //set contrast to 55%
    lcd.setBrightness(0.5);     //set brightness to 50% (utilises the PWM)
    
    while (1) {
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
    }
}
