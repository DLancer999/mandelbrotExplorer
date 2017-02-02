
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

\************************************************************************/

#include "Mouse.hpp"
#include "Camera.hpp"

//static member initialization
GLboolean Mouse::buttonState[5] = {false, false, false, false, false};
GLdouble  Mouse::xPos = 0.0;
GLdouble  Mouse::yPos = 0.0;

void mouseButton_callback(GLFWwindow* window, int button, int action, int mode)
{
    switch (button)
    {
        case GLFW_MOUSE_BUTTON_1:
            if (action == GLFW_PRESS) 
            {
                Mouse::buttonState[GLFW_MOUSE_BUTTON_1] = true;
                Camera::moveCamera[Camera::MOVING_MOUSE]=true;
                glfwGetCursorPos(window, &Mouse::xPos, &Mouse::yPos);
            }
            else if (action == GLFW_RELEASE) 
            {
                Mouse::buttonState[GLFW_MOUSE_BUTTON_1] = false;
                Camera::moveCamera[Camera::MOVING_MOUSE]=false;
            }
            break;
        case GLFW_MOUSE_BUTTON_2:
            if (action == GLFW_PRESS) 
            {
                Mouse::buttonState[GLFW_MOUSE_BUTTON_2] = true;
                Camera::moveCamera[Camera::MOVING_MOUSE]=true;
                glfwGetCursorPos(window, &Mouse::xPos, &Mouse::yPos);
            }
            else if (action == GLFW_RELEASE) 
            {
                Mouse::buttonState[GLFW_MOUSE_BUTTON_2] = false;
                Camera::moveCamera[Camera::MOVING_MOUSE]=false;
            }
            break;
        default:{/*do nothing*/}
    }
}

