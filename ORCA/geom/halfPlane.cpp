/**
 * File  : halfPlane.cpp
 * Author: Raja Soufi
 * 
 * Implementation of the HalfPlane class defined
 * in halfPlane.h.
 */

// Include header file
#include "halfPlane.h"

/*
    Constructors
*/

/**
 * Constructs a half-plane equivalent to the plane
 * defined by the inequation x > 0.
 */
HalfPlane::HalfPlane(void) : normalPosition_(), normal_(0, 1), boundingLine_() {}

/**
 * Constructs a half-plane with a normal position and
 * normal equal to the ones given as parameters.
 * 
 * @param NORMAL_POSITION - The position of the normal of the
 *                          new half-plane
 * @param NORMAL          - The normal of the new half-plane
 */
HalfPlane::HalfPlane(const Point& NORMAL_POSITION, const Vector& NORMAL) : normalPosition_(NORMAL_POSITION) {
    this->normal_ = (NORMAL.norm() == 0) ? Vector(0, 1) : NORMAL;
    double slope, intercept;
    // Vertical line
    if (this->normal_.y() == 0) {
        slope = DOUBLE_INFINITY;
        intercept = NORMAL_POSITION.x();
    }
    // Non-vertical line
    else {
        slope = -this->normal_.x() / this->normal_.y();
        intercept = NORMAL_POSITION.y() - NORMAL_POSITION.x() * slope;
    }
    this->boundingLine_ = Line(slope, intercept);
}

/**
 * Constructs a half-plane equal to the half-plane
 * given as a parameter.
 * 
 * @param THAT - The half-plane to be used to
 *               construct the new half-plane
 */
HalfPlane::HalfPlane(const HalfPlane& THAT) :
    normalPosition_(THAT.normalPosition()), normal_(THAT.normal()), boundingLine_(THAT.boundingLine()) {}

/*
    Destructor
*/

/**
 * Destroys this half-plane.
 */
HalfPlane::~HalfPlane(void) {}
