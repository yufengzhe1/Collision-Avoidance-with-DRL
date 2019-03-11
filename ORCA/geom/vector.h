/**
 * File  : vector.h
 * Author: Raja Soufi
 * 
 * Class definition of a vector in 2D space:
 * 
 *              #############
 *              #  V(x, y)  #
 *              #############
 */

// Include guard
#ifndef _VECTOR_H_
#define _VECTOR_H_

// Inclusions
#include <cmath>

#include "../utilities/utilities.h"

#include "point.h"

// Forward-declarations
class Point;

// Class definition
class Vector {
    
    private:
    
    // Attributes
    double x_, y_;
    
    public:
    
    // Constructors
    Vector(void);
    Vector(const double X, const double Y);
    Vector(const double X_ANGLE);
    Vector(const Point& P);
    Vector(const Vector& THAT);
    
    // Destructor
    ~Vector(void);
    
    // Getters
    inline double x(void) const;
    inline double y(void) const;
    
    // Other methods
    inline double norm(void) const;
    inline double xAngle(void) const;
    
    const Vector& normalize(const double NEW_NORM = 1.0);
    const Vector& limitNorm(const double MAX_NORM = 1.0);
    const Vector& limitNorm(const Vector& THAT);
    inline Vector projectionOnto(const Vector& THAT) const;
    inline Vector rotated(const double ANGLE) const;
    inline double angleFrom(const Vector& THAT) const;
    
    // Operators
    inline const Vector operator+(const Vector& THAT) const;
    inline const Vector operator-(const Vector& THAT) const;
    inline double operator*(const Vector& THAT) const;
    inline const Vector operator-(void) const;
    
    inline const Vector operator*(const double D) const;
    inline const Vector operator/(const double D) const;
    
    Vector& operator=(const Vector& THAT);
    Vector& operator+=(const Vector& THAT);
    Vector& operator-=(const Vector& THAT);
    
    inline bool operator==(const Vector& THAT) const;
    inline bool operator!=(const Vector& THAT) const;
    
    inline bool operator==(const double D) const;
    inline bool operator!=(const double D) const;
    
};

/*
    Getters
*/

/**
 * Returns the x-coordinate of this vector.
 */
inline double Vector::x(void) const {
    return this->x_;
}

/**
 * Returns the y-coordinate of this vector.
 */
inline double Vector::y(void) const {
    return this->y_;
}

/*
    Other methods
*/

/**
 * Returns the norm of this vector.
 */
inline double Vector::norm(void) const {
    return sqrt(*this * *this);
}

/**
 * Returns the angle, in radians, that this vector
 * makes with the x-axis.
 */
inline double Vector::xAngle(void) const {
    return (this->norm() == 0) ? 0 :
        (this->x_ == 0) ? M_PI_2 + ((this->y_ < 0) ? M_PI : 0) :
        trueMod(atan(this->y_ / this->x_) + ((this->x_ < 0) ? M_PI : 0), 2 * M_PI);
}


/**
 * Returns the projection of this vector onto the
 * vector given as a parameter.
 * 
 * @param THAT - The vector to project this vector
 *               onto
 */
inline Vector Vector::projectionOnto(const Vector& THAT) const {
    return Vector(THAT).normalize(std::abs(*this * THAT) / THAT.norm());
}

/**
 * Returns a new vector which is equivalent to this
 * vector rotated by the angle given as a parameter.
 * 
 * @param ANGLE - The angle by which to rotate this
 *                vector
 */
inline Vector Vector::rotated(const double ANGLE) const {
    return Vector(this->xAngle() + ANGLE).normalize(this->norm());
}

/**
 * Returns the angle, in radians, that this vector
 * makes with the vector given as a parameter.
 * 
 * @param THAT - The vector to be considered when
 *               calculating the angle
 */
inline double Vector::angleFrom(const Vector& THAT) const {
    return this->xAngle() - THAT.xAngle();
}

/*
    Operators
*/

/**
 * Returns a new vector which is the sum of this
 * vector and the vector given as a parameter.
 * 
 * @param THAT - The vector to add to this vector
 */
inline const Vector Vector::operator+(const Vector& THAT) const {
    return Vector(*this) += THAT;
}

/**
 * Returns a new vector which is the difference
 * between this vector and the vector given as a
 * parameter.
 * 
 * @param THAT - The vector to subtract from this
 *               vector
 */
inline const Vector Vector::operator-(const Vector& THAT) const {
    return Vector(*this) -= THAT;
}

/**
 * Returns the dot product of this vector and the
 * vector given as a parameter.
 * 
 * @param THAT - The second operand of the dot product
 */
inline double Vector::operator*(const Vector& THAT) const {
    return this->x_ * THAT.x() + this->y_ * THAT.y();
}

/**
 * Returns the opposite of this vector as a new vector.
 */
inline const Vector Vector::operator-(void) const {
    return Vector(-this->x_, -this->y_);
}


/**
 * Returns a new vector which has this vector's
 * coordinates scaled by the number given as a
 * parameter.
 * 
 * @param D - The number by which to scale this vector
 */
inline const Vector Vector::operator*(const double D) const {
    return Vector(this->x_ * D, this->y_ * D);
}

/**
 * Returns a new vector which has this vector's
 * coordinates divided by the number given as a
 * parameter.
 * 
 * @param D - The number by which to divide this
 *            vector's coordinates
 */
inline const Vector Vector::operator/(const double D) const {
    return Vector(this->x_ / D, this->y_ / D);
}


/**
 * Tests whether this vector is equal to the vector
 * given as a parameter, in the sense that their
 * respective coordinates are all equal.
 * 
 * @param THAT - The vector to compare to this vector
 */
inline bool Vector::operator==(const Vector& THAT) const {
    return (this->x_ == THAT.x()) && (this->y_ == THAT.y());
}

/**
 * Tests whether this vector is different from the vector
 * given as a parameter, in the sense that at least one
 * of their respective coordinates are different.
 * 
 * @param THAT - The vector to compare to this vector
 */
inline bool Vector::operator!=(const Vector& THAT) const {
    return !(*this == THAT);
}

/**
 * Tests whether this vector's norm is equal to the
 * number given as a parameter.
 * 
 * @param D - The number to compare to this vector's
 *            norm
 */
inline bool Vector::operator==(const double D) const {
    return this->norm() == D;
}

/**
 * Tests whether this vector's norm is different from
 * the number given as a parameter.
 * 
 * @param D - The number to compare to this vector's
 *            norm
 */
inline bool Vector::operator!=(const double D) const {
    return !(*this == D);
}

#endif // _VECTOR_H_
