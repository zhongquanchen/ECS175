#include <GLUT/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "FileProcessor.hpp"


//--------------------------------------------------------------
void display();
void ScreenSeperate();
void XYZonScreen();
void AxisonScreen();

void DrawOrigin(int index);
void DrawXY(int index);
void DrawXZ(int index);
void DrawYZ(int index);

void DrawAll();

//--------------------------------------------------------------

FileProcessor FileReader;

//--------------------------------------------------------------

int main(int argc, char *argv[])
{
    //allocate new pixel buffer, need initialization!!
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    //set window size to 200*200
    glutInitWindowSize(600, 600);
    //set window position
    glutInitWindowPosition(100, 100);
    
    //create and set main window title
    glutCreateWindow("Project3-1");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    //sets display function
    glutDisplayFunc(display);
    
    glutMainLoop();//main display loop, will display until terminate
    
    return 0;
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
    //clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();//load identity matrix
    DrawAll();
    //glutPostRedisplay();
    glFlush();
    
}

void ScreenSeperate()
{
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);//begin drawing of polygon
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0, -1, 0);
    glVertex3f(0, 1, 0);
    
    //display 1 on screen
    glVertex3f(-0.1, 0.95, 0);
    glVertex3f(-0.1, 0.9, 0);
    //display 2 on screen
    glVertex3f(0.95, 0.95, 0);
    glVertex3f(0.95, 0.90, 0);
    glVertex3f(0.925, 0.95, 0);
    glVertex3f(0.925, 0.9, 0);
    //display 3 on screen
    glVertex3f(-0.1, -0.05, 0);
    glVertex3f(-0.1, -0.1, 0);
    glVertex3f(-0.125, -0.05, 0);
    glVertex3f(-0.125, -0.1, 0);
    glVertex3f(-0.15, -0.05, 0);
    glVertex3f(-0.15, -0.1, 0);
    //display 4 on screen
    glVertex3f(0.90, -0.1, 0);
    glVertex3f(0.9, -0.15, 0);
    glVertex3f(0.925, -0.1, 0);
    glVertex3f(0.95, -0.15, 0);
    glVertex3f(0.95, -0.15, 0);
    glVertex3f(0.975, -0.1, 0);
    glEnd();//end drawing of polygon
}

void XYZonScreen()
{
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.1, -0.7, 0);
    glVertex3f(0.9, -0.7, 0);
    
    glVertex3f(0.3, -0.9, 0);
    glVertex3f(0.3, -0.1, 0);
    
    glVertex3f(0.1, -0.9, 0);
    glVertex3f(0.8, -0.2, 0);
    glEnd();//end drawing of polygon
    
}

void AxisonScreen()
{
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    //Project Axis on Screen iii
    glVertex3f(-0.9, -0.7, 0);
    glVertex3f(-0.1, -0.7, 0);
    glVertex3f(-0.7, -0.9, 0);
    glVertex3f(-0.7, -0.1, 0);
    //Project Axis on Screen ii
    glVertex3f(0.3, 0.1, 0);
    glVertex3f(0.3, 0.9, 0);
    glVertex3f(0.1, 0.3, 0);
    glVertex3f(0.9, 0.3, 0);
    //Project Axis on Screen i
    glVertex3f(-0.9, 0.3, 0);
    glVertex3f(-0.1, 0.3, 0);
    glVertex3f(-0.7, 0.1, 0);
    glVertex3f(-0.7, 0.9, 0);
    glEnd();//end drawing of polygon
    
}

void DrawAll()
{
    ScreenSeperate();
 //   XYZonScreen();
 //   AxisonScreen();
  //  std::cout<<"how many object are there "<<FileReader.objects.size()<<std::endl;
    for(unsigned int i=0; i<FileReader.objects.size(); i++)
    {
        DrawOrigin(i);
    }
     
}

void DrawOrigin(int index)
{

    FileReader.objects[index].DrawItSelt();
}


