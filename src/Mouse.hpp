
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Class
    Mouse
 
Description
    Class to handle mouse input and global functions relative to it
 
SourceFiles
    Mouse.cpp

\************************************************************************/

#ifndef MOUSE_H
#define MOUSE_H

// GLEW-GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Mouse
{
    static GLdouble xPos;
    static GLdouble yPos;
    static GLboolean buttonState[5];
};

void mouseButton_callback(GLFWwindow* window, int button, int action, int mode);

#endif
