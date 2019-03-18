//
//  FileProcesser.h
//  play
//
//  Created by Oscar on 2018/10/17.
//  Copyright © 2018年 Oscar. All rights reserved.
//

#ifndef FileProcessor_h
#define FileProcessor_h

#include "Polygon.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

class FileProcessor{
    
public:
    void Addline(int Lenght, int height);
    
    std::vector<std::tuple<float, float>> vertxs1;
    std::vector<std::tuple<float, float>> vertxs2;
    
    std::vector<Polygon> polygons;
};

#endif /* FileProcesser_h */
