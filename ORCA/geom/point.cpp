/**
 * File  : point.cpp
 * Author: Raja Soufi
 * 
 * Implementation of the Point class defined
 * in point.h.
 */

// Include header file
#include "point.h"

/*
    Constructors
*/

/**
 * Constructs a point with zero coordinates. The
 * constructed point is equivalent to the origin.
 */
Point::Point(void) : x_(0.0), y_(0.0) {}

/**
 * Constructs a point with coordinates equal to the
 * ones given as parameters.
 * 
 * @param X - The x-coordinate of the new point
 * @param Y - The y-coordinate of the new point
 */
Point::Point(const double X, const double Y) : x_(X), y_(Y) {}

/**
 * Constructs a point with coordinates equal to those
 * of the vector given as a parameter.
 * 
 * @param V - The vector to be used to construct the
 *            new point
 */
Point::Point(const Vector& V) : x_(V.x()), y_(V.y()) {}

/**
 * Constructs a point with coordinates equal to those
 * of the point given as a parameter.
 * 
 * @param THAT - The point to be used to construct
 *               the new point
 */
Point::Point(const Point& THAT) : x_(THAT.x()), y_(THAT.y()) {}

/*
    Destructor
*/

/**
 * Destroys this point
 */
Point::~Point(void) {}

/*
    Other methods
*/

/**
 * Returns a new vector with coordinates equal to those
 * of the difference between this point and the point
 * given as a parameter.
 * 
 * @param THAT - The point to subtract from this point
 *               in order to obtain the new vector
 */
Vector Point::from(const Point& THAT) const {
    return *this - THAT;
}

/**
 * Returns the porjection of this point onto the line
 * given as a parameter.
 * 
 * @param L - The line to project this point onto
 */
Point Point::projectionOnto(const Line& L) const {
    if (L.isVertical()) {
        return Point(L.xIntercept(), this->y_);
    } else {
        double denom = pow(L.slope(), 2.0) + 1.0;
        return Point((this->x_ + L.slope() * (this->y_ - L.yIntercept())) / denom,
            (L.slope() * (this->x_ + L.slope() * this->y_) + L.yIntercept()) / denom);
    }
}

/*
    Operators
*/

/**
 * Sets this point's coordinates to those of the
 * point given as a parameter.
 * Returns this point for chaining.
 * 
 * @param THAT - The point with the new coordinates
 */
Point& Point::operator=(const Point& THAT) {
    if (this != &THAT) {
        this->x_ = THAT.x();
        this->y_ = THAT.y();
    }
    return *this;
}

/**
 * Adds the coordinates of the point given as a
 * parameter to this point's coordinates.
 * Returns this point for chaining.
 * 
 * @param THAT - The point with the coordinates to
 *               be added
 */
Point& Point::operator+=(const Point& THAT) {
    this->x_ += THAT.x();
    this->y_ += THAT.y();
    return *this;
}

/**
 * Subtracts the coordinates of the point given as a
 * parameter from this point's coordinates.
 * Returns this point for chaining.
 * 
 * @param THAT - The point with the coordinates to
 *               be subtracted
 */
Point& Point::operator-=(const Point& THAT) {
    this->x_ -= THAT.x();
    this->y_ -= THAT.y();
    return *this;
}
