/* Joystick Library
*  Author: Craig Evans  27 jan 2020
*/

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "mbed.h"
#include "struts.h"

// this value can be tuned to alter tolerance of joystick movement
#define TOL 0.1f
#define RAD2DEG 57.2957795131f



class Joystick{
public:
    
    //              y-pot              x-pot            
    Joystick(PinName vertPin,PinName horizPin);
    
    void init();  // needs to be called at start with joystick centred
    float get_mag();              // polar
    float get_angle();            // polar
    Vector2D get_coord();         // cartesian co-ordinates x,y
    Vector2D get_mapped_coord();  // x,y mapped to circle
    Direction get_direction();    // N,NE,E,SE etc.
    Polar get_polar();            // mag and angle in struct form
    
private:
    AnalogIn *vert;
    AnalogIn *horiz;
       
    // centred x,y values    
    float _x0;
    float _y0;
};

#endif