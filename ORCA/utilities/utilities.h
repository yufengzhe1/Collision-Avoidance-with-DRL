/**
 * File  : utilities.h
 * Author: Raja Soufi
 * 
 * Definitions of useful constants, macros and
 * functions.
 */

// Include guard
#ifndef _UTILITIES_H_
#define _UTILITIES_H_

// Inclusions
#include <limits>
#include <cmath>

/*
    Constants
*/

/**
 * The representative value of infinity as a double.
 */
#define DOUBLE_INFINITY std::numeric_limits<double>::infinity()

/**
 * The value of 1 degree in radians.
 */
#define ONE_DEGREE_IN_RADIAN (M_PI / 180)

/*
    Functional macros
*/

/**
 * Returns min if v is smaller than min, otherwise
 * max if v is larger than max, otherwise v.
 */
#define CONSTRAIN_VALUE(v, min, max) ((v) < (min)) ? (min) : ((v) > (max)) ? (max) : (v)

/*
    Functions
*/

/**
 * Returns the true mathematically correct value
 * of a modulo n.
 * 
 * @param A - The left-hand operand of the modulo
 * @param N - The right-hand operand of the modulo
 */
inline double trueMod(double A, double N) {
    double r = fmod(A, N);//C 库函数 double fmod(double x, double y) 返回 x 除以 y 的余数。
    return (r < 0) ? r + N : r;
}

/**
 * Returns the value of signum(x) where x is the
 * number given as a parameter.
 * 
 * @param X - The input to signum
 */
inline int sign(double X) {
    return (X > 0) ? 1 : (X < 0) ? -1 : 0;
}

#endif
