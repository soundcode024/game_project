/*        Embed game project
*        ========================
*
*        Function:               Flappy bird game
*        Required Libraries:     Joystick           : https://github.com/ELECXJEL2645/Joystick
*                                N5110              : https://github.com/ELECXJEL2645/N5110
                                 DebouncedInterrupt : https://os.mbed.com/teams/WizziLab/code/DebouncedInterrupt/     
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
#include "Utilities.h"
#include "game.h"
#include <cstdio>
#include "menu_sprites.h" // sprites for the menus
#include "DebouncedInterrupt.h" // EXTERNAL LIBRARY USED FOR THE INTERRUPT AS IT INCLUDES SOFTWARE DEBOUNCING, I modified this to make use of internal pull-up/down resistors.

// DEFINE STATEMENTS
#define FPS 15 // This sets the games FPS (KEEP BETWEEN 12-20 FPS)
#define frame_delay 5 // Defined frame delay for menu inputs

// OBJECT INITIALISATION
Joystick joystick(PC_1, PC_0); // y     x   attach and create joystick object
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10); // Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)
DigitalIn js_button(PB_0); // Joystick button declared as DigitalIn to make use of internal pull down resistor
Game flappy; // Creates an object of the game class
DebouncedInterrupt pause_button(PC_9); // external library based interupt that features debouncing for the pause button
AnalogIn ldr(A2); // light dependant resistor input for adaptive brightness
Ticker read_ldr; // ticker for reading the light dependant resistor

// FUNCTION PROTOTYPES
void init(); // Init function
Vector2D read_joystick(); // Reads joystick and applied deadzone

void main_menu(); // Main menu function
void options_menu(); // Options menu function
void tutorial_menu(); // Tutorial text display function
int menu_offset_animation(int &logo_offset, int &animation_count); // Functions for running the menu
void menu_frame_delay(int &menu_choice, int &frame_count); // ^
void menu_draw_boxes(int const &menu_choice); // ^
void game_over(); // Game over fuction

void render(Vector2D coord); // Renders game

void pause_isr(); // Adds pause feature
void pause(); // ^

void adaptive_brightness_isr(); // adds adaptive LCD backlight brightness feature
void adaptive_brightness(); // ^

// VARIABLES
char buffer[14]={0}; // For printing text on lcd using the N5110 library
volatile int score_text_offset; // used to offset the the score text to keep it centered
volatile bool pause_button_flag = 0; // ISR variable for pause function
volatile bool pause_game = 0; // pause function variable, used to pause the game
volatile bool ldr_read_flag = 0; // ISR flag for adaptive brightness
volatile bool adaptive_brightness_en = 0; // adaptive brightness enable variable

int main(){

    init();
    main_menu(); // main menu function

    while (true) { // main while loop for the runtime of the game

        pause(); // Pauses the game when the pause button is pressed
        adaptive_brightness(); // Changes LCD brightness based on ambient light level, if this feature is enabled

        render(read_joystick()); // render function renders the game, takes joystick input and is the actual running of the game and its features.
        thread_sleep_for(1000/FPS); // delay to set frame rate of the game

        if (flappy.get_collision()) { // On collision with a wall, the game ends
                game_over();
        }
    }
}

void init() {
    static bool run_once = 1;

    if (run_once) { // prevents joystick centre being set again, prevents display flash after game over event
        joystick.init();        // set centre of the joystick
        lcd.init(LPH7366_1);    // initialise the lcd
        lcd.setContrast(0.55);  // set contrast to 55%
        js_button.mode(PullUp); // Sets internal pull down resistor, this is adequate for the frequency of button presses
        run_once = 0; // ensures this only runs a single time at startup
    }
    if (!adaptive_brightness_en) {lcd.setBrightness(0.5);} // set initial lcd brightness if adaptive brightness is not on
    flappy.init(); // Game init
    pause_button.attach(&pause_isr, IRQ_FALL, 200, true); // Checks for falling edge on pause button to update run ISR
    read_ldr.attach(&adaptive_brightness_isr, 2s); // Sets ldr_read_flag high every 2 seconds for the adaptive brightness feature
}

void render(Vector2D coord) { // Funtion to render the game on the screen, passes joystick and LCD object to the game object

    lcd.clear(); // Clears LCD buffer

    flappy.game(lcd, coord); // Renders game objects (walls, bird...)
    
    if (flappy.get_score() >= 10) {score_text_offset = 37;} // keeps the score display in the center, when score hits 10, this moves it to the left to keep in in the centre of the screen.
    else if (flappy.get_score() >= 100) {score_text_offset = 34;}
    else {score_text_offset = 40;}

    sprintf(buffer,"%i",flappy.get_score()); // print score to buffer
    lcd.printString(buffer,score_text_offset,1); // print score to display

    if (pause_button_flag) { // When the pause flag is set high by ISR, pause text is printed to LCD
        lcd.drawSprite(26, 16, 10, 32, (int*) pause_text); // Draws pause on the screen when the game is paused
        pause_game = 1; // pause_game variable set high to put MCU to sleep at the start of the next frame
    }

    lcd.refresh(); // Sends buffer to LCD

}

void main_menu() { // Function to render the main menu items and handle menu choice through user input

    static int menu_choice = 0; // static will ensure when going back to main_menu from a submenu, the last selected option will remain selected
    int frame_count = 0; // used for frame based delay
    static int logo_offset = -16; // This means the logo offset is drawn out of bounds at the top by -15-1 as that is the height of it, so it can scroll in, static ensures this only happens at the start of the game
    static int animation_count = 0; // used for animating the logo text
    bool button_en = 0; // used for frame based delay

    while (true) {
        thread_sleep_for(1000/FPS); // delay to set frame rate of the game
        adaptive_brightness(); // Changes LCD brightness based on ambient light level, if this feature is enabled
        menu_frame_delay(menu_choice, frame_count);

        lcd.clear();

        lcd.drawSprite(6, menu_offset_animation(logo_offset, animation_count), 15, 72, (int*)flappy_logo); // Game logo
        
        //first menu item
        lcd.drawSprite(16, 19, 7, 26, (int*)play_text);

        //second menu item
        lcd.drawSprite(16, 29, 7, 49, (int*)tutorial_text);

        //third menu item
        lcd.drawSprite(16, 39, 7, 43, (int*)options_text_small);

        menu_draw_boxes(menu_choice);

        lcd.refresh();

        if (frame_count == frame_delay) { // this adds a frame delay before the next input can be registered to give time to lift off the button 
            button_en = 1;
        }

        if (menu_choice == 0 and js_button.read() == 0 and button_en) { // If statements to go into the menu item when the Joystick button is pressed
            vibration(MEDIUM);
            break; // breaks out of main_menu while loop, allowing program to continue in main and for the game to start
        }

        else if (menu_choice == 1 and js_button.read() == 0 and button_en) {
            vibration(MEDIUM);
            tutorial_menu(); // displays tutorial
            frame_count = 0; // resets frame delay
            button_en = 0; // ^
        }

        else if (menu_choice == 2 and js_button.read() == 0 and button_en) {
            vibration(MEDIUM);
            options_menu(); // goes into options menu
            frame_count = 0; // resets frame delay
            button_en = 0; // ^
        }

        pause_button_flag = 0; // do not want the game be be pausable from the main menu

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
    // each character is 6 pixels wide, screen is 84 pixels (84/6 = 14), 7 pixels high

    lcd.drawSprite(2, 2, 10, 29, (int*)game_text);
    lcd.drawSprite(54, 2, 10, 27, (int*)over_text);
    lcd.drawSprite(15, 13, 35, 56, (int*)dead_bird);

    sprintf(buffer,"%i",flappy.get_score()); // print score to buffer
    lcd.printString(buffer,score_text_offset,0); // print score to display

    lcd.refresh();
    thread_sleep_for(5000);
    main();
}

void options_menu() {

    int menu_choice = 0;
    int frame_count = 0;
    int logo_offset = 1; // a logo offset of 1 means the logo will not scroll in from out of bounds
    int animation_count = 0;
    bool button_en = 0;
    bool vibration_en = 1; // variable to toggle vibration feature

    while (true) {
        thread_sleep_for(1000/FPS); // delay to set frame rate of the game
        adaptive_brightness(); // Changes LCD brightness based on ambient light level, if this feature is enabled
        menu_frame_delay(menu_choice, frame_count);

        lcd.clear();

        lcd.drawSprite(14, menu_offset_animation(logo_offset, animation_count), 15, 56, (int*)options_text_big); // Options menu text
        
        // first menu item
        lcd.drawSprite(16, 19, 7, 53, (int*)vibration_text); 
        if (!vibration_en) {lcd.drawLine(14, 22, 70, 22, 1);} // draws a line across the text if the feature is disabled

        //second menu item
        lcd.drawSprite(16, 29, 7, 49, (int*)adaptive_brightness_text);
        if (!adaptive_brightness_en) {lcd.drawLine(14, 32, 66, 32, 1);} // draws a line across the text if the feature is disabled

        //third menu item
        lcd.drawSprite(16, 39, 7, 27, (int*)back_text); // BACK

        menu_draw_boxes(menu_choice);


        lcd.refresh();

        if (frame_count == frame_delay) {
            button_en = 1;
        }

        if (menu_choice == 0 and js_button.read() == 0 and button_en) { // If statements to go into the menu item when the Joystick button is pressed
            vibration(MEDIUM);
            printf("Options menu 1 \n");

            if (vibration_en) { // if the vibration is currently on and the button is pressed on this menu, it will run vibration(OFF) disabling vibrations
                vibration(OFF);
            }
            else {
                vibration(ON);
            }
            vibration_en = !vibration_en; // the vibration_en variable is inverted everytime this runs / menu option is clicked

            frame_count = 0; // this adds a frame delay before the next input can be registered to give time to lift off the button 
            button_en = 0; // ^
        }

        else if (menu_choice == 1 and js_button.read() == 0 and button_en) {
            vibration(MEDIUM);
            printf("Options menu 2 \n");

            adaptive_brightness_en = !adaptive_brightness_en; // adaptive_brightness_en is inverted everytime this runs / menu option is clicked

            if (!adaptive_brightness_en) {
                lcd.setBrightness(0.50); // if adaptive brightness is disabled, brightness returns to default value.
                read_ldr.detach(); // detaches the Ticker to preserve system resources
                } 
            else {
                read_ldr.attach(&adaptive_brightness_isr, 2s); // Ticker is reattached
                ldr_read_flag = 1; // Flag set to 1 so brightness is updated ASAP
            }

            frame_count = 0; // this adds a frame delay before the next input can be registered to give time to lift off the button 
            button_en = 0; // ^

        }

        else if (menu_choice == 2 and js_button.read() == 0 and button_en) { // goes back to main menu
            vibration(MEDIUM);
            break; // breaks out of option menu while loop, going back to main menu
        }

        pause_button_flag = 0; // do not want the game be be pausable from the main menu

    }
}

void tutorial_menu() {

    lcd.clear();

    sprintf(buffer,"EVADE  WALLS!");
    lcd.printString(buffer,3,0);
    sprintf(buffer,"They speed up"); 
    lcd.printString(buffer,0,1); 
    sprintf(buffer,"above 5 point");
    lcd.printString(buffer,0,2);
    sprintf(buffer,"s. Try to get");
    lcd.printString(buffer,0,3);
    sprintf(buffer,"a high score.");
    lcd.printString(buffer,0,4);
    sprintf(buffer,"THEN BEAT IT!");
    lcd.printString(buffer,3,5);


    lcd.refresh();

    thread_sleep_for(200); // delay to stop the menu exiting instantly as the joystick button may still be held
    while (js_button.read()) {sleep();} // waits for joystick button to be pressed before continuing


    thread_sleep_for(200); // delay to stop the menu exiting instantly as the joystick button may still be held

    lcd.clear();

    sprintf(buffer,"Move in all d");
    lcd.printString(buffer,0,0);
    sprintf(buffer,"irections and"); 
    lcd.printString(buffer,0,1); 
    sprintf(buffer,"find a strate");
    lcd.printString(buffer,0,2);
    sprintf(buffer,"gy. To pause ");
    lcd.printString(buffer,0,3);
    sprintf(buffer,"press PAUSE. ");
    lcd.printString(buffer,0,4);
    sprintf(buffer,"GOOD LUCK xD");
    lcd.printString(buffer,6,5);


    lcd.refresh();

    thread_sleep_for(200); // delay to stop the menu exiting instantly as the joystick button may still be held
    while (js_button.read()) {sleep();} // waits for joystick button to be pressed before continuing
}

void pause_isr() { // Interupt service routine for the pause button, toggles flag when called
    pause_button_flag = !pause_button_flag;
}

void pause() {
    while (pause_game and pause_button_flag) { // While loop will only run when ISR flag is high and the pause text has been printed on the screen
        sleep(); // Puts MCU to sleep to save power
    }
    if (pause_game == 1) {
        thread_sleep_for(100); // Slight delay before going back into the game to prevent instant re-pausing
    }
    pause_game = 0; // Resets pause_game variable
}

int menu_offset_animation(int &logo_offset, int &animation_count) {

    if (logo_offset >= 1) { // When logo_offset reaches this value it increments by 1 after 10 frames pass, then decrements after another 10 frames
        animation_count++; // Increments frame count for animation
        if (animation_count == 10) { // Increment after 10 frames
            logo_offset = 2;
        }
        else if (animation_count == 20) { // Decrement after 10 frames
            logo_offset = 1;
            animation_count = 0; // Reset frame count for animation
        }
    }
    else { 
        logo_offset++; // Increments logo_offset if it is not yet in desired place before animating it
    }
    return logo_offset;
}

void menu_frame_delay(int &menu_choice, int &frame_count) {
    if (frame_count < frame_delay) { // This if statement creats a 5 frame delay without using a sleep command
        frame_count++;
    }
    
    if (joystick.get_direction() == N and frame_count == frame_delay) { // frame_count ensures this can only run every 5 frames, so menu items dont loop too quickly
        menu_choice = (menu_choice + 1) % 3; // modulo operator allows the menu items to loop around
        frame_count = 0; // resets frame count so menu cannot update for another 5 frames
        vibration(SHORT);
    }
    else if (joystick.get_direction() == S and frame_count == frame_delay) {
        menu_choice = (menu_choice - 1 + 3) % 3;
        frame_count = 0;
        vibration(SHORT);
    }
}

void menu_draw_boxes(int const &menu_choice) { // Function to draw the menu option boxes

    lcd.drawSprite(5, 19, 7, 7, (int*)box); // Draws menu selection boxes
    lcd.drawSprite(5, 29, 7, 7, (int*)box);
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
}

void adaptive_brightness_isr() { // ISR only updates the flag that triggers the adaptive brightness functionality in another function
    ldr_read_flag = 1; 
}

void adaptive_brightness() {
    if (ldr_read_flag and adaptive_brightness_en) { // If the flag is high and the feature is enabled.
        lcd.setBrightness(1-ldr.read()); // set brightness based on light dependant resistor
        ldr_read_flag = 0; // sets flag low so brightness is only updated next when the ticker sets the flag high
    }
}