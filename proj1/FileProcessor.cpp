//
//  ReadFile.cpp
//  play
//
//  Created by Oscar on 2018/10/17.
//  Copyright © 2018年 Oscar. All rights reserved.
//

#include "FileProcessor.h"


void FileProcessor::Addline(int Lenght, int height)
{
    std::ifstream ReadFile("data.txt");
    std::vector<std::string> lines;
    if(!ReadFile)
    {
        std::cerr<<"Fail to open file"<<std::endl;
        std::exit(0);
    }
    
    while(!ReadFile.eof())
    {
        std::string line;
        std::getline(ReadFile, line);
        lines.push_back(line);
    }
    int numberOfpolygon = std::stoi(lines[0]);
    
    int polygon = std::stoi(lines[2]);
    for(unsigned int i = 3; i < polygon+3; i++)
    {
        float x = std::stof(lines[i].substr(0,3));
        float y = std::stof(lines[i].substr(3,7));
       // std::cout<<x <<" "<< y <<" "<<std::endl;
        vertxs1.push_back(std::make_tuple( x, y ));
    }
    
    if(numberOfpolygon == 2)
    {
        int polygon2 = std::stoi(lines[4 + 4]);
        for(unsigned int i = 9; i < polygon2+9; i++)
        {
            float x1 = std::stof(lines[i].substr(0,3));
            float y1 = std::stof(lines[i].substr(3,7));
           // std::cout<<x1<<" "<<y1<<std::endl;
            vertxs2.push_back(std::make_tuple(x1,y1));
        }
    }
    
    polygons.push_back(Polygon(vertxs1, Lenght, height));
    polygons.push_back(Polygon(vertxs2, Lenght, height));
    
}

