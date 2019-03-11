/**
 * File  : orca.h
 * Author: Raja Soufi
 * 
 * Class definition of the ORCA system.
 */

// Include guard
#ifndef _ORCA_H_
#define _ORCA_H_

// Inclusions
#include <algorithm>
#include <cmath>
#include <vector>

#include "../geom/point.h"

#include "../utilities/exceptions.h"
#include "../utilities/utilities.h"

#include "agent.h"

// Forward-declarations
class Agent;

// Class definition
class ORCA {
    
    private:
    
    // Attributes
    static std::vector<Agent> agents_;
    static double tau_;
    static double deltaT_;
    static double arrivalThreshold_;
    
    // Constructor
    ORCA(void);
    
    public:
    
    // Getters
    static inline std::vector<Agent>& agents(void);
    static inline double tau(void);
    static inline double deltaT(void);
    static inline double arrivalThreshold(void);
    
    // Other methods
    static inline int agentCount(void);
    
    static void initialize(const std::vector<Agent>& AGENTS, const double TAU,
        const double DELTA_T, const double ARRIVAL_THRESHOLD);
    
    static Point solveLinearProgram(std::vector<HalfPlane>& H, const Vector& V_PREF,
        const double MAX_SPEED);
    
    static void iteration(void);
    static void moveAgents(const double DELTA_T);
    static bool converged(void);
    static void finalize(void);
    
};

/*
    Getters
*/

/**
 * Returns the set of agents registered in the system.
 */
inline std::vector<Agent>& ORCA::agents(void) {
    return ORCA::agents_;
}

/**
 * Returns the value of tau used for ORCA.
 */
inline double ORCA::tau(void) {
    return ORCA::tau_;
}

/**
 * Returns the value of deltaT used for ORCA.
 */
inline double ORCA::deltaT(void) {
    return ORCA::deltaT_;
}

/**
 * Returns the maximum distance between an agent A
 * and its destination for which A would be
 * considered as arrived.
 */
inline double ORCA::arrivalThreshold(void) {
    return ORCA::arrivalThreshold_;
}

/*
    Other methods
*/

/**
 * Returns the number of agents registered in the
 * system.
 */
inline int ORCA::agentCount(void) {
    return ORCA::agents_.size();
}

#endif // _ORCA_H_
