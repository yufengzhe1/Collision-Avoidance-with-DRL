/**
 * File  : color.h
 * Author: Raja Soufi
 * 
 * Class definition of an RGBA Color.
 */

// Include guard

#ifndef _COLOR_H_
#define _COLOR_H_

// Inclusions
#include <cmath>

#include "../utilities/utilities.h"

// Class definition
class Color {
    
    private:
    
    // Attributes
    double red_, green_, blue_, alpha_;
    
    public:
    
    // Predefined colors
    static const Color BLACK;
    static const Color WHITE;
    
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    
    static const Color YELLOW;
    static const Color MAGENTA;
    static const Color CYAN;
    
    // Constructors
    Color(void);
    Color(const double RED_HUE, const double GREEN_SATURATION, const double BLUE_VALUE,
        const double ALPHA = 1.0, const bool RGB = true);
    
    // Getters
    inline double red  (void) const;
    inline double green(void) const;
    inline double blue (void) const;
    inline double alpha(void) const;
    
    // Operators
    inline bool operator==(const Color& THAT) const;
    inline bool operator!=(const Color& THAT) const;
    
};

/*
    Getters
*/

/**
 * Returns the red component of this color.
 */
double Color::red(void) const {
    return this->red_;
}

/**
 * Returns the green component of this color.
 */
double Color::green(void) const {
    return this->green_;
}

/**
 * Returns the blue component of this color.
 */
double Color::blue(void) const {
    return this->blue_;
}

/**
 * Returns the alpha component of this color.
 */
double Color::alpha(void) const {
    return this->alpha_;
}

/*
    Operators
*/

/**
 * Tests whether this color is equal to the color
 * given as a parameter, in the sense that all of
 * their respective components are equal.
 * 
 * @param THAT - The color to compare to this color
 */
bool Color::operator==(const Color& THAT) const {
    return (this->red_ == THAT.red()) && (this->green_ == THAT.green()) && (this->blue_ == THAT.blue()) && (this->alpha_ == THAT.alpha());
}

/**
 * Tests whether this color is different from the
 * color given as a parameter, in the sense that at
 * least one of their respective components are
 * different.
 * 
 * @param THAT - The color to compare to this color
 */
bool Color::operator!=(const Color& THAT) const {
    return !(*this == THAT);
}

#endif // _COLOR_H_
