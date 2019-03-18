#include <GLUT/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "FileProcessor.h"


//--------------------------------------------------------------
void display();
void ScreenSeperate();
void XYZonScreen();
void DrawOrigin(int index);
void DrawXY(int index);
void DrawXZ(int index);
void DrawYZ(int index);
void AxisonScreen();
void DrawAll();
void Transform(int choose);

//--------------------------------------------------------------

FileProcessor FileReader;

static bool input = true;
static int choose = 0;

//--------------------------------------------------------------

int main(int argc, char *argv[])
{
    //allocate new pixel buffer, need initialization!!
  //  PixelBuffer = new float[200 * 200 * 3];
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    //set window size to 200*200
    glutInitWindowSize(500, 500);
    //set window position
    glutInitWindowPosition(100, 100);
    
    //create and set main window title
    int MainWindow = glutCreateWindow("Project2");
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
    
  //  glTranslatef(0.0f, 0.0f, -4.0f);//move forward 4 units
  //  FileReader.objects[0].Scale(2);
    DrawAll();
    glFlush();
    
    if(input)
    {
        DrawAll();
        glFlush();
    }else{
        std::cout<<"Press 1 to call translation function "<<std::endl;
        std::cout<<"Press 2 to call rotation function "<<std::endl;
        std::cout<<"Press 3 to call scaling function "<<std::endl;
        std::cout<<"Press 4 to end transforming and save new Coordinate to output file "<<std::endl;
        std::cin>>choose;
    }
    if(!input)
    {
        Transform(choose);
    }
    if(input)
    {
        input = false;
    }
    
    //window refresh
   // polygon = ChooseTransform(polygon);

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


}

void DrawOrigin(int index)
{
    glColor3f(1.0f, 0.0f, 1.0f); //pink color
    glBegin(GL_LINES);
    for(unsigned int i = 0; i<FileReader.objects[index].edges.size(); i++)
    {
        int edge1 = std::get<0>(FileReader.objects[index].edges[i]) - 1;
        int edge2 = std::get<1>(FileReader.objects[index].edges[i]) - 1;
        Vec2 vertex1 = FileReader.objects[index].CoordinateOn2D[edge1];
        Vec2 vertex2 = FileReader.objects[index].CoordinateOn2D[edge2];
        glVertex3f(std::get<0>(vertex1), std::get<1>(vertex1), 0);
        glVertex3f(std::get<0>(vertex2), std::get<1>(vertex2), 0);
    }
    glEnd();//end drawing of polygon
}

void DrawXY(int index)
{
    glColor3f(1.0f, 0.0f, 1.0f); //pink color
    glBegin(GL_LINES);
    for(unsigned int i = 0; i<FileReader.objects[index].edges.size(); i++)
    {
        auto edge = FileReader.objects[index].edges[i];
        int edge1 = std::get<0>(edge) - 1;
        int edge2 = std::get<1>(edge) - 1;
        Vec2 vertex1 = FileReader.objects[index].XYCoords[edge1];
        Vec2 vertex2 = FileReader.objects[index].XYCoords[edge2];
        glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1));
        glVertex2f(std::get<0>(vertex2), std::get<1>(vertex2));
    }
    glEnd();//end drawing of polygon
}

void DrawYZ(int index)
{
    glColor3f(1.0f, 0.0f, 1.0f); //pink color
    glBegin(GL_LINES);
    for(unsigned int i = 0; i<FileReader.objects[index].edges.size(); i++)
    {
        int edge1 = std::get<0>(FileReader.objects[index].edges[i]) - 1;
        int edge2 = std::get<1>(FileReader.objects[index].edges[i]) - 1;
        Vec2 vertex1 = FileReader.objects[index].YZCoords[edge1];
        Vec2 vertex2 = FileReader.objects[index].YZCoords[edge2];
        glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1));
        glVertex2f(std::get<0>(vertex2), std::get<1>(vertex2));
    }
    glEnd();//end drawing of polygon
    
}

void DrawXZ(int index)
{
    glColor3f(1.0f, 0.0f, 1.0f); //pink color
    glBegin(GL_LINES);
    for(unsigned int i = 0; i<FileReader.objects[index].edges.size(); i++)
    {
        int edge1 = std::get<0>(FileReader.objects[index].edges[i]) - 1;
        int edge2 = std::get<1>(FileReader.objects[index].edges[i]) - 1;
        Vec2 vertex1 = FileReader.objects[index].XZCoords[edge1];
        Vec2 vertex2 = FileReader.objects[index].XZCoords[edge2];
        glVertex2f(std::get<0>(vertex1), std::get<1>(vertex1));
        glVertex2f(std::get<0>(vertex2), std::get<1>(vertex2));
    }
    glEnd();//end drawing of polygon
    
}

void DrawAll()
{
    ScreenSeperate();
    XYZonScreen();
    AxisonScreen();
    for(unsigned int i=0; i<FileReader.objects.size(); i++)
    {
        DrawOrigin(i);
        DrawXY(i);
        DrawYZ(i);
        DrawXZ(i);
    }
}

void Transform(int choose)
{
    if(choose == 1)
    {
        float a,b,c;
        std::cout<<std::endl;
        std::cout<<" Enter 3D vector "<<std::endl;
        std::cout<<" Example: 0.5 0.5 0.5 ( seperated by space )"<<std::endl;
        std::cin>>a>>b>>c;
        std::cout<<std::endl;
        for(unsigned int i=0;i<FileReader.objects.size();i++)
        {
            FileReader.objects[i].Translate(a, b, c);
            glutPostRedisplay();
            glFlush();
        }
    }
    else if(choose == 2)
    {
        float factor;
        std::cout<<std::endl;
        std::cout<<" Enter a scale factor "<<std::endl;
        std::cout<<" Example: 2 "<<std::endl;
        std::cin>>factor;
        std::cout<<std::endl;
        for(unsigned int i=0;i<FileReader.objects.size();i++)
        {
            FileReader.objects[i].Scale(factor);
            glutPostRedisplay();
            glFlush();
        }
    }
    else if(choose == 3)
    {
        float angle;
        std::string plane;
        std::cout<<std::endl;
        std::cout<<" Enter an axis and a angle to Rotate "<<std::endl;
        std::cout<<" Example: x 45.0 "<<std::endl;
        std::cin>>plane>>angle;
        std::cout<<std::endl;
        for(unsigned int i=0;i<FileReader.objects.size();i++)
        {
            FileReader.objects[i].Rotation(plane, angle);
            glutPostRedisplay();
            glFlush();
        }
    }
    else if(choose == 4)
    {
        FileReader.WriteFile();
        
    }
    choose = 0;
}


