
/*************************************************************************\
License
    Copyright (c) 2017 Kavvadias Ioannis.
    
    This file is part of mandelbrotExplorer.
    
    Licensed under the MIT License. See LICENSE file in the project root for 
    full license information.  

\************************************************************************/

#include "UnqArrayPointer.hpp"

//********************************************************************************
template <class T>
UnqArrayPointer<T>::UnqArrayPointer():
//********************************************************************************
pointer_(0),
size_(0)
{
}

//********************************************************************************
template <class T>
UnqArrayPointer<T>::UnqArrayPointer(T* pointer, const GLuint size):
//********************************************************************************
pointer_(pointer),
size_(size)
{
}

//********************************************************************************
template <class T>
UnqArrayPointer<T>::UnqArrayPointer(const GLuint size):
//********************************************************************************
pointer_(0),
size_(size)
{
    if (size>0)
    {
        pointer_ = new T[size];
    }
    else 
    {
        std::cerr<<"UnqArrayPointer::Creating array with size "<<size<<std::endl;
        exit(EXIT_FAILURE);
    }   
}

//********************************************************************************
template <class T>
UnqArrayPointer<T>::~UnqArrayPointer()
//********************************************************************************
{
    if (pointer_) delete[] pointer_; 
    pointer_=0;
    size_ = 0;
}

//********************************************************************************
template <class T>
T* UnqArrayPointer<T>::ptr()
//********************************************************************************
{
    return pointer_;
}

//********************************************************************************
template <class T>
GLuint UnqArrayPointer<T>::size()
//********************************************************************************
{
    return size_;
}

//********************************************************************************
template <class T>
void UnqArrayPointer<T>::set(const GLuint size)
//********************************************************************************
{
    if (pointer_) delete[] pointer_; 
    if (size>0)
    {
        pointer_ = new T[size];
    }
    else 
    {
        std::cerr<<"UnqArrayPointer::Creating array with size "<<size<<std::endl;
        exit(EXIT_FAILURE);
    }   
    size_ = size;
}

//********************************************************************************
template <class T>
void UnqArrayPointer<T>::set(T* pointer, const GLuint size)
//********************************************************************************
{
    if (pointer_) delete[] pointer_; 
    pointer_ = pointer;
    size_ = size;
}

//********************************************************************************
template <class T>
UnqArrayPointer<T>& UnqArrayPointer<T>::operator=(const T& operand)
//********************************************************************************
{
    T* iter = &pointer_[0];
    for (GLuint i=0; i<size_; i++) 
    {
        *iter = operand;
        iter++;
      //pointer_[i] = operand;
    }
    return *this;
}

//********************************************************************************
template <class T>
T& UnqArrayPointer<T>::operator[](const GLuint i)
//********************************************************************************
{
    //set bounds check
    //if (i>=size_) 
    //{
    //    std::cerr<<"UnqArrayPointer::Access at point "<<i<<" - out of bounds - size="<<size_<<std::endl;
    //    exit(EXIT_FAILURE);
    //}

    return pointer_[i];
}

