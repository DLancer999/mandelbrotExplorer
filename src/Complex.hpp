
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Class
    Complex
 
Description
    very basic complex implementation
    used instead of std::complex due to performance issues with the later
 
\************************************************************************/

#ifndef COMPLEX_H
#define COMPLEX_H

// GLEW - GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <math.h>

//very basic complex implementation
//used instead of std::complex due to performance issues with the later

class Complex
{
protected:
    //protected variables
    GLdouble re_; 
    GLdouble im_;
    
public:
    //constructor
    Complex():re_(0.0),im_(0.0){} 
    Complex(const Complex& copy):re_(copy.re_),im_(copy.im_){} 
    Complex(const GLdouble& re,const GLdouble& im):re_(re),im_(im){} 

    //public member functions
    GLdouble& re() {return re_;}
    GLdouble& im() {return im_;}
    GLdouble mag() {return sqrt(re_*re_ + im_*im_);}
    GLdouble norm(){return (re_*re_ + im_*im_); }

    //operators
    Complex& operator=(const  Complex& operand){re_ = operand.re_; im_ = operand.im_; return *this;}
    Complex& operator+=(const Complex& operand){re_+= operand.re_; im_+= operand.im_; return *this;}
    Complex& operator-=(const Complex& operand){re_-= operand.re_; im_-= operand.im_; return *this;}
     
    Complex& operator*=(const Complex& operand)
    {
        GLdouble tempRe = re_*operand.re_ - im_*operand.im_;
        GLdouble tempIm = re_*operand.im_ + im_*operand.re_;
        re_ = tempRe;
        im_ = tempIm;
        return *this;
    }

    Complex  operator+(const  Complex& other){ return (Complex(*this)+=other); }
    Complex  operator-(const  Complex& other){ return (Complex(*this)-=other); }
    Complex  operator*(const  Complex& other){ return (Complex(*this)*=other); }
};

#endif
