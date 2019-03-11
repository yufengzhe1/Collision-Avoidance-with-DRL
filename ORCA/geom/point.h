/**
 * File  : point.h
 * Author: Raja Soufi
 * 
 * Class definition of a Point in 2D space:
 * 
 *              #############
 *              #  P(x, y)  #
 *              #############
 */

// Include guard
#ifndef _POINT_H_
#define _POINT_H_

// Inclusions
#include "line.h"
#include "vector.h"

// Forward-declarations
class Line;
class Vector;

// Class definition
class Point {
    
    private:
    
    // Attributes
    double x_, y_;
    
    public:
    
    // Constructors
    Point(void);
    Point(const double X, const double Y);
    Point(const Vector& V);
    Point(const Point& THAT);
    
    // Destructor
    ~Point(void);
    
    // Getters
    inline double x(void) const;
    inline double y(void) const;
    
    // Other methods
    Vector from(const Point& THAT) const;
    Point projectionOnto(const Line& L) const;
    
    // Operators
    inline const Point operator+(const Point& THAT) const;
    inline const Point operator-(const Point& THAT) const;
    inline const Point operator-(void) const;
    
    inline const Point operator*(const double D) const;
    inline const Point operator/(const double D) const;
    
    Point& operator=(const Point& THAT);
    Point& operator+=(const Point& THAT);
    Point& operator-=(const Point& THAT);
    
    inline bool operator==(const Point& THAT) const;
    inline bool operator!=(const Point& THAT) const;
    
};

/*
    Getters
*/

/**
 * Returns the x-coordinate of this point.
 */
inline double Point::x(void) const {
    return this->x_;
}

/**
 * Returns the y-coordinate of this point.
 */
inline double Point::y(void) const {
    return this->y_;
}

/*
    Operators
*/

/**
 * Returns a new point which is the sum of this point
 * and the point given as a parameter.
 * The sum of two points is considered to be defined
 * as follows:
 * 
 *       ######################################
 *       #  (x_1, y_1) + (x_2, y_2) =         #
 *       #            (x_1 + x_2, y_1 + y_2)  #
 *       ######################################
 * 
 * @param THAT - The point to add to this point
 */
inline const Point Point::operator+(const Point& THAT) const {
    return Point(*this) += THAT;
}

/**
 * Returns a new point which is the difference between
 * this point and the point given as a parameter.
 * The difference between two points is considered to
 * be defined as follows:
 * 
 *       ######################################
 *       #  (x_1, y_1) - (x_2, y_2) =         #
 *       #            (x_1 - x_2, y_1 - y_2)  #
 *       ######################################
 * 
 * @param THAT - The point to subtract from this point
 */
inline const Point Point::operator-(const Point& THAT) const {
    return Point(*this) -= THAT;
}

/**
 * Returns the opposite of this point as a new Point.
 */
inline const Point Point::operator-(void) const {
    return Point(-this->x_, -this->y_);
}


/**
 * Returns a new point which has this point's
 * coordinates scaled by the number given as a
 * parameter.
 * 
 * @param D - The number by which to scale this point
 */
inline const Point Point::operator*(const double D) const {
    return Point(this->x_ * D, this->y_ * D);
}

/**
 * Returns a new point which has this point's
 * coordinates divided by the number given as a
 * parameter.
 * 
 * @param D - The number by which to divide this
 *            point's coordinates
 */
inline const Point Point::operator/(const double D) const {
    return Point(this->x_ / D, this->y_ / D);
}


/**
 * Tests whether this point is equal to the point
 * given as a parameter, in the sense that their
 * respective coordinates are all equal.
 * 
 * @param THAT - The point to compare to this point
 */
inline bool Point::operator==(const Point& THAT) const {
    return (this->x_ == THAT.x()) && (this->y_ == THAT.y());
}

/**
 * Tests whether this point is different from the point
 * given as a parameter, in the sense that at least one
 * of their respective coordinates are different.
 * 
 * @param THAT - The point to compare to this point
 */
inline bool Point::operator!=(const Point& THAT) const {
    return !(*this == THAT);
}

#endif // _POINT_H_
