/**
 * File  : exceptions.cpp
 * Author: Raja Soufi
 * 
 * Implementations of the what functions for the
 * different exceptions defined in exceptions.h.
 */

// Include header file
#include "exceptions.h"

/*
    Line exceptions
*/

/**
 * Returns the description of the exception thrown.
 */
const char* LinesParallelException::what(void) const throw() {
    return "The two given lines do not have a unique intersection point.";
}

/**
 * Returns the description of the exception thrown.
 */
const char* LineVerticalException::what(void) const throw() {
    return "The given line does not contain a unique point with the given x coordinate.";
}

/**
 * Returns the description of the exception thrown.
 */
const char* LineHorizontalException::what(void) const throw() {
    return "The given line does not contain a unique point with the given y coordinate.";
}

/*
    ORCA exceptions
*/

/**
 * Returns the description of the exception thrown.
 */
const char* LinearProgramInfeasibleException::what() const throw() {
    return "The linear program was found to be infeasible during an iteration of ORCA.";
}
