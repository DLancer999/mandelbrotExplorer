
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Class
    FractalSettings
 
Description
    Parameters for the fractal rendering
 
SourceFiles
    FractalSettings.cpp

\************************************************************************/

#ifndef FRACTALSETTINGS_H
#define FRACTALSETTINGS_H

// GLEW-GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class FractalSettings
{
public:
    //public enumerators
    enum Action
    {
        INCRACCURACY,
        DECRACCURACY,
        SWITCH_PLATFORM
    };
    enum RenderType
    {
        RENDER_CPU,
        RENDER_SHADERDOUBLE,
        RENDER_SHADERFLOAT
    }; 

    //static members
    static GLboolean fracActions[3];
    static GLuint accuracy;
    static RenderType renderPlatform;

    //static members functions
    static void update();
};

#endif
