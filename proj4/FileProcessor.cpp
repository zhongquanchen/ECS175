//
//  FileProcessor.cpp
//  project3-1
//
//  Created by Oscar on 2018/11/25.
//  Copyright © 2018 Oscar. All rights reserved.
//

#include "FileProcessor.hpp"


FileProcessor::FileProcessor(){
    Addline();
}

void FileProcessor::Addline()
{
    std::ifstream ReadFile("data2.txt");
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
       // std::cout<<" numobject "<<numobject<<std::endl;
        int polygon = std::stoi(lines[counter]);
        counter++;
        for(int j=counter; j<polygon+counter; j++)
        {
            std::stringstream s(lines[j]);
            std::string word;
            std::vector<float> coors;
            while(s >> word)
            {
                coors.push_back(std::stof(word));
            }
            vertxs1.push_back(std::make_tuple(coors[0],coors[1],coors[2]));
            coors.clear();
        }
        counter+=polygon;
        
        int face = std::stoi(lines[counter]);
        counter++;
        for(int j=counter; j<face+counter; j++)
        {
            std::stringstream st(lines[j]);
            std::string words;
            std::vector<int> face;
            while(st >> words)
            {
                face.push_back(std::stoi(words));
            }
            faces.push_back(face);
            face.clear();
        }
        counter +=face;
        
        int normals = std::stoi(lines[counter]);
        counter++;
      //  std::cout<<"counter"<<counter<<std::endl;
        for(int j=counter; j<normals+counter; j++)
        {
            std::stringstream st(lines[j]);
            std::string words;
            std::vector<float> normals;
            while(st >> words)
            {
                normals.push_back(std::stof(words));
            }
            Normals.push_back(normals);
            normals.clear();
        }
        counter +=normals;
        counter++;
        
        objects.push_back(Object(vertxs1, faces, Normals));
        vertxs1.clear();
        this->faces.clear();
    }
}
/*
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
 */

