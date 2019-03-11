/**
 * File  : demo.h
 * Author: Raja Soufi
 * 
 * Class definition of the Demo class.
 */

 // Include guard
#ifndef _DEMO_H_
#define _DEMO_H_

// Inclusions
#include <ctime>
#include <GL/glut.h>
#include <iostream>

#include "../geom/halfPlane.h"
#include "../geom/line.h"
#include "../geom/point.h"
#include "../geom/vector.h"

#include "../orca/agent.h"
#include "../orca/orca.h"

#include "../utilities/utilities.h"

#include "color.h"

// Open std namespace
using namespace std;

// Class definition
class Demo {
    
    private:
    
    // Constructor
    Demo(void);
    
    public:
    
    // Attributes
    static const int SCREEN_HEIGHT;
    static const int SCREEN_WIDTH;
    static const double ZOOM;
    
    static volatile bool paused;
    static volatile double speed;
    
    static bool following;
    static int followed;
    
    // Configurations
    static const vector<Agent> CIRCLE_CONFIGURATION;
    static const vector<Agent> TWO_LINE_CONFIGURATION;
    static const vector<Agent> SQUARE_CONFIGURATION;
    static const vector<Agent> RANDOM_CONFIGURATION;
    
    static const vector<Agent>& CONFIGURATION;
    
    // Methods
    
    // Drawing initialiser
    static void initDrawing(void);
    
    // Drawing functions
    static void draw(void);
    static void follow(const int INDEX);
    static void drawPoint(const Point& P, const Color& COLOR);
    static void drawVector(const Point& POSITION, const Vector& V, const Color& COLOR);
    static void drawCircle(const Point& POSITION, const double RADIUS, const Color& COLOR);
    static void drawHalfPlane(const HalfPlane& HALF_PLANE, const Color& COLOR);
    
    // Window resize handler
    static void reshape(int width, int height);
    
    // Keypress handler
    static void key(unsigned char k, int x, int y);
    
    // Idle function
    static void idle(void);
    
    // ORCA methods
    static void loop(void);
    
};

#endif // _DEMO_H_
