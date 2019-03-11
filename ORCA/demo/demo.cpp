/**
 * File  : demo.cpp
 * Author: Raja Soufi
 * 
 * Implementation of the Demo class defined
 * in demo.h.
 */

// Include header file
#include "demo.h"

/**
 * The width of the screen used for the demo.
 */
const int Demo::SCREEN_WIDTH = 640;

/**
 * The height of the screen used for the demo.
 */
const int Demo::SCREEN_HEIGHT = Demo::SCREEN_WIDTH;

/**
 * The zoom factor of the screen used for the demo.
 */
const double Demo::ZOOM = 0.01;

/**
 * Determines whether the demo is playing or paused.
 */
volatile bool Demo::paused = false;

/**
 * The speed factor of the demo.
 */
volatile double Demo::speed = 1.0;

/**
 * Determines whether an agent is being followed.
 */
bool Demo::following = false;

/**
 * The index of the agent being followed.
 */
int Demo::followed = 0;

/**
 * A configuration with 10 agents laid out in a
 * circle around the origin.
 * Each agent's destination is the antipode of its
 * initial position on the circle.
 */
const vector<Agent> Demo::CIRCLE_CONFIGURATION = {
    Agent(Point( 60.0,   0.0), Point(-60.0,   0.0), 8.0, 20.0),
    Agent(Point( 48.5,  35.3), Point(-48.5, -35.3), 8.0, 20.0),
    Agent(Point( 18.5,  57.1), Point(-18.5, -57.1), 8.0, 20.0),
    Agent(Point(-18.5,  57.1), Point( 18.5, -57.1), 8.0, 20.0),
    Agent(Point(-48.5,  35.3), Point( 48.5, -35.3), 8.0, 20.0),
    Agent(Point(-60.0,   0.0), Point( 60.0,   0.0), 8.0, 20.0),
    Agent(Point(-48.5, -35.3), Point( 48.5,  35.3), 8.0, 20.0),
    Agent(Point(-18.5, -57.1), Point( 18.5,  57.1), 8.0, 20.0),
    Agent(Point( 18.5, -57.1), Point(-18.5,  57.1), 8.0, 20.0),
    Agent(Point( 48.5, -35.3), Point(-48.5,  35.3), 8.0, 20.0)
};

/**
 * A configuration with 10 agents divided into two
 * groups positioned at either sides of the screen.
 * Each agent's destination is at the opposite side
 * of the screen.
 */
const vector<Agent> Demo::TWO_LINE_CONFIGURATION = {
    Agent(Point( 60.0,  80.0), Point(-60.0,  80.0), 8.0, 20.0),
    Agent(Point( 60.0,  40.0), Point(-60.0,  40.0), 8.0, 20.0),
    Agent(Point( 60.0,   0.0), Point(-60.0,   0.0), 8.0, 20.0),
    Agent(Point( 60.0, -40.0), Point(-60.0, -40.0), 8.0, 20.0),
    Agent(Point( 60.0, -80.0), Point(-60.0, -80.0), 8.0, 20.0),
    Agent(Point(-60.0,  80.0), Point( 60.0,  80.0), 8.0, 20.0),
    Agent(Point(-60.0,  40.0), Point( 60.0,  40.0), 8.0, 20.0),
    Agent(Point(-60.0,   0.0), Point( 60.0,   0.0), 8.0, 20.0),
    Agent(Point(-60.0, -40.0), Point( 60.0, -40.0), 8.0, 20.0),
    Agent(Point(-60.0, -80.0), Point( 60.0, -80.0), 8.0, 20.0)
};

/**
 * A configuration with 4 agents positioned at the
 * corners of a square centered at the origin.
 * Each agent's destination is at the opposite
 * end of the square following the diagonals.
 */
const vector<Agent> Demo::SQUARE_CONFIGURATION = {
    Agent(Point(-60.0,  60.0), Point( 60.0, -60.0), 8.0, 20.0),
    Agent(Point( 60.0, -60.0), Point(-60.0,  60.0), 8.0, 20.0),
    Agent(Point( 60.0,  60.0), Point(-60.0, -60.0), 8.0, 20.0),
    Agent(Point(-60.0, -60.0), Point( 60.0,  60.0), 8.0, 20.0)
};

/**
 * A configuration with 6 agents positioned randomly
 * and with random destinations.
 */
const vector<Agent> Demo::RANDOM_CONFIGURATION = {
    Agent(Point(  1.0,   1.0), Point(  0.0,   0.0), 8.0, 20.0),
    Agent(Point( 60.0,  15.0), Point(-60.0,   0.0), 8.0, 20.0),
    Agent(Point( 40.0,  -5.0), Point(-20.0,  30.0), 8.0, 20.0),
    Agent(Point( -5.0, -30.0), Point(-40.0,  50.0), 8.0, 20.0),
    Agent(Point(-50.0,  15.0), Point( 40.0, -10.0), 8.0, 20.0),
    Agent(Point(-60.0,   0.0), Point( 60.0,   0.0), 8.0, 20.0)
};

/**
 * The configuration to use for the demo.
 */
const vector<Agent>& Demo::CONFIGURATION = Demo::SQUARE_CONFIGURATION;

/*
    Function definitions
*/

/**
 * Initialises the drawing configuration.
 */
void Demo::initDrawing(void) {
    
    // Enable blending
    glEnable(GL_BLEND);
    
    // Set blending function.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Set background color
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    
}

/*
    Drawing functions
*/

/**
 * Draws a frame to the screen.
 */
void Demo::draw(void) {
    
    // Clear the current window
    glClear(GL_COLOR_BUFFER_BIT);
    // Set the matrix mode to modify the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    // Initialise the modelview matrix to the identity matrix
    glLoadIdentity();
    
    // If following mode is enabled, then follow an agent
    if (Demo::following) {
        Demo::follow(Demo::followed);
    }
    
    const int FIRST_ID = ORCA::agents()[0].id();
    const double HUE_OFFSET = 1.0 / ORCA::agentCount();
    
    // Draw agents
    for (Agent& agent : ORCA::agents()) {
        Demo::drawCircle(agent.position(), agent.radius(),
            Color((agent.id() - FIRST_ID) * HUE_OFFSET, 1.0, 1.0, 0.7, false));
    }
    
    // Draw x/y unit vectors
    Demo::drawVector(Point(), Vector(1.0, 0.0), Color::RED);
    Demo::drawVector(Point(), Vector(0.0, 1.0), Color::GREEN);
    
    // Swap the back buffer with the front buffer
    glutSwapBuffers();
    
}

/**
 * Follows the agent with index equal to the integer
 * given as a parameter by drawing useful information
 * related to that agent to the screen, such as its
 * maximum speed radius, half-planes in its ORCA
 * domain, its preferred velocity and current
 * velocity, and its destination.
 * 
 * @param INDEX - The index of the agent to follow
 */
void Demo::follow(const int INDEX) {
    
    Agent& agent = ORCA::agents()[INDEX];
    
    int i = 0;
    const double HUE_OFFSET = 1.0 / ORCA::agentCount();
    
    vector<HalfPlane> halfPlanes = agent.orca_A(ORCA::agents(), ORCA::tau());
    
    // Draw half-planes
    for (vector<HalfPlane>::iterator halfPlane = halfPlanes.begin() ;
        halfPlane != halfPlanes.end() ; i++)
    {
        if (i != INDEX) {
            Demo::drawHalfPlane(HalfPlane(halfPlane->normalPosition() + agent.position(),
                halfPlane->normal()), Color(i * HUE_OFFSET, 1.0, 1.0, 1.0, false));
            halfPlane++;
        }
    }
    
    // Draw agent's destination
    Demo::drawPoint(agent.destination_, Color::WHITE);
    
    // Draw vMax circle
    Demo::drawCircle(agent.position(), agent.maxSpeed_, Color(1.0, 1.0, 1.0, 0.5));
    
    // Draw prefVelocity and velocity
    Demo::drawVector(agent.position(), agent.prefVelocity_, Color::WHITE);
    Demo::drawVector(agent.position(), agent.velocity(), Color::BLACK);
    
}

/**
 * Draws a point in a color given as a parameter.
 * 
 * @param P     - The point to draw
 * @param COLOR - The color to use to draw the point
 */
void Demo::drawPoint(const Point& P, const Color& COLOR) {
    
    glPushMatrix();
        
        glPointSize(5.0);
        glColor4d(COLOR.red(), COLOR.green(), COLOR.blue(), COLOR.alpha());
        
        glBegin(GL_POINTS);
            glVertex2d(P.x(), P.y());
        glEnd();
        
    glPopMatrix();
    
}

/**
 * Draws a vector at a specific position in a color
 * given as a parameter.
 * 
 * @param POSITION - The position at which to draw
 *                   the vector
 * @param V        - The vector to draw
 * @param COLOR    - The color to use to draw the
 *                   vector
 */
void Demo::drawVector(const Point& POSITION, const Vector& V, const Color& COLOR) {
    
    double arrowHeadSize = V.norm() / 5.0;
    
    glPushMatrix();
        
        glLoadIdentity();
        
        glTranslatef(POSITION.x(), POSITION.y(), 0.0);
        glRotatef(V.xAngle() * 180 / M_PI, 0.0, 0.0, 1.0);
        
        glColor4d(COLOR.red(), COLOR.green(), COLOR.blue(), COLOR.alpha());
        
        glBegin(GL_LINES);
            glVertex2d(0.0, 0.0);
            glVertex2d(V.norm(), 0.0);
            
            glVertex2d(V.norm(), 0.0);
            glVertex2d(V.norm() - arrowHeadSize, - 0.5 * arrowHeadSize);
            
            glVertex2d(V.norm(), 0.0);
            glVertex2d(V.norm() - arrowHeadSize, 0.5 * arrowHeadSize);
        glEnd();
        
    glPopMatrix();
    
}

/**
 * Draws a circle in a color given as a parameter.
 * 
 * @param POSITION - The position of the center of the
 *                   circle to draw
 * @param RADIUS   - The radius of the circle to draw
 * @param COLOR    - The color to use to draw the
 *                   circle
 */
void Demo::drawCircle(const Point& POSITION, const double RADIUS, const Color& COLOR) {
    
    double rad = 0;
    
    glPushMatrix();
        
        glLoadIdentity();
        
        glTranslated(POSITION.x(), POSITION.y(), 0.0);
        
        glColor4d(COLOR.red(), COLOR.green(), COLOR.blue(), COLOR.alpha());
        
        glBegin(GL_POLYGON);
            for (int i = 0 ; i < 36 ; i++) {
                glVertex2d(RADIUS * cos(rad), RADIUS * sin(rad));
                rad += 10 * ONE_DEGREE_IN_RADIAN;
            }
        glEnd();
        
    glPopMatrix();
    
}

/**
 * Draws a half-plane in a color given as a parameter.
 * 
 * @param HALF_PLANE - The half-plane to draw
 * @param COLOR      - The color to use to draw the
 *                     half-plane
 */
void Demo::drawHalfPlane(const HalfPlane& HALF_PLANE, const Color& COLOR) {
    
    double x1, y1, x2, y2, x3, y3, x4, y4;
    
    double distanceToBoundingLine = 1.0 / Demo::ZOOM;
    
    if (HALF_PLANE.boundingLine().isVertical()) {
        x1 = HALF_PLANE.normalPosition().x();
        y1 = - distanceToBoundingLine;
        x2 = x1;
        y2 = distanceToBoundingLine;
        x3 = (HALF_PLANE.normal().x() > 0) ? distanceToBoundingLine : - distanceToBoundingLine;
        y3 = distanceToBoundingLine;
        x4 = x3;
        y4 = - distanceToBoundingLine;
    } else if (HALF_PLANE.boundingLine().isHorizontal()) {
        x1 = - distanceToBoundingLine;
        y1 = HALF_PLANE.normalPosition().y();
        x2 = distanceToBoundingLine;
        y2 = y1;
        x3 = distanceToBoundingLine;
        y3 = (HALF_PLANE.normal().y() > 0) ? distanceToBoundingLine : - distanceToBoundingLine;
        x4 = - distanceToBoundingLine;
        y4 = y3;
    } else {
        x1 = - distanceToBoundingLine;
        y1 = HALF_PLANE.boundingLine().getPointAtX(x1).y();
        x2 = distanceToBoundingLine;
        y2 = HALF_PLANE.boundingLine().getPointAtX(x2).y();
        if (HALF_PLANE.normal().y() > 0) {
            if (HALF_PLANE.normal().x() > 0) {
                x3 = distanceToBoundingLine;
                x4 = (y1 < distanceToBoundingLine) ? - distanceToBoundingLine : distanceToBoundingLine;
            } else {
                x3 = (y2 < distanceToBoundingLine) ? distanceToBoundingLine : - distanceToBoundingLine;
                x4 = - distanceToBoundingLine;
            }
            y3 = distanceToBoundingLine;
            y4 = distanceToBoundingLine;
        } else {
            if (HALF_PLANE.normal().x() > 0) {
                x3 = distanceToBoundingLine;
                x4 = (y1 > - distanceToBoundingLine) ? - distanceToBoundingLine : distanceToBoundingLine;
            } else {
                x3 = (y2 > - distanceToBoundingLine) ? distanceToBoundingLine : - distanceToBoundingLine;
                x4 = - distanceToBoundingLine;
            }
            y3 = - distanceToBoundingLine;
            y4 = - distanceToBoundingLine;
        }
    }
    
    glPushMatrix();
        
        glLoadIdentity();
        
        glColor3d(COLOR.red(), COLOR.green(), COLOR.blue());
        
        glBegin(GL_LINES);
            glVertex2d(x1, y1);
            glVertex2d(x2, y2);
        glEnd();
        
        glColor4d(COLOR.red(), COLOR.green(), COLOR.blue(), 0.1);
        
        glBegin(GL_POLYGON);
            glVertex2d(x1, y1);
            glVertex2d(x2, y2);
            glVertex2d(x3, y3);
            glVertex2d(x4, y4);
        glEnd();
        
        drawVector(HALF_PLANE.normalPosition(), Vector(HALF_PLANE.normal()).normalize(10.0), COLOR);
        
    glPopMatrix();
    
}

/**
 * Readjusts the viewport and projection when the
 * screen is reshaped.
 * 
 * @param width  - The new width of the screen
 * @param height - The new height of the screen
 */
void Demo::reshape(int width, int height) {
    
    // Set the viewport to be the same width and height as the window
    glViewport(0, 0, width, height);
    
    // Set the matrix mode to modify the projection matrix
    glMatrixMode(GL_PROJECTION);
    
    // Initialise the projection matrix to the identity matrix
    glLoadIdentity();
    
    // Set up the projection
    gluOrtho2D(-1.0 / Demo::ZOOM, 1.0 / Demo::ZOOM, -1.0 / Demo::ZOOM, 1.0 / Demo::ZOOM);
    
    // Redraw the screen
    glutPostRedisplay();
    
}

/**
 * Handles key presses.
 * 
 * @param k - The key that was pressed
 * @param x - The x-position of the mouse when the
 *            key was pressed
 * @param y - The y-position of the mouse when the
 *            key was pressed
 */
void Demo::key(unsigned char k, int x, int y) {
    
    switch (k) {
        
        // Pause/Resume the demo
        case 'p':
            Demo::paused = !Demo::paused;
            cout << (Demo::paused ? "Demo paused." : "Demo resumed.") << endl;
            break;
        
        // Slow down the demo
        case '-':
            if (Demo::speed > 0.015625) {
                Demo::speed /= 2.0;
                cout << "Demo speed decreased to " << Demo::speed << "x." << endl;
            }
            break;
        
        // Speed up the demo
        case '=':
            if (Demo::speed < 16.0) {
                Demo::speed *= 2.0;
                cout << "Demo speed increased to " << Demo::speed << "x." << endl;
            }
            break;
        
        // Start/Stop following agents
        case 'f':
            Demo::following = !Demo::following;
            if (Demo::following) {
                cout << "Started following agent " << Demo::followed << " from the demo..." << endl;
            } else {
                cout << "Stopped following agents." << endl;
            }
            // Redraw the screen
            glutPostRedisplay();
            break;
        
        // Follow previous agent
        case ',':
            Demo::followed = (Demo::followed <= 0) ?
                Demo::CONFIGURATION.size() - 1 : Demo::followed - 1;
            if (Demo::following) {
                cout << "Following agent " << Demo::followed << " from the demo..." << endl;
            }
            // Redraw the screen
            glutPostRedisplay();
            break;
        
        // Follow next agent
        case '.':
            Demo::followed = (Demo::followed >= Demo::CONFIGURATION.size() - 1) ?
                0 : Demo::followed + 1;
            if (Demo::following) {
                cout << "Following agent " << Demo::followed << " from the demo..." << endl;
            }
            // Redraw the screen
            glutPostRedisplay();
            break;
        
    }
    
}

/**
 * Runs when glut is idle.
 */
void Demo::idle(void) {}

/**/

/**
 * Runs the main loop of the demo.
 */
void Demo::loop(void) {
    
    cout << "Started the ORCA loop." << endl;
    
    // While the system hasn't converged yet...
    while(!ORCA::converged()) {
        
        // If the demo is paused, wait
        while(Demo::paused);
        
        // Run a single iteration
        ORCA::iteration();
        
        // Sleep for deltaT time
        struct timespec sleepTime;
        sleepTime.tv_sec = 0;
        sleepTime.tv_nsec = 1000000000L * ORCA::deltaT() / Demo::speed;
        nanosleep(&sleepTime, NULL);
        
        // Move the agents for the waited
        // deltaT time
        ORCA::moveAgents(ORCA::deltaT());
        
        // Redraw the screen
        glutPostRedisplay();
        
    }
    
    cout << "All agents have converged to their final destinations." << endl;
    
    ORCA::finalize();
    
}
