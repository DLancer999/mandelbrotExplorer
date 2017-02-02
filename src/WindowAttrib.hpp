
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Class
    WidndowAttrib
 
Description
    Parameters for the current window and global functions relative to it
 
SourceFiles
    WindowAttrib.cpp

\************************************************************************/

#ifndef WINDOWATTRIB_H
#define WINDOWATTRIB_H

// GLEW-GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Fractal2D.hpp"

struct WindowAttrib
{
    static GLboolean RESIZED;
    static GLint     WIDTH;
    static GLint     HEIGHT;
    static std::string NAME;
};

void windowResize_callback(GLFWwindow* window, int width, int height);
void framebufferResize_callback(GLFWwindow* window, int width, int height);
void resizedWindow(GLFWwindow* , Fractal2D&);

#endif
