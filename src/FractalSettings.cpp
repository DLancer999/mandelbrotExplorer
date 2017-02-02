
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

\************************************************************************/

#include "FractalSettings.hpp"
#include <iostream>

//static member initialization
GLboolean                   FractalSettings::fracActions[3] = {false, false, false};
GLuint                      FractalSettings::accuracy = 20;
FractalSettings::RenderType FractalSettings::renderPlatform = FractalSettings::RENDER_CPU;

//********************************************************************************
void FractalSettings::update()
//********************************************************************************
{
    if (fracActions[INCRACCURACY])
    {
        accuracy<<=1;
        if (!accuracy) accuracy++;
        std::cout<<"max Escape time = "<<accuracy<<std::endl;
        fracActions[INCRACCURACY]=false;
    }
    if (fracActions[DECRACCURACY])
    {
        accuracy>>=1;
        //accuracy-=1;
        std::cout<<"max Escape time = "<<accuracy<<std::endl;
        fracActions[DECRACCURACY]=false;
    }
    if (fracActions[SWITCH_PLATFORM])
    {
        if      (renderPlatform == RENDER_CPU)          
        {
            renderPlatform = RENDER_SHADERDOUBLE;
            std::cout<<"Changed Rendering Platform to Shader - double precision"<<std::endl;
        }
        else if (renderPlatform == RENDER_SHADERDOUBLE) 
        {
            renderPlatform = RENDER_SHADERFLOAT;
            std::cout<<"Changed Rendering Platform to Shader - single precision"<<std::endl;
        }
        else                
        {
            renderPlatform = RENDER_CPU;
            std::cout<<"Changed Rendering Platform to CPU"<<std::endl;
        }
        fracActions[SWITCH_PLATFORM]=false;
    }
}
