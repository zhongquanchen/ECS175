//
//  FileProcesser.h
//  play
//
//  Created by Oscar on 2018/10/17.
//  Copyright © 2018年 Oscar. All rights reserved.
//

#ifndef FileProcessor_h
#define FileProcessor_h

#include "Object.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

class FileProcessor{
public:
    FileProcessor();
    void Addline();
    void WriteFile();
    
    std::vector<Vec3> vertxs1;
    std::vector<Vec2> edges;

    std::vector<Object> objects;
    
};

#endif /* FileProcesser_h */
