
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

\************************************************************************/

#include "Camera.hpp"
#include "WindowAttrib.hpp"
#include "Mouse.hpp"

//static member initialization
GLboolean Camera::moveCamera[8] = {false, false, false, false, false, false, false, false};
GLint Camera::activeCamMovements = 0;

//********************************************************************************
void Camera::setCamMovement(Action moveDirection, GLboolean buttonPressed)
//********************************************************************************
{
    if (buttonPressed)
    {
        moveCamera[Camera::MOVING] = true;
        moveCamera[moveDirection] = true;
        activeCamMovements += 1;
    }
    else
    {
        moveCamera[moveDirection] = false;
        activeCamMovements -= 1;
        if (activeCamMovements == 0) moveCamera[Camera::MOVING] = false;
    }
}    

//Constructor
//********************************************************************************
Camera::Camera():
//********************************************************************************
diameter_(3.0),
centerX_(-0.5),
centerY_(0.0),
minX_(centerX_-diameter_*0.5),
minY_(centerY_-diameter_*0.5),
timer_()
{
}

//********************************************************************************
void Camera::move(GLdouble dx, GLdouble dy)
//********************************************************************************
{
    //reverse sign due to cursor orientation
    centerX_ -= dx;
    minX_    -= dx;
    centerY_ += dy;
    minY_    += dy;
}

//********************************************************************************
void Camera::moveHorizontal(GLdouble dTime, GLboolean posDir)
//********************************************************************************
{
    GLdouble sign = posDir ? 1.0 : -1.0; 
    GLdouble movement = diameter_*sign*dTime*0.25;
    centerX_ += movement;
    minX_    += movement;
}

//********************************************************************************
void Camera::moveVertical(GLdouble dTime, GLboolean posDir)
//********************************************************************************
{
    GLdouble sign = posDir ? 1.0 : -1.0; 
    GLdouble movement = diameter_*sign*dTime*0.25;
    centerY_ += movement;
    minY_    += movement;
}

//********************************************************************************
void Camera::zoom(GLdouble dTime, GLboolean posDir)
//********************************************************************************
{
    GLdouble sign = posDir ? 1.01 : -1.01; 
    diameter_ *= (1.0+sign*dTime);
    minX_    = centerX_-0.5*diameter_;
    minY_    = centerY_-0.5*diameter_;
}

//********************************************************************************
void Camera::zoom(GLdouble zoomPerc)
//********************************************************************************
{
    diameter_ *= (1.0-zoomPerc);
    minX_    = centerX_-0.5*diameter_;
    minY_    = centerY_-0.5*diameter_;
}


//********************************************************************************
void Camera::update(GLFWwindow* window)
//********************************************************************************
{
    GLdouble dTime = timer_.dtNow();
    timer_.start();

    if (moveCamera[Camera::MOVING_MOUSE])
    {
            GLdouble xPosNow, yPosNow;
            GLint width = WindowAttrib::WIDTH; 
            GLint height= WindowAttrib::HEIGHT;
            glfwGetCursorPos(window, &xPosNow, &yPosNow);
            GLdouble dx = xPosNow - Mouse::xPos;
            GLdouble dy = yPosNow - Mouse::yPos;

            if (dx*dx<0.1 && dy*dy <0.1) return;

            if (Mouse::buttonState[GLFW_MOUSE_BUTTON_1]) 
            {
                if (width>height)
                {
                    GLdouble dwidth = 1./GLdouble(width);
                    dx*= dwidth*diameter_;
                    dy*= dwidth*diameter_;
                }
                else 
                {
                    GLdouble dheight = 1./GLdouble(height);
                    dx*= dheight*diameter_;
                    dy*= dheight*diameter_;
                }
                move(dx,dy);
            }
            else if (Mouse::buttonState[GLFW_MOUSE_BUTTON_2]) 
            {
                if (width>height)
                {
                    dy*= 1./GLdouble(width);
                }
                else 
                {
                    dy*= 1./GLdouble(height);
                }
                zoom(dy);
            }


            Mouse::xPos = xPosNow;
            Mouse::yPos = yPosNow;
    }
    else if (moveCamera[Camera::MOVING])   
    {
        if ( moveCamera[Camera::MOVELEFT])  moveHorizontal(dTime, false);
        if ( moveCamera[Camera::MOVERIGHT]) moveHorizontal(dTime, true);
        if ( moveCamera[Camera::MOVEUP])    moveVertical(dTime, true);
        if ( moveCamera[Camera::MOVEDOWN])  moveVertical(dTime, false);
        if ( moveCamera[Camera::ZOOMIN])    zoom(dTime, true);
        if ( moveCamera[Camera::ZOOMOUT])   zoom(dTime, false);
    }
}
