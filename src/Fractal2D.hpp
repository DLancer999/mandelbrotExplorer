
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

Class
    Fractal2D
 
Description
    Class responsible for the rendering of the mandelbrot image
 
SourceFiles
    Fractal2D.cpp

\************************************************************************/

#ifndef FRACTAL2D_H
#define FRACTAL2D_H

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//other includes
#include "Shader.hpp"
#include "Camera.hpp"
#include "UnqArrayPointer.hpp"

class Fractal2D
{
protected:
    //handlers
	GLuint VAO_;
	GLuint VBOPoints_;
	GLuint VBOTex_;
	GLuint EBO_;
    GLuint texEscapeTimeHandler_;
    GLuint texZMagHandler_;

    //image related arrays
	GLint                    width_;       //texture width  
	GLint                    height_;      //texture height
	UnqArrayPointer<GLuint>  escapeTime_;  //used to render fractal - diverging iter
    UnqArrayPointer<GLfloat> Znorm_;       //used to render fractal - Z mag squared

    //shaders used for rendering
    Shader drawShader_;     //rendering pipeline
    Shader fractalShader_;  //compute shader - computes espace time of each pixel - double precision
    Shader ffractalShader_; //compute shader - computes espace time of each pixel - single precision

    //protected member functions
    void cpuRendering(Camera&);
    void gpuRendering(Camera&);
    void updateBindedTextures(GLboolean);

public:
    //public members
    //constructor
    Fractal2D(); 
    Fractal2D(GLFWwindow*); 
    Fractal2D(const Fractal2D&);  //disable copy constructor
    ~Fractal2D();

    //public member functions
    void initialize(GLFWwindow* );
    void resizeToWindow(GLint width, GLint height);
    void render(Camera&);
};

#endif
