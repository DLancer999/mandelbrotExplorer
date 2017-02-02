
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Description
    Main source file of mandelbrotExplorer program. With mandelbrotExplorer 
    one can interactively explore the mandelbrot set in realtime, redering
    either in CPU or in GPU (using openGL compute shaders).

\************************************************************************/

// GLEW GLFW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//other includes
#include <iostream>
#include "Camera.hpp"
#include "Fractal2D.hpp"
#include "globalFunctions.hpp"
#include "WindowAttrib.hpp"
#include "Mouse.hpp"
#include "FractalSettings.hpp"
#include "Timer.hpp"

int main()
{
    std::cout<<"Initializing GLFW"<<std::endl;
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions
    std::cout<<"Creating window"<<std::endl;
	GLFWwindow* window = glfwCreateWindow(WindowAttrib::WIDTH, WindowAttrib::HEIGHT, WindowAttrib::NAME.c_str(), nullptr, nullptr);    
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	// Set the required callback functions
    std::cout<<"Setting callback functions"<<std::endl;
	glfwSetMouseButtonCallback(window, mouseButton_callback);
	glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, windowResize_callback);
    glfwSetFramebufferSizeCallback(window, framebufferResize_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    std::cout<<"Initializing GLEW"<<std::endl;
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		exit(1);
	}    

	// Define the viewport dimensions
	glViewport(0, 0, WindowAttrib::WIDTH, WindowAttrib::HEIGHT);

    // set clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // disable vsync to speedtest different implementations 
    glfwSwapInterval(0);

    Camera camera;

    std::cout<<"Creating fractal image"<<std::endl;
    Fractal2D fractal(window);

    //variables to count fps
    GLint nFrames = 0;
    Timer timer; timer.start();
    GLdouble timePerFrame  = 0.0;

    showControls();

    std::cout<<"Starting rendering loop"<<std::endl;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
        //resize window when needed
        resizedWindow(window, fractal);
        // update camera based on input
        camera.update(window);
        // update fractal render settings
        FractalSettings::update();

		// Render
		// Clear the colorbuffer
		glClear(GL_COLOR_BUFFER_BIT);

        //render image
	    fractal.render(camera);

	    glfwSwapBuffers(window);

        // count fps
        nFrames++;
        GLdouble deltaT = timer.dtNow();
        if (deltaT > 1.0)
        {
            timePerFrame = deltaT/GLdouble(nFrames);
            std::string windowName;
            if       (FractalSettings::renderPlatform == FractalSettings::RENDER_CPU)          windowName += "CPU:: ";
            else if  (FractalSettings::renderPlatform == FractalSettings::RENDER_SHADERDOUBLE) windowName += "SHADER-DOUBLE:: ";
            else if  (FractalSettings::renderPlatform == FractalSettings::RENDER_SHADERFLOAT)  windowName += "SHADER-FLOAT:: ";
            windowName += "nFrames "+std::to_string(nFrames)+" ms/frame = "+std::to_string(timePerFrame*1e3);
            glfwSetWindowTitle(window, windowName.c_str());
            timer.start();
            timePerFrame = 0.0;
            nFrames=0;
        }
	}

	std::cout<< "destroying window" <<std::endl;
	glfwDestroyWindow(window);

	std::cout<< "terminating glfw" <<std::endl;
	glfwTerminate();

	return 0;
}

