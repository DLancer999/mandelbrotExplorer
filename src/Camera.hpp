
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.   
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Class
    Camera
 
Description
    2D camera that controls which part of the mandelbrot is going
    to be rendered on screen.
 
SourceFiles
    Camera.cpp

\************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

// GLEW-GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Timer.hpp"

class Camera
{
private:
    //private members
    GLdouble diameter_;
    GLdouble centerX_;
	GLdouble centerY_;
    GLdouble minX_;
	GLdouble minY_;
    Timer timer_;

public:
    //public enumarator
    enum Action
    {
        MOVING_MOUSE,
        MOVING,
        MOVELEFT,
        MOVERIGHT,
        MOVEUP,
        MOVEDOWN,
        ZOOMIN,
        ZOOMOUT
    };

    //static members
    static GLboolean moveCamera[8];
    static GLint activeCamMovements;
    //static functions
    static void setCamMovement(Action moveDirection, GLboolean buttonPressed);


    //constructor
    Camera(); 

    //access functions
    GLdouble radius(){return diameter_*0.5;}
    GLdouble diameter(){return diameter_;}
    GLdouble centerX(){return centerX_;}
	GLdouble centerY(){return centerY_;}
    GLdouble minX(){return minX_;}
	GLdouble minY(){return minY_;}

    //public member functions
    void move(GLdouble dx, GLdouble dy);
    void moveHorizontal(GLdouble dTime, GLboolean posDir);
    void moveVertical(GLdouble dTime, GLboolean posDir);
    void zoom(GLdouble dTime, GLboolean posDir);
    void zoom(GLdouble zoomPerc);
    void update(GLFWwindow*);
};

#endif
