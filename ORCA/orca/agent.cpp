/**
 * File  : agent.cpp
 * Author: Raja Soufi
 * 
 * Implementation of the Agent class defined
 * in agent.h.
 */

// Include header file
#include "agent.h"

/*
    Static Attributes
*/

/**
 * Global ID counter for the agent class.
 */
int Agent::id_counter = 0;

/*
    Constructors
*/

/**
 * Constructs an agent with position, radius and
 * max-speed equal to the ones given as parameters.
 * The constructed agent has a destination equal to
 * its position, as if it has already arrived to its
 * destination.
 * 
 * @param POSITION  - The position of the new agent
 * @param RADIUS    - The radius of the new agent
 * @param MAX_SPEED - The maximum speed of the new agent
 */
Agent::Agent(const Point& POSITION, const double RADIUS, const double MAX_SPEED) :
    id_(Agent::id_counter++),
    position_(POSITION),
    destination_(POSITION),
    velocity_(),
    prefVelocity_(),
    radius_(RADIUS),
    maxSpeed_(MAX_SPEED) {}

/**
 * Constructs an agent with initial position, destination,
 * radius and max speed equal to the ones given as
 * parameters.
 * The initial velocity of the new agent is set to zero.
 * 
 * @param POSITION    - The initial position of the new agent
 * @param DESTINATION - The destination of the new agent
 * @param RADIUS      - The radius of the new agent
 * @param MAX_SPEED   - The maximum speed of the new agent
 */
Agent::Agent(const Point& POSITION, const Point& DESTINATION, const double RADIUS, const double MAX_SPEED) :
    id_(Agent::id_counter++),
    position_(POSITION),
    destination_(DESTINATION),
    velocity_(),
    prefVelocity_(DESTINATION.from(POSITION).limitNorm(MAX_SPEED)),
    radius_(RADIUS),
    maxSpeed_(MAX_SPEED) {}

/*
    Destructor
*/

Agent::~Agent(void) {}

/*
    Other methods
*/

/**
 * Tests whether this agent has reached its destination
 * within the given threshold distance.
 * 
 * @param ARRIVAL_THRESHOLD - The maximum distance at which
 *                            this agent would be considered
 *                            to have reached its destination
 */
bool Agent::arrived(const double ARRIVAL_THRESHOLD/* = 0.0 */) const {
    return this->destination_.from(this->position_).norm() <= ARRIVAL_THRESHOLD;
}


/**
 * Moves this agent for DELTA_T time with its
 * current velocity, using the following equation:
 * 
 *            ########################
 *            #  p_new = p + v * dt  #
 *            ########################
 * 
 * @param DELTA_T - The time during which to move
 *                  this agent
 */
void Agent::move(const double DELTA_T) {
    this->position_ += this->velocity_ * DELTA_T;
    this->prefVelocity_ = this->destination_.from(this->position_).limitNorm(this->maxSpeed_);
}

/**
 * Updates the current velocity of this agent to the
 * one given as a parameter, after normalizing it to
 * the norm of this agent's preferred velocity in
 * case it exceeds it.
 * 
 * @param V - The new velocity for this agent
 */
void Agent::updateVelocity(const Vector& V) {
    this->velocity_ = Vector(V).limitNorm(this->prefVelocity_);
}


/**
 * Calls ORCA's function to solve a linear program
 * given a set of half-planes.
 * This intermediate function acts as a way to give
 * access to this agent's preferred velocity and
 * maximum speed for this particular task only.
 * Returns a point representing the solution to the
 * linear program.
 * 
 * @param halfPlanes - The set of half-planes to use
 *                     as input for the linear program
 */
Point Agent::solveLinearProgram(std::vector<HalfPlane>& halfPlanes) const {
    
    return ORCA::solveLinearProgram(halfPlanes, this->prefVelocity_, this->maxSpeed_);
    
}


/**
 * Returns ORCA_A^TAU, where A is this agent, as
 * a set of half-planes.
 * 
 * @param agents - The set of agents to consider
 *                 for ORCA_A^TAU
 * @param TAU    - The value of tau to be used
 *                 when computing ORCA_A^TAU
 */
std::vector<HalfPlane> Agent::orca_A(std::vector<Agent>& agents, const double TAU) const {
    
    // The set of half-planes representing ORCA_A^TAU
    std::vector<HalfPlane> halfPlanes;
    
    // For each agent B...
    for (Agent& agent : agents) {
        // Here we are assuming that B's maximum speed is equal to A's
        if ((*this != agent) &&
            (this->position_.from(agent.position()).norm() <= 2 * this->maxSpeed_))
        {
            // Compute ORCA_A|B^TAU and add it to ORCA_A^TAU
            halfPlanes.push_back(this->orca_A_B(agent, TAU));
        }
    }
    
    return halfPlanes;
    
}

/**
 * Returns ORCA_A|B^TAU as a half-plane, where A is
 * this agent and B is the agent given as a
 * parameter.
 * 
 * @param B   - The agent B to consider when
 *              computing ORCA_A|B^TAU
 * @param TAU - The value of tau to be used when
 *              computing ORCA_A|B^TAU
 */
HalfPlane Agent::orca_A_B(const Agent& B, const double TAU) const {
    
    // v_A - v_B
    Vector vDiff_A_B = this->velocity_ - B.velocity();
    
    Point voMainCircleCenter = B.position() - this->position_;
    Point voTruncationCircleCenter = voMainCircleCenter / TAU;
    
    double voMainCircleRadius = this->radius_ + B.radius();
    
    Vector axis(voMainCircleCenter);
    
    Point* closestCircleCenter = &voTruncationCircleCenter;
    
    double voHalfAperture = asin(voMainCircleRadius / Vector(voMainCircleCenter).norm());
    
    Vector leftProjection = vDiff_A_B.projectionOnto(axis.rotated(voHalfAperture));
    Vector rightProjection = vDiff_A_B.projectionOnto(axis.rotated(- voHalfAperture));
    
    // If the projection vector is orthogonal to or in the
    // opposite direction of the vector to p_B - p_A, then
    // vDiff_A_B can not possibly be in VO_A|B^TAU
    
    if (vDiff_A_B * axis > 0.0) {
        
        Vector& projection =
            (leftProjection * axis <= 0.0) ? rightProjection :
            (rightProjection * axis <= 0.0) ? leftProjection :
            (leftProjection.norm() > rightProjection.norm()) ? leftProjection : rightProjection;
        
        Point projectionCircleCenter = Line(Line(projection), vDiff_A_B).intersect(voMainCircleCenter);
        
        if (Vector(projectionCircleCenter).norm() > Vector(voTruncationCircleCenter).norm()) {
            closestCircleCenter = &projectionCircleCenter;
        }
        
    }
    
    double closestCircleRadius = voMainCircleRadius * Vector(*closestCircleCenter).norm() / axis.norm();
    
    Vector centerToV = vDiff_A_B - *closestCircleCenter;
    
    // In case v_A - v_B and the velocity obstacle's axis are
    // collinear, the vector from the center to the closest
    // border can be found using either of the left and right
    // projections. In this case we use the right one.
    // Otherwise ...
    Vector centerToBorder = (centerToV == 0.0) ?
        rightProjection - vDiff_A_B : Vector(centerToV).normalize(closestCircleRadius);
    
    Vector u = centerToBorder - centerToV;
    
    return HalfPlane(this->velocity_ + (u / 2.0), centerToBorder);
    
}
