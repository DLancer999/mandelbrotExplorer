
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Description
    lonely global functions placed here... they had to be somewhere...
 
SourceFiles
    globalFunctions.cpp

\************************************************************************/

#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

// GLEW-GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//other includes

void showControls();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

#endif

