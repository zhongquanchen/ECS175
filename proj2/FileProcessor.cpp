//
//  ReadFile.cpp
//  play
//
//  Created by Oscar on 2018/10/17.
//  Copyright © 2018年 Oscar. All rights reserved.
//

#include "FileProcessor.h"

FileProcessor::FileProcessor(){
    Addline();
}

void FileProcessor::Addline()
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
    int numobject = std::stoi(lines[0]);
    int counter = 2;
    for(int i =0; i<numobject; i++)
    {
        int polygon = std::stoi(lines[counter]);
        counter++;
        for(int j=counter; j<polygon+counter; j++)
        {
            float x = std::stof(lines[j].substr(0,3));
            float y = std::stof(lines[j].substr(3,7));
            float z = std::stof(lines[j].substr(7,11));
            vertxs1.push_back(std::make_tuple(x,y,z));
        }
        counter+=polygon;
        int edge = std::stoi(lines[counter]);
        counter++;
        for(int j=counter; j<edge+counter; j++)
        {
            int line1 = std::stoi(lines[j].substr(0,1));
            int line2 = std::stoi(lines[j].substr(1,3));
            edges.push_back(std::make_tuple(line1, line2));
        }
        counter +=edge;
        objects.push_back(Object(vertxs1, edges));
        vertxs1.clear();
        edges.clear();
    }
}

void FileProcessor::WriteFile()
{
    std::cout<<"Saving to output file..."<<std::endl;
    std::ofstream File("output.txt");
    if(!File)
    {
        std::cout<<"Fail to open output.txt"<<std::endl;
    }
    File<<objects.size()<<"\n";
    File<<"\n";
    for(auto a : objects)
    {
        File << a.Coordinates.size()<<"\n";
        for(auto b : a.Coordinates)
        {
            File<<std::get<0>(b)<<" "<<std::get<1>(b)<<" "<<std::get<2>(b)<<"\n";
        }
        File << a.edges.size()<<"\n";
        for(auto c : a.edges)
        {
            File<<std::get<0>(c)<<" "<<std::get<1>(c)<<"\n";
        }
        File<<"\n";
        
    }
    File.close();
    std::cout<<"Save complete.. exiting now"<<std::endl;
    exit(0);
}

