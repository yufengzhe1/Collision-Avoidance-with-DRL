/**
 * File  : line.h
 * Author: Raja Soufi
 * 
 * Class definition of a line in 2D space:
 * 
 *     ################################
 *     #  y = slope * x + yIntercept  #
 *     ################################
 * 
 * In case of a vertical line, slope is set to
 * std::numeric_limits<double>::infinity().
 * 
 * A line also has a yIntercept and xIntercept that
 * are set to 0.0 in cases where they are not defined
 * (vertical line or horizontal line respectively).
 * Since a line's yIntercept and xIntercept can still
 * be valid and equal to 0.0, one should first test
 * whether a line is vertical/horizontal before in
 * order to determine whether these variables are
 * valid.
 */

// Include guard
#ifndef _LINE_H_
#define _LINE_H_

// Inclusions
#include "../utilities/exceptions.h"
#include "../utilities/utilities.h"

#include "point.h"

// Forward-declarations
class Point;

// Class definition
class Line {
    
    private:
    
    // Attributes
    double slope_, yIntercept_, xIntercept_;
    
    public:
    
    // Constructors
    Line(void);
    Line(const double SLOPE, const double INTERCEPT);
    Line(const double X_ANGLE);
    Line(const Point& P1, const Point& P2);
    Line(const Point& P);
    Line(const Line& THAT, const Point& P);
    Line(const Line& THAT);
    
    // Destructor
    ~Line(void);
    
    // Getters
    inline double slope(void) const;
    inline double yIntercept(void) const;
    inline double xIntercept(void) const;
    
    // Other methods
    inline double xAngle(void) const;
    
    inline bool isVertical(void) const;
    inline bool isHorizontal(void) const;
    bool contains(const Point& P) const;
    
    inline Line rotated(const double ANGLE) const;
    
    Point intersect(const Line& THAT) const;
    Point getPointAtX(const double X) const;
    Point getPointAtY(const double Y) const;
    
    // Operators
    inline bool operator==(const Line& THAT) const;
    inline bool operator!=(const Line& THAT) const;
    inline bool operator||(const Line& THAT) const;
    
};

/*
    Getters
*/

/**
 * Returns the slope of this line.
 */
inline double Line::slope(void) const {
    return this->slope_;
}

/**
 * Returns the y-intercept of this line.
 * Returns 0.0 when this line is vertical.
 */
inline double Line::yIntercept(void) const {
    return this->yIntercept_;
}

/**
 * Returns the y-intercept of this line.
 * Returns 0.0 when this line is vertical.
 */
inline double Line::xIntercept(void) const {
    return this->xIntercept_;
}

/*
    Other methods
*/

/**
 * Returns the angle that this line makes
 * with the x-axis.
 */
inline double Line::xAngle(void) const {
    return trueMod(atan(this->slope_), M_PI);
}


/**
 * Tests whether this line is vertical.
 */
inline bool Line::isVertical(void) const {
    return this->slope_ == DOUBLE_INFINITY;
}

/**
 * Tests whether this line is horizontal.
 */
inline bool Line::isHorizontal(void) const {
    return this->slope_ == 0;
}


/**
 * Returns a new line which is equivalent to this
 * line rotated by the angle given as a parameter.
 * 
 * @param ANGLE - The angle by which to rotate this
 *                line
 */
inline Line Line::rotated(const double ANGLE) const {
    return Line(this->xAngle() + ANGLE);
}

/*
    Operators
*/

/**
 * Tests whether this line is equal to the line
 * given as a parameter, in the sense that their
 * respective slopes and intercepts are equal.
 * 
 * @param THAT - The line to compare to this line
 */
inline bool Line::operator==(const Line& THAT) const {
    return (this->slope_ == THAT.slope()) &&
        (((this->slope_ == DOUBLE_INFINITY) && (this->xIntercept_ == THAT.xIntercept())) ||
        (this->yIntercept_ == THAT.yIntercept()));
}

/**
 * Tests whether this line is different from the line
 * given as a parameter, in the sense that either
 * their slopes are different or one of their respective
 * intercepts are different.
 * 
 * @param THAT - The line to compare to this line
 */
inline bool Line::operator!=(const Line& THAT) const {
    return !(*this == THAT);
}

/**
 * Tests whether this line is parallel to the line
 * given as a parameter.
 * 
 * @param THAT - The line to test with this line
 */
inline bool Line::operator||(const Line& THAT) const {
    return this->slope_ == THAT.slope();
}

#endif // _LINE_H_
