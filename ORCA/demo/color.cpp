=/**
 * File  : color.cpp
 * Author: Raja Soufi
 * 
 * Implementation of the Color class defined
 * in color.h.
 */

// Include header file
#include "color.h"

/*
    Predefined colors
*/

const Color Color::BLACK  (0.0, 0.0, 0.0);
const Color Color::WHITE  (1.0, 1.0, 1.0);

const Color Color::RED    (1.0, 0.0, 0.0);
const Color Color::GREEN  (0.0, 1.0, 0.0);
const Color Color::BLUE   (0.0, 0.0, 1.0);

const Color Color::YELLOW (1.0, 1.0, 0.0);
const Color Color::MAGENTA(1.0, 0.0, 1.0);
const Color Color::CYAN   (0.0, 1.0, 1.0);

/*
    Constructors
*/

/**
 * Constructs a color with its RGBA components set
 * to zero. The constructed color is quivalent to a
 * black, fully transparent color.
 */
Color::Color(void) : red_(0.0), green_(0.0), blue_(0.0), alpha_(0.0) {}

/**
 * Constructs a color with its RGBA components set to
 * the values given as parameters.
 * In case parameter RGB is set to true (default value)
 * then the components are set directly, otherwise
 * they are interpreted as HSV values and converted to
 * RGB before they are stored.
 * 
 * @param RED_HUE          - The red/hue component to use with the
 *                           new color, depending on the RGB value
 * @param GREEN_SATURATION - The green/saturation component to use with
 *                           the new color, depending on the RGB value
 * @param BLUE_VALUE       - The blue/value component to use with the
 *                           new color, depending on the RGB value
 * @param ALPHA            - The alpha component to use with the new
 *                           color
 * @param RGB              - The interpretation mode of the first
 *                           three parameters
 */
Color::Color(const double RED_HUE, const double GREEN_SATURATION, const double BLUE_VALUE,
    const double ALPHA/* = 1.0 */, const bool RGB/* = true */) : alpha_(CONSTRAIN_VALUE(ALPHA, 0.0, 1.0))
{
    
    double redHue          = CONSTRAIN_VALUE(RED_HUE         , 0.0, 1.0);
    double greenSaturation = CONSTRAIN_VALUE(GREEN_SATURATION, 0.0, 1.0);
    double blueValue       = CONSTRAIN_VALUE(BLUE_VALUE      , 0.0, 1.0);
    
    if (RGB) {
        this->red_   = redHue;
        this->green_ = greenSaturation;
        this->blue_  = blueValue;
    } else {
        
        double multipleOfSix = redHue * 6;
        
        double c = greenSaturation * blueValue;
        double x = c * (1 - std::abs(trueMod(multipleOfSix, 2) - 1));
        double m = blueValue - c;
        
        if (multipleOfSix < 2) {
            this->blue_ = 0.0;
            if (multipleOfSix < 1) {
                this->red_   = c;
                this->green_ = x;
            } else {
                this->red_   = x;
                this->green_ = c;
            }
        } else if (multipleOfSix < 4) {
            this->red_ = 0.0;
            if (multipleOfSix < 3) {
                this->green_ = c;
                this->blue_  = x;
            } else {
                this->green_ = x;
                this->blue_  = c;
            }
        } else {
            this->green_ = 0.0;
            if (multipleOfSix < 5) {
                this->red_  = x;
                this->blue_ = c;
            } else {
                this->red_  = c;
                this->blue_ = x;
            }
        }
        
        this->red_   += m;
        this->green_ += m;
        this->blue_  += m;
        
    }
    
}
