
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Class
    Timer
 
Description
    Class to keep track of time
 
\************************************************************************/

#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

// GLEW-GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Timer
{
public:
    //public members
    GLdouble startTime_; // used to count time inside function
    GLdouble endTime_; // used to count time between different frames

    //constructor
    Timer():
    startTime_(0.0),
    endTime_(0.0)
    {} 

    //public functions
    void      start() {startTime_ = glfwGetTime();}
    void      end()   {endTime_   = glfwGetTime();} 
    GLdouble  startTime() {return startTime_;} 
    GLdouble  endTime()   {return endTime_;}
    GLdouble  time()      {return glfwGetTime();}
    GLdouble  dt()        {return (endTime_-startTime_);}
    GLdouble  dtNow()     {return (glfwGetTime()-startTime_);}
};

#endif
