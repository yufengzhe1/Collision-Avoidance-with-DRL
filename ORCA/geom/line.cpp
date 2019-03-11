/**
 * File  : line.cpp
 * Author: Raja Soufi
 * 
 * Implementation of the Line class defined
 * in line.h.
 */

// Include header file
#include "line.h"

/*
    Constructors
*/

/**
 * Constructs a line with a zero slope and zero
 * intercepts. The constructed line is equivalent
 * to the x-axis.
 */
Line::Line(void) : slope_(0), yIntercept_(0), xIntercept_(0) {}

/**
 * Constructs a line with a slope equal to the first
 * given parameter. If this first parameter is equal
 * to +/-DOUBLE_INFINITY, then the x-intercept of the
 * new line is set to the second given parameter.
 * Otherwise, the y-intercept is set to the second
 * given parameter and the x-intercept is calculated
 * accordingly.
 * 
 * @param SLOPE     - The slope of the new line
 * @param INTERCEPT - The x-intercept or y-intercept
 *                    of the new line, depending on
 *                    the value of slope
 */
Line::Line(const double SLOPE, const double INTERCEPT) {
    this->slope_ = (SLOPE == -DOUBLE_INFINITY) ? DOUBLE_INFINITY : SLOPE;
    if (this->isVertical()) {
        this->yIntercept_ = 0;
        this->xIntercept_ = INTERCEPT;
    } else {
        this->yIntercept_ = INTERCEPT;
        this->xIntercept_ = this->isHorizontal() ? 0 : -INTERCEPT / SLOPE;
    }
}

/**
 * Constructs a line that makes an angle with the
 * x-axis equal to the number given as a parameter.
 * 
 * @param X_ANGLE - The angle that the new line makes
 *                  with the x-axis
 */
Line::Line(const double X_ANGLE) : yIntercept_(0), xIntercept_(0) {
    double xAngleBound = trueMod(X_ANGLE, M_PI);
    this->slope_ = (xAngleBound == M_PI_2) ? DOUBLE_INFINITY : tan(xAngleBound);
}

/**
 * Constructs a line that goes through the two points
 * given as parameters. If the two points are the
 * same, the new line will have a zero slope.
 * 
 * @param P1 - The first point for the new line
 * @param P2 - The second point for the new line
 */
Line::Line(const Point& P1, const Point& P2) {
    if ((P1.x() == P2.x()) && (P1.y() != P2.y())) {
        this->slope_ = DOUBLE_INFINITY;
        this->yIntercept_ = 0;
        this->xIntercept_ = P1.x();
    } else {
        this->slope_ = (P1 == P2) ? 0 : (P2.y() - P1.y()) / (P2.x() - P1.x());
        this->yIntercept_ = P1.y() - P1.x() * this->slope_;
        this->xIntercept_ = this->isHorizontal() ? 0 : -this->yIntercept_ / this->slope_;
    }
}

/**
 * Constructs a line that goes through the origin
 * and the point given as a parameter.
 * 
 * @param P - The point for the new line
 */
Line::Line(const Point& P) : Line(Point(), P) {}

/**
 * Constructs a line perpendicular to the line given
 * as a parameter and going through the point given
 * as a parameter.
 * 
 * @param THAT - The line perpendicular to the new
 *               line
 * @param P    - The point for the new line
 */
Line::Line(const Line& THAT, const Point& P) {
    if (THAT.isHorizontal()) {
        this->slope_ = DOUBLE_INFINITY;
        this->yIntercept_ = 0;
        this->xIntercept_ = P.x();
    } else {
        this->slope_ = - 1 / THAT.slope();
        this->yIntercept_ = P.y() - P.x() * this->slope_;
        this->xIntercept_ = this->isHorizontal() ? 0 : -this->yIntercept_ / this->slope_;
    }
}

/**
 * Constructs a line with slope and intercepts equal
 * to those of the line given as a parameter.
 * 
 * @param THAT - The line to be used to construct
 *               the new line
 */
Line::Line(const Line& THAT) :
    slope_(THAT.slope()), yIntercept_(THAT.yIntercept()), xIntercept_(THAT.xIntercept()) {}

/*
    Destructor
*/

/**
 * Destroys this line.
 */
Line::~Line(void) {}

/*
    Other methods
*/

/**
 * Tests whether the point given as a parameter is
 * on this line.
 * 
 * @param P - The point to test with this line
 */
bool Line::contains(const Point& P) const {
    return P.y() == this->slope_ * P.x() + this->yIntercept_;
}


/**
 * Returns a new point that is the intersection of
 * this line and the line given as a parameter.
 * In case the two lines are parallel, an exception
 * of type LinesParallelException is thrown.
 * 
 * @param THAT - The line to intersect with this line
 */
Point Line::intersect(const Line& THAT) const {
    // If the two lines are parallel, throw an exception
    if (*this || THAT) {
        throw LinesParallelException();
    }
    // If this line is vertical, use its xIntercept to get
    // the intersection point from the other line
    else if (this->isVertical()) {
        return THAT.getPointAtX(this->xIntercept_);
    }
    // If THAT line is vertical, do exactly as in the previous
    // case but the other way around
    else if (THAT.isVertical()) {
        return this->getPointAtX(THAT.xIntercept());
    }
    // If the two lines are not parallel and neither of them is
    // vertical, compute the x coordinate of their intersection
    // and use it to get the y coordinate from this line
    else {
        return this->getPointAtX((THAT.yIntercept() - this->yIntercept_) / (this->slope_ - THAT.slope()));
    }
}

/**
 * Returns a new point which represents the point on
 * this line with x-coordinate equal to the number
 * given as a parameter.
 * In case this line is vertical, an exception of
 * type LineVerticalException is thrown.
 * 
 * @param X - The x-coordinate of the point to return
 */
Point Line::getPointAtX(const double X) const {
    if (this->isVertical()) {
        throw LineVerticalException();
    } else {
        return Point(X, this->slope_ * X + this->yIntercept_);
    }
}

/**
 * Returns a new point which represents the point on
 * this line with y-coordinate equal to the number
 * given as a parameter.
 * In case this line is horizontal, an exception of
 * type LineHorizontalException is thrown.
 * 
 * @param Y - The y-coordinate of the point to return
 */
Point Line::getPointAtY(const double Y) const {
    if (this->isHorizontal()) {
        throw LineHorizontalException();
    } else {
        return Point(this->isVertical() ? this->xIntercept_ : (Y - this->yIntercept_) / this->slope_, Y);
    }
}
