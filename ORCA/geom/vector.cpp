/**
 * File  : vector.cpp
 * Author: Raja Soufi
 * 
 * Implementation of the Vector class defined
 * in vector.h.
 */

// Include header file
#include "vector.h"

/*
    Constructors
*/

/**
 * Constructs a vector with zero coordinates.
 */
Vector::Vector(void) : x_(0), y_(0) {}

/**
 * Constructs a vector with coordinates equal to the
 * ones given as parameters.
 * 
 * @param X - The x-coordinate of the new vector
 * @param Y - The y-coordinate of the new vector
 */
Vector::Vector(const double X, const double Y) : x_(X), y_(Y) {}

/**
 * Constructs a unit-vector that makes an angle with
 * the x-axis that is equal to the angle given as a
 * parameter.
 * 
 * @param X_ANGLE - The angle that the new vector
 *                  makes with the x-axis
 */
Vector::Vector(const double X_ANGLE) {
    double xAngleBound = trueMod(X_ANGLE, 2 * M_PI);
    this->x_ = cos(xAngleBound);
    this->y_ = sin(xAngleBound);
}

/** Constructs a vector with coordinates equal to those
 * of the point given as a parameter.
 * 
 * @param P - The point to be used to construct the
 *            new vector
 */
Vector::Vector(const Point& P) : x_(P.x()), y_(P.y()) {}

/**
 * Constructs a vector with coordinates equal to those
 * of the vector given as a parameter.
 * 
 * @param THAT - The vector to be used to construct
 *               the new vector
 */
Vector::Vector(const Vector& THAT) : x_(THAT.x()), y_(THAT.y()) {}

/*
    Destructor
*/

/**
 * Destroys this vector.
 */
Vector::~Vector(void) {}

/*
    Other methods
*/

/**
 * Normalizes this vector to the number given as a
 * parameter. If no number is given, the vector is
 * normalized to the unit-vector.
 * Returns this vector for chaining.
 * 
 * @param NEW_NORM - The number to use when normalizing
 *                   this vector
 */
const Vector& Vector::normalize(const double NEW_NORM/* = 1.0 */) {
    double norm = this->norm();
    if (norm != 0) {
        this->x_ *= NEW_NORM / norm;
        this->y_ *= NEW_NORM / norm;
    }
    return *this;
}

/**
 * Limits this vector's norm to the number given as
 * a parameter. If no number is given, the vector's
 * norm is limited to the unit-vector.
 * Returns this vector for chaining.
 * 
 * @param MAX_NORM - The number to which to limit this
 *                   vector's norm
 */
const Vector& Vector::limitNorm(const double MAX_NORM/* = 1.0 */) {
    if (this->norm() > MAX_NORM) {
        this->normalize(MAX_NORM);
    }
    return *this;
}

/**
 * Limits this vector's norm to that of the vector
 * given as a parameter.
 * Returns this vector for chaining.
 * 
 * @param THAT - The vector with the norm to which to
 *               limit this vector's norm
 */
const Vector& Vector::limitNorm(const Vector& THAT) {
    return limitNorm(THAT.norm());
}

/*
    Operators
*/

/**
 * Sets this vector's coordinates to those of the
 * vector given as a parameter.
 * Returns this vector for chaining.
 * 
 * @param THAT - The vector with the new coordinates
 */
Vector& Vector::operator=(const Vector& THAT) {
    if (this != &THAT) {
        this->x_ = THAT.x();
        this->y_ = THAT.y();
    }
    return *this;
}

/**
 * Adds the coordinates of the vector given as a
 * parameter to this vector's coordinates.
 * Returns this vector for chaining.
 * 
 * @param THAT - The vector with the coordinates to
 *               be added
 */
Vector& Vector::operator+=(const Vector& THAT) {
    this->x_ += THAT.x();
    this->y_ += THAT.y();
    return *this;
}

 /**
 * Subtracts the coordinates of the vector given as a
 * parameter from this vector's coordinates.
 * Returns this vector for chaining.
 * 
 * @param THAT - The vector with the coordinates to
 *               be subtracted
 */
Vector& Vector::operator-=(const Vector& THAT) {
    this->x_ -= THAT.x();
    this->y_ -= THAT.y();
    return *this;
}
