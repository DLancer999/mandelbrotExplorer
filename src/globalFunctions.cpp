
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

\************************************************************************/

#include <iostream>
#include "globalFunctions.hpp"
#include "Camera.hpp"
#include "FractalSettings.hpp"

void showControls()
{
    std::cout<<std::endl<<std::endl<<" -----> Controls <----"<<std::endl<<std::endl;
    std::cout<<"Navigate around either with {wasd} or mouse (Left  click and drag)"<<std::endl;
    std::cout<<"Zoom in/out with either    {q}-{e} or mouse (Right click and drag vertically)"<<std::endl;
    std::cout<<"Increase/decrease fractal rendering accuracy {[}-{]} (open-close bracket keys)"<<std::endl;
    std::cout<<"Switch between CPU-GPU rendering {p}"<<std::endl;
    std::cout<<"Show controls {h}"<<std::endl<<std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//std::cout << key << "\t" << action <<std::endl ;
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_A:
            if      (action == GLFW_PRESS  ) Camera::setCamMovement(Camera::MOVELEFT,true);
            else if (action == GLFW_RELEASE) Camera::setCamMovement(Camera::MOVELEFT,false);
            break;
        case GLFW_KEY_D:
            if      (action == GLFW_PRESS)   Camera::setCamMovement(Camera::MOVERIGHT,true);
            else if (action == GLFW_RELEASE) Camera::setCamMovement(Camera::MOVERIGHT,false);
            break;
        case GLFW_KEY_W:
            if      (action == GLFW_PRESS)   Camera::setCamMovement(Camera::MOVEUP,true);
            else if (action == GLFW_RELEASE) Camera::setCamMovement(Camera::MOVEUP,false);
            break;
        case GLFW_KEY_S:
            if      (action == GLFW_PRESS)   Camera::setCamMovement(Camera::MOVEDOWN,true);
            else if (action == GLFW_RELEASE) Camera::setCamMovement(Camera::MOVEDOWN,false);
            break;
        case GLFW_KEY_Q:
            if      (action == GLFW_PRESS)   Camera::setCamMovement(Camera::ZOOMIN,true);
            else if (action == GLFW_RELEASE) Camera::setCamMovement(Camera::ZOOMIN,false);
            break;
        case GLFW_KEY_E:
            if      (action == GLFW_PRESS)   Camera::setCamMovement(Camera::ZOOMOUT,true);
            else if (action == GLFW_RELEASE) Camera::setCamMovement(Camera::ZOOMOUT,false);
            break;
        case GLFW_KEY_RIGHT_BRACKET:
            if (action == GLFW_PRESS) 
                FractalSettings::fracActions[FractalSettings::INCRACCURACY]=true;
            break;
        case GLFW_KEY_LEFT_BRACKET:
            if (action == GLFW_PRESS) 
                FractalSettings::fracActions[FractalSettings::DECRACCURACY]=true;
            break;
        case GLFW_KEY_P:
            if (action == GLFW_PRESS) 
                FractalSettings::fracActions[FractalSettings::SWITCH_PLATFORM]=true;
            break;
        case GLFW_KEY_H:
            if (action == GLFW_PRESS) showControls();
            break;
        default:{/*do nothing*/}
    }
}

