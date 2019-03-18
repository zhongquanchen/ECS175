//
//  FileProcessor.hpp
//  project3-1
//
//  Created by Oscar on 2018/11/25.
//  Copyright © 2018 Oscar. All rights reserved.
//

#ifndef FileProcessor_hpp
#define FileProcessor_hpp

#include "Object.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>

class FileProcessor{
public:
    FileProcessor();
    void Addline();
    void WriteFile();
    
    std::vector<Vec3> vertxs1;
    std::vector<std::vector<int>> faces;
    
    std::vector<Object> objects;
    std::vector<std::vector<float>> Normals;
};

#endif /* FileProcessor_hpp */
