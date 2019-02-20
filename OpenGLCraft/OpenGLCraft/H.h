//
//  Helper.h
//  opengl
//
//  Created by David Skinner on 2/13/19.
//  Copyright © 2019 David Skinner. All rights reserved.
//

#define LINIX
#ifdef LINUX
#include <GL/glut.h>
#else
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#endif

#ifndef Helper_h
#define Helper_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

////////////////////////////Helpers////////////////////////////
//gets a random floating point number in a range
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

//gets a random integer in a range
int RandomInt(int min, int max){
    return rand() % max + min;
}

//more concise
void endFlush(){
    glEnd();
    glFlush();
}

//creates/allocates a 2D array
float** createArray(int r, int c){
    
    float** array = new float*[r]; // Rows
    for (int i = 0; i < r; i++){
        array[i] = new float[c]; // Columns
    }
    return array;
}

float getColor()
{
    return RandomFloat(0.3, 0.6);
}
////////////////////////////Helpers////////////////////////////

#endif /* Helper_h */


