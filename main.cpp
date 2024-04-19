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

// INCLUSIONS
#include "mbed.h"
#include "Joystick.h" 
#include "N5110.h"
#include "struts.h"
#include "game.h"
#include <cstdio>
#include "menu_sprites.h" // sprites for the main menu

// DEFINE STATEMENTS
#define FPS 15

// OBJECT INITIALISATION
Joystick joystick(PC_1, PC_0); // y     x   attach and create joystick object
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10); // Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)
DigitalIn js_button(PB_0); // Joystick button declared as DigitalIn to make use of internal pull down resistor
Game flappy;
InterruptIn pause_button(BUTTON1);

// FUNCTION PROTOTYPES
void init();
void main_menu();
void render(Vector2D coord);
Vector2D read_joystick();
void game_over();
void pause_isr();
void pause();

// VARIABLES
char buffer[14]={0};
int score_text_offset;
volatile bool pause_button_flag = 0;
volatile bool pause_game = 0;

int main(){

    init(); // initialise the lcd and joystick
    main_menu(); // main menu function

    while (true) { // main while loop for the runtime of the game

        pause(); // Pauses the game when the pause button is pressed

        render(read_joystick()); // render function renders the game, takes joystick input and is the actual running of the game and its features.
        thread_sleep_for(1000/FPS); // delay to set frame rate of the game

        if (flappy.get_collision()) {
                game_over();
        }
    }
}

void init() {

    joystick.init();        // set centre of the joystick
    lcd.init(LPH7366_1);    // initialise the lcd
    lcd.setContrast(0.55);  // set contrast to 55%
    lcd.setBrightness(0.5); // set brightness
    js_button.mode(PullDown); // Sets internal pull down resistor, this is adequate for the frequency of button presses
    flappy.init(); // Game init
    score_text_offset = 40;

    pause_button.fall(&pause_isr); // Checks for falling edge on pause button to update pause flag 
    pause_button.mode(PullUp); // Internal pull up for the pause button
}

void render(Vector2D coord) { // Funtion to render the game on the screen, passes joystick and LCD object to the game object

    lcd.clear(); // Clears LCD buffer

    flappy.game(lcd, coord); // Renders game objects (walls, bird...)
    
    if (flappy.get_score() == 10) {score_text_offset = 37;} // when score hits 10, this moves it to the left to keep in in the centre of the screen.
    sprintf(buffer,"%i",flappy.get_score()); // print score to buffer
    lcd.printString(buffer,score_text_offset,1); // print score to display

    if (pause_button_flag) { // When the pause flag is set high by ISR, pause text is printed to LCD
        lcd.drawSprite(26, 16, 10, 32, (int*) pause_text);
        pause_game = 1; // pause_game variable set high to put MCU to sleep at the start of the next frame
    }

    lcd.refresh(); // Sends buffer to LCD

}

void main_menu() { // Function to render the main menu items and handle menu choice through user input

    int menu_choice = 0;
    int frame_count = 5;
    int animation_count = 0;
    int logo_offset = -15;

    while (true) {
        thread_sleep_for(1000/FPS); // delay to set frame rate of the game
        
        if (frame_count < 5) { // This if statement creats a 5 frame delay without using a sleep command
            frame_count++;
        }
        
        if (joystick.get_direction() == N and frame_count == 5) { // frame_count ensures this can only run every 5 frames, so menu items dont loop too quickly
            menu_choice = (menu_choice + 1) % 3; // modulo operator allows the menu items to loop around
            frame_count = 0; // resets frame count so menu cannot update for another 5 frames
        }
        else if (joystick.get_direction() == S and frame_count == 5) {
            menu_choice = (menu_choice - 1 + 3) % 3;
            frame_count = 0;
        }

        
        if (logo_offset >= 1) {
            animation_count++;
            if (animation_count == 10) {
                logo_offset++;
            }
            else if (animation_count == 20) {
                logo_offset--;
                animation_count = 0;
            }
        }
        else {
            logo_offset++;
        }

        lcd.clear();

        lcd.drawSprite(6, logo_offset, 15, 72, (int*)flappy_logo); // Game logo
        
        lcd.drawSprite(16, 19, 7, 29, (int*)play_text); // first menu item and box
        lcd.drawSprite(5, 19, 7, 7, (int*)box);

        //second menu item and box
        lcd.drawSprite(16, 29, 7, 46, (int*)tutorial_text);
        lcd.drawSprite(5, 29, 7, 7, (int*)box);

        //third menu item and box
        lcd.drawSprite(5, 39, 7, 7, (int*)box);

        switch (menu_choice) { // draws a box with a cross in it depending on which menu item is selected
            case 0:
                lcd.drawSprite(5, 19, 7, 7, (int*)box_selected);
                break;
            case 1:
                lcd.drawSprite(5, 29, 7, 7, (int*)box_selected);
                break;
            case 2:
                lcd.drawSprite(5, 39, 7, 7, (int*)box_selected);
                break;
        }

        lcd.refresh();

        if (menu_choice == 0 and js_button.read() == 1) { // If statements to go into the menu item when the Joystick button is pressed
            printf("Menu choice 0 = PLAY \n");
            break;
        }

        else if (menu_choice == 1 and js_button.read() == 1) {
            printf("Menu choice 1 = TUTORIAL \n");
        }

        else if (menu_choice == 2 and js_button.read() == 1) {
            printf("Menu choice 2 \n");
        }
    }
}

Vector2D read_joystick() { // Function to read the joystick mapped coordinates and apply a deadzone to it

    Vector2D coord = joystick.get_mapped_coord();

    if (abs(coord.x) < 0.01) { // applies a deadzone to the joystick
        coord.x = 0;
    }

    if (abs(coord.y) < 0.01) {
        coord.y = 0;
    }
    return coord;
}

void game_over() { // Function to handle the game over scenario
    lcd.clear();
    char buffer[14]={0};  // each character is 6 pixels wide, screen is 84 pixels (84/6 = 14)
    sprintf(buffer,"GAME OVER"); // print formatted data to buffer
    lcd.printString(buffer,15,0);     // display on screen
    sprintf(buffer,"Score = %i", flappy.get_score()); // print formatted data to buffer
    lcd.printString(buffer,15,1);     // display on screen
    lcd.refresh();
    thread_sleep_for(5000);
    main();

    // MAKE IT SAY SOMETHING LIKE TRY HARDER OR A DIFFERENT MESSAGE EVERY TIME?
}

void pause_isr() { // Interupt service routine for the pause button, toggles flag when called
    pause_button_flag = !pause_button_flag;
}

void pause() {
    while (pause_game and pause_button_flag) { // While loop will only run when ISR flag is high and the pause text has been printed on the screen
        sleep(); // Puts MCU to sleep to save power
    }
    pause_game = 0; // Resets pause_game variable
}