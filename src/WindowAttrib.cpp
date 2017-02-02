
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

\************************************************************************/

#include "WindowAttrib.hpp"

//initialize static members

GLboolean WindowAttrib::RESIZED = false;
GLint     WindowAttrib::WIDTH   = 800;
GLint     WindowAttrib::HEIGHT  = 600;
std::string WindowAttrib::NAME  = "Beautiful Fractal";

void windowResize_callback(GLFWwindow* window, int width, int height)
{
    WindowAttrib::RESIZED = true;
}

void framebufferResize_callback(GLFWwindow* window, int width, int height)
{
    WindowAttrib::RESIZED = true;
}

void resizedWindow(GLFWwindow* window, Fractal2D& fractal)
{
    static GLdouble lastCallTime = 0.0;
    if (!WindowAttrib::RESIZED) return;
    GLdouble callTime = glfwGetTime();
    if (callTime - lastCallTime < 0.1) return;

    lastCallTime = callTime;
    WindowAttrib::RESIZED = false;

    //read new window size
    glfwGetWindowSize(window, &WindowAttrib::WIDTH,  &WindowAttrib::HEIGHT);

    //update framebuffer size
    glViewport(0, 0, WindowAttrib::WIDTH, WindowAttrib::HEIGHT);

    //resize image
    fractal.resizeToWindow(WindowAttrib::WIDTH, WindowAttrib::HEIGHT);
}
