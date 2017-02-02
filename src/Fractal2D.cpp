
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

\************************************************************************/

#include "Fractal2D.hpp"
#include "FractalSettings.hpp"
#include "Complex.hpp"

//********************************************************************************
Fractal2D::Fractal2D():
//********************************************************************************
VAO_(0),
VBOPoints_(0),
VBOTex_(0),
EBO_(0),
texEscapeTimeHandler_(0),
texZMagHandler_(0),
width_(0),
height_(0),
escapeTime_(),
Znorm_(),
drawShader_(),
fractalShader_(),
ffractalShader_()
{
    //have to call this->initialize(...) before use!
}

//********************************************************************************
Fractal2D::Fractal2D(GLFWwindow* window):
//********************************************************************************
VAO_(0),
VBOPoints_(0),
VBOTex_(0),
EBO_(0),
texEscapeTimeHandler_(0),
texZMagHandler_(0),
width_(0),
height_(0),
escapeTime_(),
Znorm_(),
drawShader_(),
fractalShader_(),
ffractalShader_()
{
    initialize(window);
}

//********************************************************************************
Fractal2D::~Fractal2D()
//********************************************************************************
{
    glDeleteBuffers(1, &VBOPoints_   );
    glDeleteBuffers(1, &VBOTex_      );
    glDeleteVertexArrays(1, &VAO_);
    glDeleteTextures(1, &texEscapeTimeHandler_);
    glDeleteTextures(1, &texZMagHandler_);
}

//********************************************************************************
void Fractal2D::initialize(GLFWwindow* window)
//********************************************************************************
{
    // compile shaders
	drawShader_.compileVertexShader("src/shaders/texShader.vert");
	drawShader_.compileFragmentShader("src/shaders/texShader.frag");
	drawShader_.linkShaders();

    fractalShader_.compileComputeShader("src/shaders/fracShader_double.comp");
    fractalShader_.linkShaders();

    ffractalShader_.compileComputeShader("src/shaders/fracShader_float.comp");
    ffractalShader_.linkShaders();

    // Define Data for handlers
    GLfloat vertices[] = 
    {
        // point coord 
         1.0f,  1.0f, // Top Right
         1.0f, -1.0f, // Bottom Right
        -1.0f, -1.0f, // Bottom Left
        -1.0f,  1.0f  // Top Left 
    };

    GLuint indices [] =
    {
        0, 1, 3,  //first  triangle
        1, 2, 3   //second triangle
    };

    GLfloat texCoords[] = 
    {
        //tex coord
        1.0f, 1.0f, // Top Right
        1.0f, 0.0f, // Bottom Right
        0.0f, 0.0f, // Bottom Left
        0.0f, 1.0f  // Top Left 
    };

    // Create Vertex/Element Buffer and Array Objects
    // Create Vertex Buffer
    glGenBuffers(1, &VBOPoints_);
    glGenBuffers(1, &VBOTex_);

    // Create Element Buffer for triangle 
    glGenBuffers(1, &EBO_);
    // Create Array for triangle
    glGenVertexArrays(1, &VAO_);

    // Bind Vertex Array Object
    glBindVertexArray(VAO_);
    // Bind Buffer to GL_ELEMENT_ARRAY_BUFFER 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    // Bind data to GL_ELEMENT_ARRAY_BUFFER
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Bind Buffer to GL_ARRAY_BUFFER 
    glBindBuffer(GL_ARRAY_BUFFER, VBOPoints_);
    // Bind data to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Bind Vertices to buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid*)0);
    // Enable Vertex Attributes
    glEnableVertexAttribArray(0);
    // Bind Buffer to GL_ARRAY_BUFFER 
    glBindBuffer(GL_ARRAY_BUFFER, VBOTex_);
    // Bind data to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    // Bind Vertices to buffer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid*)0);
    // Enable Vertex Attributes
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    //initialize texture arrays
    GLint width, height;
    glfwGetWindowSize(window, &width, &height);
    resizeToWindow(width,height);

    //initialize fractal textures
    glGenTextures(1, &texEscapeTimeHandler_);
    glBindTexture(GL_TEXTURE_RECTANGLE, texEscapeTimeHandler_);
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // create initial texture
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_R32UI, width_, height_, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, escapeTime_.ptr());
    glBindImageTexture(0, texEscapeTimeHandler_, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32UI);
    glBindTexture(GL_TEXTURE_RECTANGLE, 0);

    glGenTextures(1, &texZMagHandler_);
    glBindTexture(GL_TEXTURE_RECTANGLE, texZMagHandler_);
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // create initial texture
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_R32F, width_, height_, 0, GL_RED, GL_FLOAT, Znorm_.ptr());
    glBindImageTexture(1, texZMagHandler_, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);
    glBindTexture(GL_TEXTURE_RECTANGLE, 0);
}

//********************************************************************************
void Fractal2D::resizeToWindow(GLint width, GLint height)
//********************************************************************************
{
    //resize arrays
    width_=width;
    height_=height;

    GLint imageSize = width_*height_; //escapeTime for each pixel
    escapeTime_.set(imageSize);
    escapeTime_ = 0;

    Znorm_.set(imageSize);
    Znorm_ = 0.0f;

    //resizing textures
    if (texEscapeTimeHandler_)
    {
        glBindTexture(GL_TEXTURE_RECTANGLE, texEscapeTimeHandler_);
        glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_R32UI, width_, height_, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, escapeTime_.ptr());
        glBindTexture(GL_TEXTURE_RECTANGLE, 0);
    }

    if (texZMagHandler_)
    {
        glBindTexture(GL_TEXTURE_RECTANGLE, texZMagHandler_);
        glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_R32F, width_, height_, 0, GL_RED, GL_FLOAT, Znorm_.ptr());
        glBindTexture(GL_TEXTURE_RECTANGLE, 0);
    }

    GLfloat texCoords[] = 
    {
        //tex coord
        GLfloat(width_), GLfloat(height_), // Top Right
        GLfloat(width_), 0.0f,             // Bottom Right
        0.0f,            0.0f,             // Bottom Left
        0.0f,            GLfloat(height_)  // Top Left 
    };

    //update buffer
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBOTex_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glBindVertexArray(0); // Unbind VAO
    //set clipping end
}

//********************************************************************************
void Fractal2D::render(Camera& camera)
//********************************************************************************
{
    if (FractalSettings::renderPlatform == FractalSettings::RENDER_CPU)
    {
        cpuRendering(camera);
        updateBindedTextures(true);
    }
    else 
    {
        gpuRendering(camera);
        updateBindedTextures(false);
    }

    drawShader_.use();

	// Bind Vertex Array 1 Object
	glBindVertexArray(VAO_);
	// draw Triangle from VAO and shaderProgram1
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Unbind Vertex Array Object
	glBindVertexArray(0);
}

//********************************************************************************
void Fractal2D::cpuRendering(Camera& camera)
//********************************************************************************
{
    //length of each pixel
    GLdouble d = camera.diameter()/GLdouble(height_); 

    Complex c(0.0,0.0); 
    Complex z(0.0,0.0);

    GLint halfHeight = height_/2;
    GLint halfWidth  = width_/2;

    GLdouble x,y;
    GLuint k, iNode;

    for (GLint i=0;i<height_;i++)
    {
        for (GLint j=0;j<width_;j++)
    	{
            x = camera.centerX()+(GLdouble(j-halfWidth ) + 0.5)*d;
            y = camera.centerY()+(GLdouble(i-halfHeight) + 0.5)*d;

            c  = Complex( x , y );
            z  = Complex(0.0,0.0);
            for (k=0;k<FractalSettings::accuracy;k++)
            {
                //z = (z*z) + c;
                z *=z; 
                z +=c;
                if (z.norm()>4.0)
                {
                    break;
                }
            }
            iNode = i*width_+j;
            if (k == FractalSettings::accuracy)
            {
                escapeTime_[iNode] = 0;
                Znorm_[iNode]      = 4.0f;
                // values chosen for black color inside fractal
            }
            else
            {
                escapeTime_[iNode] = k;
                Znorm_[iNode]      = GLfloat(z.norm());
            }
        }
    }
}


//********************************************************************************
void Fractal2D::gpuRendering(Camera& camera)
//********************************************************************************
{
    GLdouble pixelSize = camera.diameter()/GLdouble(height_);

    if (FractalSettings::renderPlatform==FractalSettings::RENDER_SHADERDOUBLE)
    {
        fractalShader_.use();
        //give shader the cam Coord
        GLuint camCenterLocation = glGetUniformLocation(fractalShader_.program(),"camCenter");
        glUniform2d(camCenterLocation, camera.centerX(), camera.centerY());
        //give shader the pixel size
        GLuint pixelSizeLocation = glGetUniformLocation(fractalShader_.program(),"pixelSize");
        glUniform1d(pixelSizeLocation, pixelSize);
        //give shader the max escape time for fractals
        GLuint accuracyLocation = glGetUniformLocation(fractalShader_.program(),"fracAccuracy");
        glUniform1ui(accuracyLocation, FractalSettings::accuracy);
        //give shader other stuff
        GLuint widthLocation = glGetUniformLocation(fractalShader_.program(),"width");
        glUniform1i(widthLocation, width_);
        GLuint halfSizeLocation = glGetUniformLocation(fractalShader_.program(),"halfSize");
        glUniform2i(halfSizeLocation, width_/2, height_/2);
    }
    else //if (FractalSettings::renderPlatform==SHADERFLOAT)
    {
        ffractalShader_.use();
        //give shader the cam Coord
        GLuint camCenterLocation = glGetUniformLocation(fractalShader_.program(),"camCenter");
        glUniform2f(camCenterLocation, GLfloat(camera.centerX()), GLfloat(camera.centerY()));
        //give shader the pixel size
        GLuint pixelSizeLocation = glGetUniformLocation(ffractalShader_.program(),"pixelSize");
        glUniform1f(pixelSizeLocation, GLfloat(pixelSize));
        //give shader the max escape time for fractals
        GLuint accuracyLocation = glGetUniformLocation(ffractalShader_.program(),"fracAccuracy");
        glUniform1ui(accuracyLocation, FractalSettings::accuracy);
        //give shader other stuff
        GLuint widthLocation = glGetUniformLocation(ffractalShader_.program(),"width");
        glUniform1i(widthLocation, width_);
        GLuint halfSizeLocation = glGetUniformLocation(ffractalShader_.program(),"halfSize");
        glUniform2i(halfSizeLocation, width_/2, height_/2);
    }
    //run shader
    glDispatchCompute( width_/128+1, height_, 1 ); 
    glMemoryBarrier( GL_ALL_BARRIER_BITS );
}

//********************************************************************************
void Fractal2D::updateBindedTextures(GLboolean updateTex)
//********************************************************************************
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_RECTANGLE, texEscapeTimeHandler_);
    if (updateTex) glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, width_, height_, GL_RED_INTEGER, GL_UNSIGNED_INT, escapeTime_.ptr());
    glUniform1i(glGetUniformLocation(drawShader_.program(), "escapeTime"), 0);  

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_RECTANGLE, texZMagHandler_);
    if (updateTex) glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, width_, height_, GL_RED, GL_FLOAT, Znorm_.ptr());
    glUniform1i(glGetUniformLocation(drawShader_.program(), "ZMagTex"), 1);  
}
