#include <GLUT/glut.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileProcessor.h"

int Height;
int Lenght;
FileProcessor FileReader;

void display();
void ClearBuffer();
void ChooseAlgorithm();
int ChooseTransform(int polygon);

void Rotation(double degree);

void Scale(int scalx, int scaly);

void Translation(float vec1, float vec2);

static float* PixelBuffer;

static int input = 0;
static int polygon =0;
static int choose = 0;

int main(int argc, char *argv[])
{
    
    //allocate new pixel buffer, need initialization!!
    std::cout << "Please Initial window size. Height & Lenght. For instance 200 200"<<std::endl;
    std::cin>> Height >> Lenght;
    
    FileReader.Addline(Lenght, Height);
    
    PixelBuffer = new float[Height * Lenght];
    
    ChooseAlgorithm();
    
   // FileReader.polygons[0].DebugDrawLine(PixelBuffer);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    //set window size to 200*200
    glutInitWindowSize(Height, Lenght);
    //set window position
    glutInitWindowPosition(100, 100);
    
    //create and set main window title
    glutCreateWindow("Project1-4!!");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    //sets display function
    glutDisplayFunc(display);
    for(int i=0; i<250; i++)
    {
        PixelBuffer[100 * 500 + i] = 255;
    }
    
    glutMainLoop();//main display loop, will display until terminate

    return 0;
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
    float vec1, vec2;
    int scalx, scaly;
    double degree;
    //Misc.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(200, 200, GL_BLUE, GL_FLOAT, PixelBuffer);
    
    glFlush();
    
    if(input == 1)
    {
        Translation( vec1,  vec2);
    }else if(input == 2)
    {
        Rotation(degree);
    }
    else if(input == 3)
    {
        Scale(scalx, scaly);
    }
    //window refresh
    
    polygon = ChooseTransform(polygon);
    std::cout<<"Press 1 to call translation function "<<std::endl;
    std::cout<<"Press 2 to call rotation function "<<std::endl;
    std::cout<<"Press 3 to call scaling function "<<std::endl;
    std::cin>>input;
}


void ClearBuffer()
{
    for(int i = 0; i <= Height; i++)
    {
        for(int j = 0; j<= Lenght; j++)
        {
            int index = i*Lenght + j;
            PixelBuffer[index] = 0;
        }
    }
}

void ChooseAlgorithm()
{
    std::cout<<"Which algorithem you want to use to draw line "<<std::endl;
    std::cout<<"1. DDA  "<<"2.Bresenham"<<std::endl;
    std::cin>>choose;
    FileReader.polygons[0].DrawPixel(PixelBuffer, choose);
    FileReader.polygons[1].DrawPixel(PixelBuffer, choose);
    choose = 0;
    std::cout<<"Choose which polygon to Rasterze "<<std::endl;
    std::cout<<"1.First 2.Second 3.Both"<<std::endl;
    std::cin>>choose;
    if(choose == 1)
    {
        FileReader.polygons[0].Rasterzing(PixelBuffer);
    }else if(choose == 2)
    {
        FileReader.polygons[1].Rasterzing(PixelBuffer);
        std::cout<<"enter rasterzing 1"<<std::endl;
    }
    else
    {
        FileReader.polygons[0].Rasterzing(PixelBuffer);
        FileReader.polygons[1].Rasterzing(PixelBuffer);
    }
}

int ChooseTransform(int polygon)
{
    std::cout<<"Please choose a polygon to transform 0. first 1.second "<<std::endl;
    std::cin>>polygon;
    return polygon;
}

void Translation(float vec1, float vec2)
{
    ClearBuffer();
    std::cout<<"vec1 will control the shape to shift left or right. vec2 will control the shape to shift up or down"<<std::endl;
    std::cout<<"Please choose a vector to translate : vec1"<<std::endl;
    std::cin>>vec1;
    std::cout<<"Please choose a vector to translate : vec2"<<std::endl;
    std::cin>>vec2;
    FileReader.polygons[polygon].Translation(vec1, vec2);
    //   std::cout<<"polygon "<<polygon<<std::endl;
    for(auto i : FileReader.polygons)
    {
        i.DrawPixel(PixelBuffer, choose);
        i.Rasterzing(PixelBuffer);
    }
    glDrawPixels(200, 200, GL_BLUE, GL_FLOAT, PixelBuffer);
    glutPostRedisplay();
    glFlush();
}

void Rotation(double degree)
{
    ClearBuffer();
    std::cout<<"Example. You can input 45, which mean rotate 45 degree"<<std::endl;
    std::cout<<"Please choose how many degree to rotate : "<<std::endl;
    std::cin>>degree;
    FileReader.polygons[polygon].Rotation(degree);
    for(auto i : FileReader.polygons)
    {
        i.DrawPixel(PixelBuffer, choose);
        i.Rasterzing(PixelBuffer);
    }
    glDrawPixels(200, 200, GL_BLUE, GL_FLOAT, PixelBuffer);
    glutPostRedisplay();
    glFlush();
}

void Scale(int scalx, int scaly)
{
    ClearBuffer();
    std::cout<<"Input a scale factor to scale the shape"<<std::endl;
    std::cout<<"Scalx Scaly"<<std::endl;
    std::cin>>scalx >>scaly;
    FileReader.polygons[polygon].Scalling(scalx, scaly);
    for(auto i : FileReader.polygons)
    {
        i.DrawPixel(PixelBuffer, choose);
        i.Rasterzing(PixelBuffer);
    }
    glDrawPixels(200, 200, GL_BLUE, GL_FLOAT, PixelBuffer);
    glutPostRedisplay();
    glFlush();
}

