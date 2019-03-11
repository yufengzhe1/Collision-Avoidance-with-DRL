/**
 * File  : main.cpp
 * Author: Raja Soufi
 * 
 * Implementation of the main function
 * of the program.
 */

// Inclusions
#include <GL/glut.h>
#include <iostream>
#include <thread>

#include "demo.h"

// Open std namespace
using namespace std;

/*
    Main function
*/

/**
 * The main function of the program.
 * 
 * @param argc - The number of parameters passed to
 *               the program
 * @param argv - A pointer to the parameters passed
 *               to the program
 */
int main(int argc, char** argv) {
    
    // Initialise Glut and create a window
    glutInit(&argc, argv);
    
    // Display mode setup
    // Here we've selected an RGBA display with depth
    // testing and double buffering enabled
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    
    // Request a window size of SCREEN_WIDTH x SCREEN_HEIGHT
    glutInitWindowSize(Demo::SCREEN_WIDTH, Demo::SCREEN_HEIGHT);
    // Position the window's initial top-left corner
    glutInitWindowPosition(320, 40);

    // Create a window and pass through the window title
    glutCreateWindow("ORCA demo");
    glutReshapeWindow(Demo::SCREEN_WIDTH, Demo::SCREEN_HEIGHT);
    
    // Set up callback functions
    glutDisplayFunc(Demo::draw);
    glutReshapeFunc(Demo::reshape);
    glutKeyboardFunc(Demo::key);
    glutIdleFunc(Demo::idle);
    
    // Run our own drawing initialiser
    Demo::initDrawing();
    
    cout << "Initializing the ORCA system..." << endl;
    
    // Initialise ORCA
    ORCA::initialize(Demo::CONFIGURATION,
        /*TAU = */0.01, /*DELTA_T = */0.01, /*ARRIVAL_THRESHOLD = */0.1);
    
    cout << "Creating a separate thread to run the ORCA loop..." << endl;
    
    // Create a separate thread that takes care of the
    // ORCA loop and detach it to run independently
    thread(Demo::loop).detach();
    
    // Run the Glut main loop
    glutMainLoop();
    
    return 0;
    
}
