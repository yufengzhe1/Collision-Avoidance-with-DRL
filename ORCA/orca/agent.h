/**
 * File  : agent.h
 * Author: Raja Soufi
 * 
 * Class definition of an agent with a position,
 * radius, destination.
 */

// Include guard
#ifndef _AGENT_H_
#define _AGENT_H_

// Inclusions
#include <vector>

#include "../geom/halfPlane.h"
#include "../geom/point.h"

#include "orca.h"

// Class definition
class Agent {
    
    #ifdef _DEMO_H_
    friend class Demo;
    #endif // _DEMO_H_
    
    private:
    
    // Attributes
    static int id_counter;
    
    int id_;
    Point position_, destination_;
    Vector velocity_, prefVelocity_;
    double radius_, maxSpeed_;
    
    public:
    
    // Constructors
    Agent(const Point& POSITION, const double RADIUS, const double MAX_SPEED);
    Agent(const Point& POSITION, const Point& DESTINATION, const double RADIUS, const double MAX_SPEED);
    
    // Destructor
    ~Agent(void);
    
    // Getters
    inline int id(void) const;
    inline const Point& position(void) const;
    inline const Vector& velocity(void) const;
    inline double radius(void) const;
    
    // Other methods
    bool arrived(const double ARRIVAL_THRESHOLD = 0.0) const;
    
    void move(const double DELTA_T);
    void updateVelocity(const Vector& V);
    
    Point solveLinearProgram(std::vector<HalfPlane>& halfPlanes) const;
    
    std::vector<HalfPlane> orca_A(std::vector<Agent>& agents, const double TAU) const;
    HalfPlane orca_A_B(const Agent& B, const double TAU) const;
    
    // Operators
    inline bool operator==(const Agent& THAT) const;
    inline bool operator!=(const Agent& THAT) const;
    
};

/*
    Getters
*/

/**
 * Returns the ID of this agent.
 */
inline int Agent::id(void) const {
    return this->id_;
}

/**
 * Returns the position of this agent.
 */
inline const Point& Agent::position(void) const {
    return this->position_;
}

/**
 * Returns the current velocity of this agent.
 */
inline const Vector& Agent::velocity(void) const {
    return this->velocity_;
}

/**
 * Returns the radius of this agent.
 */
inline double Agent::radius(void) const {
    return this->radius_;
}

/*
    Operators
*/

/**
 * Tests whether this agent is equal to the agent
 * passed as a parameter, in the sense that it is
 * the exact same agent with the same agent ID.
 * 
 * @param THAT - The agent to compare to this agent
 */
inline bool Agent::operator==(const Agent& THAT) const {
    return this->id_ == THAT.id();
}

/**
 * Tests whether this agent is different from the
 * agent passed as a parameter, in the sense that
 * they are different agents with different agent
 * IDs.
 * 
 * @param THAT - The agent to compare to this agent
 */
inline bool Agent::operator!=(const Agent& THAT) const {
    return !(*this == THAT);
}

#endif // _AGENT_H_
