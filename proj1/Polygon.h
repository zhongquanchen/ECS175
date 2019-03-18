//
//  Vertices.h
//  play
//
//  Created by Oscar on 2018/10/17.
//  Copyright © 2018年 Oscar. All rights reserved.
//

#ifndef Polygon_h
#define Polygon_h

#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<tuple>

class Polygon{
public:
    Polygon(std::vector<std::tuple<float, float>> array, int Lenght, int Height);
    
    void DrawPixel(float* PixelBuffer, int chooseOfAlgorithm);
    void ConvertCoordinateToPoint();
    void DigitalDifferential(float x1, float y1, float x2, float y2, float* PixelBuffer);
    void BresenHam(float x1, float y1, float x2, float y2, float* PixelBuffer);
    int GetLineCoordinateToIndex(float x, float y, int val, float slope);
    int GetLineCoordinateToIndexBresenham(float x, float y, int val, float slope);
    void Rasterzing(float* Pixel);
    void FindMinMax();
    void FindHorizontal(float* Pixel);
    //Transform
    void Scalling( int scalx, int scaly);
    void Rotation( double degree);
    void Translation( float vec1, float vec2);
    
    void DebugDrawLine(float* PixelBuffer);
    
public:
    std::vector<std::tuple<float, float>> coordinates;
    std::vector<std::tuple<int, int>> Points;
    std::vector<std::tuple<int, int>> edges;
    std::vector<std::tuple<float, float, float, float>> horizontal;
    int mHeight;
    int mLength;
    
    int maxHeight = 0.0f;
    int minHeight = 1000.0f;
    int maxWeight = 0.0f;
    int minWeight = 1000.0f;
};


#endif /* Vertices_h */
