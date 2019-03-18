//
//  Object.h
//  project2
//
//  Created by Oscar on 2018/10/24.
//  Copyright © 2018年 Oscar. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <vector>
#include <tuple>
#include <string>
#include <cmath>
#include <fstream>
#define PI 3.1415926

using Vec3 = std::tuple<float, float, float>;
using Vec2 = std::tuple<float, float>;

class Object{

public:
    void Translate(float x, float y, float z);
    void Rotation(std::string plane, float angle);
    void Scale(float factor);
    void WriteFile(std::string filename);
    
public:
    Object(std::vector<Vec3> coordinates, std::vector<Vec2> edge);
    Object() = default;
    void ConvertCoordinateTo2D();
    void ConvertToXYCoords();
    void ConvertToYZCoords();
    void ConvertToXZCoords();
    void UpdateAll();
    
    std::vector<Vec3> Coordinates;
    std::vector<Vec2> CoordinateOn2D;
    std::vector<Vec3> OutputCoords;
    
    std::vector<Vec2> XYCoords;
    std::vector<Vec2> XZCoords;
    std::vector<Vec2> YZCoords;
    
    std::vector<Vec2> edges;
    int minX,maxX,minY,maxY,minZ,maxZ;
    
};


#endif /* Object_h */
