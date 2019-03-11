/**
 * File  : halfPlane.h
 * Author: Raja Soufi
 * 
 * Class definition of a half-plane in 2D space.
 * A half-plane is defined by a line, the half-plane
 * itself being one of the two halves of the 2D plane
 * split by that line. Which particular half is
 * represented by this half-plane is specified by the
 * normal vector. Points on the bounding line are
 * considered to be included in the area of the
 * half-plane.
 */

// Include guard
#ifndef _HALF_PLANE_H_
#define _HALF_PLANE_H_

// Inclusions
#include "../utilities/utilities.h"

#include "line.h"
#include "point.h"
#include "vector.h"

// Class definition
class HalfPlane {
    
    private:
    
    // Attributes
    Point normalPosition_;
    Vector normal_;
    Line boundingLine_;
    
    public:
    
    // Constructors
    HalfPlane(void);
    HalfPlane(const Point& NORMAL_POSITION, const Vector& NORMAL);
    HalfPlane(const HalfPlane& THAT);
    
    // Destructor
    ~HalfPlane(void);
    
    // Getters
    inline const Point& normalPosition(void) const;
    inline const Vector& normal(void) const;
    inline const Line& boundingLine(void) const;
    
    // Other methods
    inline bool contains(const Point& P) const;
    
    // Operators
    inline bool operator==(const HalfPlane& THAT) const;
    inline bool operator!=(const HalfPlane& THAT) const;
    
};

/*
    Getters
*/

/**
 * Returns the starting point of the normal of this
 * half-plane.
 */
inline const Point& HalfPlane::normalPosition(void) const {
    return this->normalPosition_;
}

/**
 * Returns the normal of this half-plane.
 */
inline const Vector& HalfPlane::normal(void) const {
    return this->normal_;
}

/**
 * Returns the bounding line of this half-plane.
 */
inline const Line& HalfPlane::boundingLine(void) const {
    return this->boundingLine_;
}

/*
    Other methods
*/

/**
 * Tests whether this half-plane contains the point
 * given as a parameter.
 * 
 * @param P - The point to test with this half-plane
 */
inline bool HalfPlane::contains(const Point& P) const {
    return P.from(this->normalPosition_) * this->normal_ >= 0;
}

/*
    Operators
*/

/**
 * Tests whether this half-plane is equal to the
 * half-plane given as a parameter, in the sense that
 * they represent the exact same area.
 * 
 * @param THAT - The half-plane to compare to this
 *               half-plane
 */
inline bool HalfPlane::operator==(const HalfPlane& THAT) const {
    return this->boundingLine_ == THAT.boundingLine();
}

/**
 * Tests whether this half-plane is different from the
 * half-plane given as a parameter, in the sense that
 * the areas they represent are not exactly the same.
 * 
 * @param THAT - The half-plane to compare to this
 *               half-plane
 */
inline bool HalfPlane::operator!=(const HalfPlane& THAT) const {
    return !(*this == THAT);
}

#endif // _HALF_PLANE_H_
