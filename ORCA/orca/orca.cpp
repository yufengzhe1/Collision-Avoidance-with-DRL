/**
 * File  : orca.cpp
 * Author: Raja Soufi
 * 
 * Implementation of the ORCA class defined
 * in orca.h.
 */

// Include header file
#include "orca.h"

/*
    Static Attributes
*/

/**
 * The set of agents registered in the system.
 */
std::vector<Agent> ORCA::agents_;

/**
 * The value of tau to be used for the ORCA system.
 */
double ORCA::tau_ = 0.0;

/**
 * The value of deltaT to be used for the ORCA system.
 */
double ORCA::deltaT_ = 0.0;

/**
 * The maximum distance between an agent A and its
 * destination for which A would be considered as
 * arrived.
 */
double ORCA::arrivalThreshold_ = 0.0;

/*
    Methods
*/

/**
 * Initializes the system with a set of agents, a value of
 * tau, and an arrival threshold given as parameters.
 * 
 * @param AGENTS            - The agents to register in the system
 * @param TAU               - The value of tau to use for the ORCA
 *                            system
 * @param ARRIVAL_THRESHOLD - The arrival threshold to be used
 */
void ORCA::initialize(const std::vector<Agent>& AGENTS, const double TAU,
    const double DELTA_T, const double ARRIVAL_THRESHOLD)
{
    ORCA::agents_ = std::vector<Agent>(AGENTS);
    ORCA::tau_ = TAU;
    ORCA::deltaT_ = DELTA_T;
    ORCA::arrivalThreshold_ = ARRIVAL_THRESHOLD;
}

/**
 * Solves a linear program given a set of half-planes
 * as input, as well as a preferred velocity and a
 * maximum speed.
 * Returns a point representing the solution to the
 * linear program.
 * 
 * @param H         - The set of half-planes to use
 *                    as input for the linear program
 * @param V_PREF    - The preferred velocity to use as
 *                    as input for the linear program
 * @param MAX_SPEED - The maximum speed to use as
 *                    input for the linear program
 */
Point ORCA::solveLinearProgram(std::vector<HalfPlane>& H,
    const Vector& V_PREF, const double MAX_SPEED)
{
    // Number of input half-planes
    size_t n = H.size();
    
    // Compute a random permutation of the half-planes
    std::random_shuffle(H.begin(), H.end());
    
    Vector vMax = Vector(V_PREF);
    
    // Initialize the solution to be the furthest point on
    // the circle of radius MAX_SPEED in the direction of V_PREF
    Point solution = vMax;
    
    // Loop through the shuffled half-planes
    for (std::vector<HalfPlane>::iterator h_i = H.begin() ; h_i != H.end() ; h_i++) {
        
        // If the next half-plane does not contain the
        // current solution, compute the new solution
        // or report that the program is infeasible
        if (!h_i->contains(solution)) {
            
            // Find the number of intersections between h_i's bounding
            // line and the circle of radius MAX_SPEED
            // Line     : y = slope * x + yIntercept
            // Circle   : x^2 + y^2 = MAX_SPEED^2
            // Equation to solve :
            //     (slope^2 + 1) * x^2 + 2 * slope * yIntercept * x + yIntercept^2 - MAX_SPEED^2 = 0
            
            double discriminant;
            double a = pow(h_i->boundingLine().slope(), 2.0) + 1.0;
            double b = 2.0 * h_i->boundingLine().slope() * h_i->boundingLine().yIntercept();
            
            // If the h_i's bounding line is vertical then we
            // hard-code the values of the discriminant
            if (h_i->boundingLine().isVertical()) {
                discriminant = sign(MAX_SPEED - abs(h_i->boundingLine().xIntercept()));
            } else {
                // discriminant = 4 * (MAX_SPEED^2 * (slope^2 + 1) - yIntercept^2)
                discriminant = 4.0 * (pow(MAX_SPEED, 2.0) * a - pow(h_i->boundingLine().yIntercept(), 2.0));
            }
            
            // If the discriminant is strictly negative then...
            if (discriminant < 0.0) {
                // ...either h_i completely contains the circle in which
                // case any point on the circle satisfies the constraint
                // introduced by h_i and we can simply ignore it...
                if (h_i->normal() * h_i->normalPosition().from(Point()) < 0.0) {
                    continue;
                }
                // ...or the circle is completely outside h_i in which case
                // no point on the circle satisfies the constraint introduced
                // by h_i and we report that the program is infeasible
                else {
                    throw LinearProgramInfeasibleException();
                }
            }
            // If the discriminant is equal to zero then...
            else if (discriminant == 0.0) {
                // ...either h_i completely contains the circle in which
                // case any point on the circle satisfies the constraint
                // introduced by h_i, including the intersection point,
                // and we can simply ignore it...
                if (h_i->normal() * h_i->normalPosition().from(Point()) < 0.0) {
                    continue;
                }
                // ...or the only point on the circle that h_i contains
                // is the intersection point, which means that h_i alone
                // constrains the solution to a single point. Two cases
                // are possible here:
                //     - All other half-planes contain this point in
                //       which case we return it as the solution to
                //       the linear program
                //     - There exists at least one half-plane that
                //       does not contain this point in which case
                //       we report that the program is infeasible
                // Therefore, we do one final traversal of H in order to
                // check whether all half-planes contain the intersection
                // point and act accordingly
                else {
                    solution = h_i->boundingLine().isVertical() ? h_i->boundingLine().getPointAtY(0.0) :
                        h_i->boundingLine().getPointAtX(- b / (2.0 * a));
                    
                    for (h_i = H.begin() ; h_i != H.end() ; h_i++) {
                        if (!h_i->contains(solution)) {
                            throw LinearProgramInfeasibleException();
                        }
                    }
                    
                    // At this point, we are certain that all half-planes
                    // contain the solution, so we break out of the
                    // for-loop and return it
                    break;
                }
            }
            // If the discriminant is strictly positive then...
            else {
                // left and right represent the parametrised constraints
                // on the position of the solution on the bounding line of
                // h_i. If the bounding line is not vertical, they are the
                // same as xLeft and xRight from the formal definition of
                // the algorithm. If however the bounding line is vertical,
                // then left and right are computed in an analogous way in
                // the y-dimension, and can be thought of as "yLeft" and
                // "yRight" respectively. The property of being "left" or
                // "right" on a half-plane's bounding line is determined
                // with respect to its normal, and is therefore fully
                // defined even for a vertical bounding line.
                double left, right;
                
                // If h_i's bounding line is vertical, then we compute left
                // and right (for which a better name in this case would be
                // "up" and "down" for example) using Pythagoras' theorem.
                if (h_i->boundingLine().isVertical()) {
                    left = sqrt(pow(MAX_SPEED, 2.0) - pow(h_i->boundingLine().xIntercept(), 2.0));
                    right = - left;
                }
                // If h_i's bounding line is not vertical, then the
                // previously computed discriminant is valid and we use it
                // to compute left and right.
                else {
                    left  = (- b - sqrt(discriminant)) / (2.0 * a);
                    right = (- b + sqrt(discriminant)) / (2.0 * a);
                }
                
                // If h_i's normal is facing downwards, or left in case
                // h_i's bounding line is vertical, then left and right
                // should be swapped.
                if ((h_i->boundingLine().isVertical() && (h_i->normal().x() < 0.0)) ||
                    (!h_i->boundingLine().isVertical() && (h_i->normal().y() < 0.0)))
                {
                    std::swap(left, right);
                }
                
                // Loop through the half-planes in H_i-1
                for (std::vector<HalfPlane>::iterator h = H.begin() ; h != h_i ; h++) {
                    
                    // If the bounding line of h is parallel to that
                    // of h_i, then...
                    if (h_i->boundingLine() || h->boundingLine()) {
                        
                        // ...either their intersection is not empty in
                        // which case any point on the bounding line of h_i
                        // satisfies h and we can simply ignore it...
                        if ((h_i->normal() * h->normal() > 0.0) || (h_i->contains(h->normalPosition()))) {
                            continue;
                        }
                        // ...or their intersection is empty in which case no
                        // point on the bounding line of h_i satisfies h and
                        // we report that the linear program is infeasible
                        else {
                            throw LinearProgramInfeasibleException();
                        }
                    }
                    
                    // If the bounding line of h is not parallel to
                    // that of h_i, then we compute their intersection
                    // and use it to update either left or right.
                    else {
                        
                        double angleDiff = trueMod(h_i->normal().angleFrom(h->normal()), 2.0 * M_PI);
                        Point intersection = h_i->boundingLine().intersect(h->boundingLine());
                        
                        // If the angle difference between the normals is
                        // smaller than PI, then it is left that must be
                        // updated, in case we need to update at all.
                        if (angleDiff < M_PI) {
                            if (h_i->boundingLine().isVertical() &&
                                ((h_i->normal().x() < 0.0) == (intersection.y() > left)))
                            {
                                left = intersection.y();
                            }
                            
                            else if (!h_i->boundingLine().isVertical() &&
                                ((h_i->normal().y() < 0.0) == (intersection.x() < left)))
                            {
                                left = intersection.x();
                            }
                        }
                        
                        // If the angle difference between the normals is
                        // larger than PI, then it is right that must be
                        // updated, in case we need to update at all.
                        else {
                            if (h_i->boundingLine().isVertical() &&
                                ((h_i->normal().x() < 0.0) == (intersection.y() < right)))
                            {
                                right = intersection.y();
                            }
                            
                            else if (!h_i->boundingLine().isVertical() &&
                                ((h_i->normal().y() < 0.0) == (intersection.x() > right)))
                            {
                                right = intersection.x();
                            }
                        }
                        
                    }
                    
                }
                
                // If h_i's normal is facing downwards or right and left
                // is smaller than right, or if it's facing upwards or
                // left and left is larger than right, then we report that
                // the linear program is infeasible
                if
                (
                    (
                        (
                            (h_i->boundingLine().isVertical() && (h_i->normal().x() > 0.0))
                        ||
                            (!h_i->boundingLine().isVertical() && (h_i->normal().y() < 0.0))
                        )
                    &&
                        (left < right)
                    )
                ||
                    (
                        (
                            (h_i->boundingLine().isVertical() && (h_i->normal().x() < 0.0))
                        ||
                            (!h_i->boundingLine().isVertical() && (h_i->normal().y() > 0.0))
                        )
                    &&
                        (left > right)
                    )
                ) {
                    throw LinearProgramInfeasibleException();
                }
                
                // Project vMax onto h_i's bounding line
                Point projection = Point(vMax).projectionOnto(h_i->boundingLine());
                
                // Set the solution to be either the previously computed
                // projection, or left or right, depending on whether the
                // projection lies in the interval bound by left and right.
                if (h_i->boundingLine().isVertical() &&
                    ((h_i->normal().x() < 0.0) == (projection.x() < left)))
                {
                    solution = h_i->boundingLine().getPointAtY(left);
                }
                else if (h_i->boundingLine().isVertical() &&
                    ((h_i->normal().x() < 0.0) == (projection.x() > right)))
                {
                    solution = h_i->boundingLine().getPointAtY(right);
                }
                else if (!h_i->boundingLine().isVertical() &&
                    ((h_i->normal().y() < 0.0) == (projection.x() > left)))
                {
                    solution = h_i->boundingLine().getPointAtX(left);
                }
                else if (!h_i->boundingLine().isVertical() &&
                    ((h_i->normal().y() < 0.0) == (projection.x() < right)))
                {
                    solution = h_i->boundingLine().getPointAtX(right);
                }
                else {
                    solution = projection;
                }
                
                
            }
            
        }
        
    }
    
    // Return the solution
    return solution;
}

/**
 * Executes a single iteration of ORCA.
 */
void ORCA::iteration(void) {
    
    std::vector<Vector> newVelocities;
    newVelocities.reserve(ORCA::agentCount());
    
    // Compute ORCA's and new velocities
    for (Agent& agent : ORCA::agents_) {
        
        std::vector<HalfPlane> halfPlanes = agent.orca_A(ORCA::agents_, ORCA::tau_);
        
        newVelocities.push_back(agent.solveLinearProgram(halfPlanes));
        
    }
    
    std::vector<Vector>::iterator newVelocity = newVelocities.begin();
    
    // Update velocities
    for (Agent& agent : ORCA::agents_) {
        
        agent.updateVelocity(*newVelocity);
        
        newVelocity++;
        
    }
}

/**
 * Moves agents for DELTA_T time one by one.
 * 
 * @param DELTA_T - The time during which to move
 *                  the agents
 */
void ORCA::moveAgents(const double DELTA_T) {
    
    // Move agents
    for (Agent& agent : ORCA::agents_) {
        
        agent.move(DELTA_T);
        
    }
    
}

/**
 * Tests whether the system has converged, in the
 * sense of that all agents are within the arrival
 * threshold from their respective destinations.
 */
bool ORCA::converged(void) {
    
    // Loop through the agents
    for (Agent& agent : ORCA::agents_) {
        
        // If one of the agents has not arrived
        // yet, then return false
        if (!agent.arrived(ORCA::arrivalThreshold_)) {
            return false;
        }
        
    }
    
    // If all agents have arrived,
    // then return true
    return true;
}

/**
 * Runs finalization code that is executed when
 * the system converges and is about to terminate.
 * Any cleaning up that should be done before
 * terminating goes here.
 */
void ORCA::finalize(void) {}
