//
//  Object.cpp
//  project2
//
//  Created by Oscar on 2018/10/24.
//  Copyright © 2018年 Oscar. All rights reserved.
//

#include "Object.h"

#include <iostream>

Object::Object(std::vector<Vec3> coordinates, std::vector<Vec2> edge)
{
    for(auto a : coordinates)
    {
        Coordinates.push_back(a);
    }
    for(auto b : edge)
    {
        edges.push_back(b);
       // std::cout<<std::get<0>(b)<<" "<<std::get<1>(b)<<std::endl;
    }
    ConvertCoordinateTo2D();
    ConvertToXYCoords();
    ConvertToXZCoords();
    ConvertToYZCoords();
}

void Object::ConvertCoordinateTo2D()
{
    CoordinateOn2D.clear();
    for(auto a : Coordinates)
    {
        float x = std::get<0>(a);
        float y = std::get<1>(a);
        float z = std::get<2>(a);
        
        float x1 = sqrt(z/2.0);
        float y1 = x1;
        CoordinateOn2D.push_back(std::make_tuple((x+x1)/4.0 + 0.3,(y+y1)/4.0 -0.7));
    }
}

void Object::ConvertToXYCoords()
{
    XYCoords.clear();
    for(auto a : Coordinates)
    {
        float x = std::get<0>(a);
        float y = std::get<1>(a);
        XYCoords.push_back(std::make_tuple(x/4 - 0.7,y/4 + 0.3));
    }
}

void Object::ConvertToYZCoords()
{
    YZCoords.clear();
    for(auto a : Coordinates)
    {
        float y = std::get<1>(a);
        float z = std::get<2>(a);
        YZCoords.push_back(std::make_tuple(y/4 + 0.3,z/4 + 0.3));
    }
}
void Object::ConvertToXZCoords()
{
    XZCoords.clear();
    for(auto a : Coordinates)
    {
        float x = std::get<0>(a);
        float z = std::get<2>(a);
        XZCoords.push_back(std::make_tuple(x/4 - 0.7,z/4 -0.7));
    }
}

void Object::Translate(float x, float y, float z)
{
   // std::cout<<"Translated"<<std::endl;
    for(unsigned int i=0; i<Coordinates.size(); i++)
    {
        std::get<0>(Coordinates[i]) += x;
        std::get<1>(Coordinates[i]) += y;
        std::get<2>(Coordinates[i]) += z;
    }
    for(unsigned int i=0; i<Coordinates.size(); i++)
    {
        float x1 = std::get<0>(Coordinates[i]) + x/2;
        float y1 = std::get<1>(Coordinates[i]) + y/2;
        float z1 = std::get<2>(Coordinates[i]) + z/2;
        OutputCoords.push_back(std::make_tuple(x1,y1,z1));
    }
    UpdateAll();
}

void Object::Rotation(std::string plane, float angle)
{

    //Translate point will use later
    Vec3 p1 = Coordinates[0];

    //Translate back to origin point
    Translate(-1* std::get<0>(p1), -1 * std::get<1>(p1), -1 * std::get<2>(p1));

    if(plane == "y")
    {
        for(unsigned int i = 0; i<Coordinates.size(); i++)
        {
            double tempz = std::get<2>(Coordinates[i]);
            double x = std::get<0>(Coordinates[i]);
            double z = std::get<2>(Coordinates[i]);
            std::get<2>(Coordinates[i]) = z*cos(angle * PI / 180.0) - x*sin(angle*PI/180.0);
            std::get<0>(Coordinates[i]) = tempz*sin(angle*PI/180.0) + x*cos(angle*PI/180.0);
        }
        
    }
    else if(plane == "x")
    {
        for(unsigned int i = 0; i<Coordinates.size(); i++)
        {
            double tempy = std::get<1>(Coordinates[i]);
            double y = std::get<1>(Coordinates[i]);
            double z = std::get<2>(Coordinates[i]);
            std::get<1>(Coordinates[i]) = y*cos(angle * PI / 180.0) - z * sin(angle*PI/180.0);
            std::get<2>(Coordinates[i]) = tempy*sin(angle*PI/180.0) + z*cos(angle*PI/180.0);
        }
    }
    else
    {
       // std::cout<<"entered loop"<<std::endl;
        for(unsigned int i = 0; i<Coordinates.size(); i++)
        {
            double tempArray = std::get<0>(Coordinates[i]);
            std::get<0>(Coordinates[i]) = std::get<0>(Coordinates[i]) * cos(angle * PI / 180.0) + std::get<1>(Coordinates[i]) * sin(angle * PI / 180);
            std::get<1>(Coordinates[i]) = std::get<1>(Coordinates[i]) * cos(angle* PI / 180.0) - tempArray * sin( angle*PI/180.0);
        }
    }
    Translate(std::get<0>(p1), std::get<1>(p1), std::get<2>(p1));
    UpdateAll();
}

void Object::Scale(float factor)
{
    //std::cout<<"Scaled"<<std::endl;
    for(unsigned int i=0; i<Coordinates.size(); i++)
    {
        std::get<0>(Coordinates[i]) *= factor;
        std::get<1>(Coordinates[i]) *= factor;
        std::get<2>(Coordinates[i]) *= factor;
    }
    for(unsigned int i=0; i<Coordinates.size(); i++)
    {
        float x1 = std::get<0>(Coordinates[i]);
        float y1 = std::get<1>(Coordinates[i]);
        float z1 = std::get<2>(Coordinates[i]);
        OutputCoords.push_back(std::make_tuple(x1,y1,z1));
    }
    UpdateAll();
}

void Object::UpdateAll()
{
    ConvertCoordinateTo2D();
    ConvertToXYCoords();
    ConvertToXZCoords();
    ConvertToYZCoords();
}

void Object::WriteFile(std::string filename)
{
    std::ofstream File(filename);
    File << Coordinates.size()<<"\n";
    for(auto a: Coordinates)
    {
        File<<std::get<0>(a)<<" "<<std::get<1>(a)<<" "<<std::get<2>(a);
    }
    File << edges.size();
    for(auto b:edges)
    {
        File<<std::get<0>(b)<<" "<<std::get<1>(b);
    }
    File<<std::endl;
    
}










