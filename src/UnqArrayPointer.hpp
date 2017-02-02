
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Class
    UnqArrayPointer
 
Description
    Unique pointer class for arrays
 
SourceFiles
    UnqArrayPointer.ipp

\************************************************************************/

#ifndef UNQARRAYPOINTER_H
#define UNQARRAYPOINTER_H

// GLEW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>

template <class T>
class UnqArrayPointer
{
private:
    T* pointer_;
    GLuint size_;

public:
    //constructor
    UnqArrayPointer();
    UnqArrayPointer(const GLuint size);
    UnqArrayPointer(T* pointer, const GLuint size);
    UnqArrayPointer(const UnqArrayPointer& copy); //disable copy constructor

    ~UnqArrayPointer();

    //public functions
    void set(const GLuint size);
    void set(T* pointer, const GLuint size);

    //access functions
    T* ptr();
    GLuint size();

    //operators
    UnqArrayPointer<T>& operator=(const UnqArrayPointer& operand); //disable operator=
    UnqArrayPointer<T>& operator=(const T& operand);
    T& operator[](const GLuint i); 
};

#include "UnqArrayPointer.ipp"

#endif
