/**
 * File  : exceptions.h
 * Author: Raja Soufi
 * 
 * Class definitions of useful exceptions.
 */

// Include guard
#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

// Inclusions
#include <exception>

/*
    Line exceptions
*/

// Class definition of LinesParallelException
class LinesParallelException : public std::exception {
    
    public:
    
    // what function
    const char* what(void) const throw();
    
};

// Class definition of LineVerticalException
class LineVerticalException : public std::exception {
    
    public:
    
    // what function
    const char* what(void) const throw();
    
};

// Class definition of LineHorizontalException
class LineHorizontalException : public std::exception {
    
    public:
    
    // what function
    const char* what(void) const throw();
    
};

/*
    ORCA exception
*/

// Class definition of LinearProgramInfeasibleException
class LinearProgramInfeasibleException : public std::exception {
    
    public:
    
    // what function
    const char* what() const throw();
    
};

#endif // _EXCEPTIONS_H_
