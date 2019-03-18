//
//  Object.hpp
//  project3-1
//
//  Created by Oscar on 2018/11/25.
//  Copyright © 2018 Oscar. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp
#include <GLUT/glut.h>
#include <vector>
#include <tuple>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cmath>
#include <map>
#define PI 3.1415926

using Vec3 = std::tuple<float, float, float>;
using Vec2 = std::tuple<float, float>;
using Vec5 = std::tuple<Vec2, int, int>;

class Object{
    
public:

    void WriteFile(std::string filename);
   // void CovertFace();
    
    //--------------------------------------------------------------------------------
    //this part is to draw the object
    void DrawItSelt();
    void DrawYZ(int point1, int point2, int level);
    void DrawXY(int point1, int point2, int level);
    void DrawXZ(int point1, int point2, int level);
    void DrawAll(int point1, int point2,int level);
    void DrawLine(Vec2 point1, Vec2 point2, int a, int b, int level);

    void ConnectPoints(const std::vector<int>& oneface, int level);
    void ConnectPointsXY(const std::vector<int>& oneface, int level);
    void ConnectPointsXZ(const std::vector<int>& oneface, int level);
    void ConnectPointsYZ(const std::vector<int>& oneface, int level);
    //--------------------------------------------------------------------------------
    
    
    //--------------------------------------------------------------------------------
    //this part is to calculate the phong intensity and rasterize the object
    Vec3 Intensity(Vec2 point1, Vec2 point2, Vec2 point3, int a, int b);
    Vec3 Intensity3d(std::vector<Vec5> intersec,Vec2 xp, const std::vector<Vec2>& coords);
    
    void Rasterzition(const std::vector<int>& oneface, const std::vector<Vec2>& coors, int level);
    void Rasterzition1(const std::vector<int>& oneface, const std::vector<Vec2>& coors, int level);
    bool Inside(Vec2 testpoint, const std::vector<int>& face, const std::vector<Vec2>& coords);
    
    bool EdgeFunction(Vec2 a, Vec2 b, Vec2 c);
    Vec2 EdgeFunction2(Vec2 a, Vec2 b, Vec2 c);
    
    Vec3 RasterIntensity(const std::vector<int>& oneface, const std::vector<Vec2>& coords, Vec2& testpoint, int level);
    std::vector<Vec5> Scanline1(const std::vector<int> &oneface, const std::vector<Vec2> &coords, Vec2 &testpoint);
    float DistanceCal(Vec2 a, Vec2 b);

    Vec3 ComputeIp(Vec3 ka, Vec3 kd, Vec3 ks, float K, int n, Vec3 x, Vec3 f, float IA, float IL, Vec3 vertex, Vec3 normal);
    Vec3 IpFunction(Vec3 ka, Vec3 ks, float IA, float IL, Vec3 f, Vec3 p, float K, Vec3 kd, Vec3 l, Vec3 normal, Vec3 r, Vec3 v, int n);
    
    void CalculateIntensity();

    //--------------------------------------------------------------------------------
    //this part is to implement the painter algo. sort the faces
    void PainterAlgoXY();
    void PainterAlgoXZ();
    void PainterAlgoYZ();
    float FindMinimum(std::vector<int>& face, int X);
    
    
    //--------------------------------------------------------------------------------
    //Constructor
public:
    Object(const std::vector<Vec3>& coordinates, const std::vector<std::vector<int>>& face, const std::vector<std::vector<float>>& normals);
    Object() = default;
    
    void ConvertCoordinateTo2D();
    void ConvertToXYCoords();
    void ConvertToYZCoords();
    void ConvertToXZCoords();
    void UpdateAll();
    
    void InitPhongData();
    
   // int minX,maxX,minY,maxY,minZ,maxZ;
    
    std::vector<Vec3> Coordinates;
    std::vector<Vec2> CoordinateOn2D;
    std::vector<Vec3> OutputCoords;
    
    std::vector<Vec2> XYCoords;
    std::vector<Vec2> XZCoords;
    std::vector<Vec2> YZCoords;
    
    std::vector<std::vector<int>> faces;
    std::vector<std::vector<int>> XYfaces;
    std::vector<std::vector<int>> XZfaces;
    std::vector<std::vector<int>> YZfaces;
    
    
    std::vector<Vec3> NormalsPerFace;
    
    std::vector<Vec3> Normals;
    std::vector<Vec3> Normalizes;
    
    std::vector<Vec3> Intensities;
    
  //  std::vector<std::map<float, float>> interpoints;
    
    float K;
    int n;
    float I_L;
    
    float k_aR ;
    float k_aG ;
    float k_aB ;
    Vec3 ka = std::make_tuple(k_aR, k_aG, k_aB);
    
    float I_a ;
    
    float k_dR;
    float k_dG ;
    float k_dB ;
    Vec3 kd = std::make_tuple(k_dR, k_dG, k_dB);
    
    float k_sR ;
    float k_sG ;
    float k_sB ;
    Vec3 ks = std::make_tuple(k_sR, k_sG, k_sB);
    
    float ffX ;
    float ffY ;
    float ffZ ;
    Vec3 f = std::make_tuple(ffX, ffY, ffZ);
    
    float xX ;
    float xY ;
    float xZ ;
    Vec3 x = std::make_tuple(xX, xY, xZ);
    

};


#endif /* Object_hpp */
