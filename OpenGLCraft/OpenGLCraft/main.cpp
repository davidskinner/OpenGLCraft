//---------------------------------------
// Program: balls2.cpp
// Purpose: Use Phong shading to display exploding
//          balls within a cubic region
// Author:  John Gauch
// Date:    December 2008
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

// Constants
#define ROTATE 1
#define TRANSLATE 2
#define FLYMODE 3
#define RADIUS 110
#define COUNT 20
#define SIZE 20
#define STEP 0.1
#define SLOW 0.995


// Max values
const int xmax = 50;
const int xmin = -50;
const int ymax = 50;
const int ymin = -50;
const int zmax = 50;
const int zmin = -50;

// Transformation variables
int xangle = 0;
int yangle = 0;
int zangle = 0;
int xpos = 0;
int ypos = 0;
int zpos = 0;
int mode = ROTATE;

// Player block
int PlayerX, PlayerY, PlayerZ = 0;

// Ball variables
float Px[COUNT];
float Py[COUNT];
float Pz[COUNT];
float Radius[COUNT];
float Red[COUNT];
float Green[COUNT];
float Blue[COUNT];
float X[SIZE+1][SIZE+1];
float Y[SIZE+1][SIZE+1];
float Z[SIZE+1][SIZE+1];

#include "H.h"

 class Cube {
 public:
     int x;
     int y;
     int z;
     bool kill = false;
    
    Cube(int xd, int yd, int zd)
    {
        x = xd;
        y = yd;
        z = zd;
        kill = false;
    }
};

vector<Cube> cubePositions;
//---------------------------------------
// Calculate random value between [min..max]
//---------------------------------------
float myrand(float min, float max)
{
    return rand() * (max - min) / RAND_MAX + min;
}

//---------------------------------------
// Initialize balls
//---------------------------------------
void init_balls()
{
    // Initialize balls with random positions and colors
    int i;
    for (i=0; i<COUNT; i++)
    {
        
    }
    
    // Initialize ball surface
    for (i = 0; i <= SIZE; i++)
    {
        
    }
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
    // Initialize OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-RADIUS, RADIUS, -RADIUS, RADIUS, -RADIUS, RADIUS);
    glEnable(GL_DEPTH_TEST);
    
    // Initialize smooth shading
    
    // Initialize bouncing balls
    init_balls();
}

//---------------------------------------
// Draw 3D cube
//---------------------------------------
void draw_cube(float midx, float midy, float midz, float size)
{
    // Define 8 vertices
    float ax = midx - size / 2;
    float ay = midy - size / 2;
    float az = midz + size / 2;
    float bx = midx + size / 2;
    float by = midy - size / 2;
    float bz = midz + size / 2;
    float cx = midx + size / 2;
    float cy = midy + size / 2;
    float cz = midz + size / 2;
    float dx = midx - size / 2;
    float dy = midy + size / 2;
    float dz = midz + size / 2;
    float ex = midx - size / 2;
    float ey = midy - size / 2;
    float ez = midz - size / 2;
    float fx = midx + size / 2;
    float fy = midy - size / 2;
    float fz = midz - size / 2;
    float gx = midx + size / 2;
    float gy = midy + size / 2;
    float gz = midz - size / 2;
    float hx = midx - size / 2;
    float hy = midy + size / 2;
    float hz = midz - size / 2;
    
    // Draw 6 faces
    glBegin(GL_LINE_LOOP);
    glVertex3f(ax, ay, az);
    glVertex3f(bx, by, bz);
    glVertex3f(cx, cy, cz);
    glVertex3f(dx, dy, dz);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(ax, ay, az);
    glVertex3f(dx, dy, dz);
    glVertex3f(hx, hy, hz);
    glVertex3f(ex, ey, ez);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(ax, ay, az);
    glVertex3f(ex, ey, ez);
    glVertex3f(fx, fy, fz);
    glVertex3f(bx, by, bz);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(gx, gy, gz);
    glVertex3f(fx, fy, fz);
    glVertex3f(ex, ey, ez);
    glVertex3f(hx, hy, hz);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(gx, gy, gz);
    glVertex3f(cx, cy, cz);
    glVertex3f(bx, by, bz);
    glVertex3f(fx, fy, fz);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(gx, gy, gz);
    glVertex3f(hx, hy, hz);
    glVertex3f(dx, dy, dz);
    glVertex3f(cx, cy, cz);
    glEnd();
}
//---------------------------------------
// Draw 3D ball
//---------------------------------------
void draw_ball(float centerX, float centerY,
               float centerZ, float radius)
{
    // Draw the surface
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
        {
            glBegin(GL_POLYGON);
            glNormal3f(X[i][j], Y[i][j], Z[i][j]);
            glVertex3f(centerX+radius*X[i][j],
                       centerY+radius*Y[i][j], centerZ+radius*Z[i][j]);
            
            glNormal3f(X[i][j + 1], Y[i][j + 1], Z[i][j + 1]);
            glVertex3f(centerX+radius*X[i][j + 1],
                       centerY+radius*Y[i][j + 1], centerZ+radius*Z[i][j + 1]);
            
            glNormal3f(X[i + 1][j + 1], Y[i + 1][j + 1], Z[i + 1][j + 1]);
            glVertex3f(centerX+radius*X[i + 1][j + 1],
                       centerY+radius*Y[i + 1][j + 1], centerZ+radius*Z[i + 1][j + 1]);
            
            glNormal3f(X[i + 1][j], Y[i + 1][j], Z[i + 1][j]);
            glVertex3f(centerX+radius*X[i + 1][j],
                       centerY+radius*Y[i + 1][j], centerZ+radius*Z[i + 1][j]);
            glEnd();
        }
}

void drawCubes()
{
    for (int i = 0; i < cubePositions.size(); i++) {
        draw_cube(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z, 10);
    }
}

void removeCube(int x, int y, int z)
{
    for (int i = 0; i < cubePositions.size(); i++) {
        if(cubePositions[i].x == x && cubePositions[i].y == y && cubePositions[i].z == z)
        {
            cubePositions.erase(cubePositions.begin()+i);
        }
    }
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
    // Incrementally rotate objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(xpos / 500.0, ypos / 500.0, zpos / 500.0);
    glRotatef(xangle, 1.0, 0.0, 0.0);
    glRotatef(yangle, 0.0, 1.0, 0.0);
    glRotatef(zangle, 0.0, 0.0, 1.0);

    // Draw bounding box
    draw_cube(0,0,0,RADIUS);
    draw_cube(PlayerX, PlayerY, PlayerZ, 10);
    drawCubes();
    glutSwapBuffers();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    std::cout<< xangle<<endl;
    // Determine if we are in ROTATE or TRANSLATE mode
    if ((key == 'r') || (key == 'R'))
        mode = ROTATE;
    else if ((key == 't') || (key == 'T'))
        mode = TRANSLATE;
    else if ((key == 'f') || (key == 'F'))
        mode = FLYMODE;
    
    if(mode == FLYMODE)
    {
        cout<< PlayerX<<endl;
        if (key == 'x')
        {
            PlayerX -= 10;
            if(PlayerX < xmin)
                PlayerX = xmin;
        }
        else if (key == 'y')
        {
            PlayerY -= 10;
            if(PlayerY < ymin)
                PlayerY = ymin;
        }
        else if (key == 'z')
        {
            PlayerZ -= 10;
            if(PlayerZ < zmin)
                PlayerZ = zmin;
        }
        else if (key == 'X')
        {
            PlayerX += 10;
            if(PlayerX > xmax)
                PlayerX = xmax;
        }
        else if (key == 'Y')
        {
            PlayerY += 10;
            if(PlayerY > ymax)
                PlayerY = ymax;
        }
        else if (key == 'Z')
        {
            PlayerZ += 10;
            if(PlayerZ > zmax)
                PlayerZ = zmax;
        }
    }
    
    if(key == '+')
    {
        Cube temp = Cube(PlayerX,PlayerY,PlayerZ);
        cubePositions.push_back(temp);
    }
    
    if(mode == FLYMODE && key == '-')
        removeCube(PlayerX, PlayerY, PlayerZ);
    
    // Update ROTATE parameters
    if (mode == ROTATE)
    {
        if (key == 'x')
            xangle -= 5;
        else if (key == 'y')
            yangle -= 5;
        else if (key == 'z')
            zangle -= 5;
        else if (key == 'X')
            xangle += 5;
        else if (key == 'Y')
            yangle += 5;
        else if (key == 'Z')
            zangle += 5;
    }
    
    // Update TRANSLATE parameters
    if (mode == TRANSLATE)
    {
        if (key == 'x')
            xpos -= 5;
        else if (key == 'y')
            ypos -= 5;
        else if (key == 'z')
            zpos -= 5;
        else if (key == 'X')
            xpos += 5;
        else if (key == 'Y')
            ypos += 5;
        else if (key == 'Z')
            zpos += 5;
    }
    
    // Redraw objects
    glutPostRedisplay();
}

//---------------------------------------
// Print command menu
//---------------------------------------
void print_menu()
{
    printf("\nObject controls:\n");
    printf("  '-' = remove block\n");
    printf("  '+' = add block\n");
    printf("\nMotion controls:\n");
    printf("  'r' = switch to rotation mode\n");
    printf("  't' = switch to translation mode\n");
    printf("  'x' = decrease X translation/rotation\n");
    printf("  'X' = increase X translation/rotation\n");
    printf("  'y' = decrease Y translation/rotation\n");
    printf("  'Y' = increase Y translation/rotation\n");
    printf("  'z' = decrease Z translation/rotation\n");
    printf("  'Z' = increase Z translation/rotation\n");
}

//---------------------------------------
// Mouse callback for OpenGL
//---------------------------------------
void mouse(int button, int state, int x, int y)
{
    // Handle mouse down
    static int xdown, ydown;
    if (state == GLUT_DOWN)
    {
        xdown = x;
        ydown = y;
    }
    
    // Handle ROTATE
    if ((mode == ROTATE) && (state == GLUT_UP))
    {
        xangle += (y - ydown);
        yangle -= (x - xdown);
        zangle = 0;
        glutPostRedisplay();
    }
    
    // Handle TRANSLATE
    if ((mode == TRANSLATE) && (state == GLUT_UP))
    {
        xpos += (x - xdown);
        ypos -= (y - ydown);
        glutPostRedisplay();
    }
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
    // Create OpenGL window
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(250, 250);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Baaaaaaalllllllllllls");
    init();
    print_menu();
    
    // Specify callback function
    glutDisplayFunc(display);
//    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
