//
//  Object.cpp
//  project3-1
//
//  Created by Oscar on 2018/11/25.
//  Copyright © 2018 Oscar. All rights reserved.
//

#include "Object.hpp"


Object::Object(const std::vector<Vec3>& coordinates, const std::vector<std::vector<int>>& face, const std::vector<std::vector<float>>& normals)
{
    for(auto a : coordinates)
    {
        Coordinates.push_back(a);
    }
    for(auto b : face)
    {
        faces.push_back(b);
        
    }
    for(auto b : normals)
    {
        float x = b[0];
        float y = b[1];
        float z = b[2];
       // std::cout<<" x "<<x<<" y "<<y<<" z "<<z<<std::endl;
        this->Normals.push_back(std::make_tuple(x,y,z));
    }
   // ConvertCoordinateTo2D();
    InitPhongData();
    PainterAlgoXY();
    PainterAlgoYZ();
    PainterAlgoXZ();
    
    ConvertToXYCoords();
    ConvertToXZCoords();
    ConvertToYZCoords();

    //CalculateNormal();
    CalculateIntensity();
    
    
}
void Object::PainterAlgoXY()
{
   // std::cout<<"  enter XY "<<std::endl;
    int X = 2;
    for(unsigned int i=0; i<faces.size(); i++)
    {
        for(unsigned int j=0; j<faces.size()-1-i; j++)
        {
            float a1 = FindMinimum(faces[j], X);
            float a2 = FindMinimum(faces[j+1], X);
            if(a1 > a2)
            {
                auto temp = faces[j+1];
                faces[j+1] = faces[j];
                faces[j] = temp;
              //  std::cout<<"entered swapping "<<std::endl;
            }
        }
    }
    
    for(auto a:faces)
    {
    //    std::cout<<" a is "<<a[0]<<"  "<<a[1]<<" "<<a[2]<<std::endl;
        XYfaces.push_back(a);
    }
    
}

float Object::FindMinimum(std::vector<int>& face, int X)
{
    float biggest = 0;
    
    for(unsigned int i=0; i<face.size(); i++)
    {
        std::vector<float> temp;
        float x = std::get<0>(Coordinates[face[i]]);
        float y = std::get<1>(Coordinates[face[i]]);
        float z = std::get<2>(Coordinates[face[i]]);
        temp.push_back(x);
        temp.push_back(y);
        temp.push_back(z);
        if( temp[X] > biggest )
        {
            biggest = temp[X];
        }
    }
 //   std::cout<<" face "<<face[0]<<" "<<face[1]<<" "<<face[2]<<std::endl;
 //   std::cout<<biggest<<std::endl;
    return biggest;
}

void Object::PainterAlgoXZ()
{
 //   std::cout<<"  enter XZ "<<std::endl;
    int X = 1;
    for(unsigned int i=0; i<faces.size(); i++)
    {
        for(unsigned int j=0; j<faces.size()-1-i; j++)
        {
            float a1 = FindMinimum(faces[j], X);
            float a2 = FindMinimum(faces[j+1], X);
            if(a1 > a2)
            {
                auto temp = faces[j+1];
                faces[j+1] = faces[j];
                faces[j] = temp;
            }
        }
    }
    
    for(auto a:faces)
    {
    //    std::cout<<" a is "<<a[0]<<"  "<<a[1]<<" "<<a[2]<<std::endl;
        XZfaces.push_back(a);
    }
}
void Object::PainterAlgoYZ()
{
  //  std::cout<<"  enter YZ "<<std::endl;
    int X = 0;
    for(unsigned int i=0; i<faces.size(); i++)
    {
        for(unsigned int j=0; j<faces.size()-1-i; j++)
        {
            float a1 = FindMinimum(faces[j], X);
            float a2 = FindMinimum(faces[j+1], X);
            if(a1 > a2)
            {
                auto temp = faces[j+1];
                faces[j+1] = faces[j];
                faces[j] = temp;
            }
        }
    }
    
    for(auto a:faces)
    {
   //     std::cout<<" a is "<<a[0]<<"  "<<a[1]<<" "<<a[2]<<std::endl;
        YZfaces.push_back(a);
    }
}

void Object::CalculateIntensity()
{
    for(unsigned int i=0; i<Coordinates.size(); i++)
    {
        Vec3 Ip = ComputeIp( ka, kd, ks, K, n, x, f,I_a, I_L, Coordinates[i], Normals[i]);
        Intensities.push_back(Ip);
    }
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
        CoordinateOn2D.push_back(std::make_tuple((x+x1)/300.0,(y+y1)/300.0 ));
    }
}

void Object::ConvertToXYCoords()
{
    XYCoords.clear();
    for(auto a : Coordinates)
    {
        float x = std::get<0>(a);
        float y = std::get<1>(a);
        XYCoords.push_back(std::make_tuple(x/300.0 - 1,y/300.0));
    }
}

void Object::ConvertToYZCoords()
{
    YZCoords.clear();
    for(auto a : Coordinates)
    {
        float y = std::get<1>(a);
        float z = std::get<2>(a);
        YZCoords.push_back(std::make_tuple(y/300.0 -1,z/300.0 -1));
    }
}
void Object::ConvertToXZCoords()
{
    XZCoords.clear();
    for(auto a : Coordinates)
    {
        float x = std::get<0>(a);
        float z = std::get<2>(a);
        XZCoords.push_back(std::make_tuple(x/300.0,z/300.0));
    }
}

void Object::UpdateAll()
{
    ConvertCoordinateTo2D();
    ConvertToXYCoords();
    ConvertToXZCoords();
    ConvertToYZCoords();
}

void Object::DrawItSelt()
{

    for(unsigned int i=0; i<faces.size(); i++)
    {
    //    ConnectPointsXY(XYfaces[i], i);
    //    ConnectPointsXZ(XZfaces[i], i);
    //    ConnectPointsYZ(YZfaces[i], i);
        Rasterzition(XYfaces[i], XYCoords, i);
        Rasterzition(XZfaces[i], XZCoords, i);
        Rasterzition(YZfaces[i], YZCoords, i);
    }
    
}

void Object::ConnectPointsXY(const std::vector<int>& oneface, int level)
{

    unsigned int i=1;
    for(; i<oneface.size(); i++)
    {
        DrawXY(i, i-1, level);
    }
    DrawXY(oneface.size()-1, 0, level);

}

void Object::ConnectPointsXZ(const std::vector<int>& oneface, int level)
{
    
    unsigned int i=1;
    for(; i<oneface.size(); i++)
    {
        DrawXZ(i, i-1, level);
    }
    DrawXZ(oneface.size()-1, 0, level);
    
}

void Object::ConnectPointsYZ(const std::vector<int>& oneface, int level)
{
    
    unsigned int i=1;
    for(; i<oneface.size(); i++)
    {
        DrawYZ(i, i-1, level);
    }
    DrawYZ(oneface.size()-1, 0, level);
    
}

void Object::DrawAll(int point1, int point2, int level)
{
  //  DrawLine(point1, point2);
    DrawXY(point1, point2, level);
    DrawXZ(point1, point2, level);
    DrawYZ(point1, point2, level);
}

void Object::DrawLine(Vec2 point1, Vec2 point2, int a, int b, int level)
{
    std::map<float, float> world;
    float dx, dy, x1,y1,x2,y2;

    x1 = std::get<0>(point1);
    y1 = std::get<1>(point1);
    x2 = std::get<0>(point2);
    y2 = std::get<1>(point2);


  //  std::cout<<" x1 "<<x1<<" y1 "<<y1<<" x2 "<<x2<<" y2 "<<y2<<std::endl;
    dx = (x2 - x1);
    dy = (y2 - y1);
    float slope = dy/dx;
    float constant = y1 - slope * x1;
  //  std::cout<<"y = "<<slope<<"x"<<" + "<<constant<<std::endl;
    
    glBegin(GL_POINTS);
    if( slope >=-1 && slope <= 1 )
    {
        if(x1 < x2)
        {
            for(float i = 0; i <= x2-x1; i+=0.003)
            {
                float x = x1 + i;
                float y = x * slope + constant;
                Vec2 point3 = std::make_tuple(x,y);
                
                Vec3 Ip = Intensity(point1, point2, point3, a, b);
                glColor3f(std::get<0>(Ip), std::get<1>(Ip), std::get<2>(Ip));
                glVertex3f(x, y, 0);
                
           //     world.insert(std::pair<float,float>(y,x));
            
            }
       //     this->interpoints.push_back(world);

        }
        else
        {
            for(float i=0; i<x2-x1; i-=0.003)
            {
                float x = x1 + i;
                float y = x * slope + constant;
                Vec2 point3 = std::make_tuple(x,y);
                Vec3 Ip = Intensity(point1, point2, point3, a, b);
                
                glColor3f(std::get<0>(Ip), std::get<1>(Ip), std::get<2>(Ip));
                glVertex3f(x, y, 0);
                
         //       world.insert(std::pair<float,float>(y,x));
            }
         //   this->interpoints.push_back(world);
        }
    }
    else{
        if(y2 > y1)
        {
            for(float i=0; i<abs(y2-y1); i+=0.003)
            {
                float y = y1 + i;
                float x = (y-constant)/slope;
                Vec2 point3 = std::make_tuple(x,y);
                Vec3 Ip = Intensity(point1, point2, point3, a, b);
                
                glColor3f(std::get<0>(Ip), std::get<1>(Ip), std::get<2>(Ip));
                glVertex3f(x, y, 0);
                
        //        world.insert(std::pair<float,float>(y,x));
            }
        //    this->interpoints.push_back(world);
        }
        else
        {
            for(float i=0; i<y2-y1; i-=0.003)
            {
                float y = y1 + i;
                float x = (y-constant)/slope;
                Vec2 point3 = std::make_tuple(x,y);
                Vec3 Ip = Intensity(point1, point2, point3, a, b);
                
                glColor3f(std::get<0>(Ip), std::get<1>(Ip), std::get<2>(Ip));
                glColor3f(1.0f, 1.0f, 1.0f); //pink color
                glVertex3f(x, y, 0);
                
          //      world.insert(std::pair<float,float>(y,x));
            }
         //   this->interpoints.push_back(world);
        }
    }
    glEnd();
}

Vec3 Object::Intensity(Vec2 point1, Vec2 point2, Vec2 point3, int a, int b)
{

    float y1,y2,ys;
    if(std::get<1>(point1) > std::get<1>(point2))
    {
        y1 = std::get<1>(point1);
        y2 = std::get<1>(point2);
        ys = std::get<1>(point3);
    }
    else
    {
        y1 = std::get<1>(point2);
        y2 = std::get<1>(point1);
        ys = std::get<1>(point3);
    }
    float I1_r = std::get<0>(Intensities[a]);
    float I1_g = std::get<1>(Intensities[a]);
    float I1_b = std::get<2>(Intensities[a]);
    
    float I2_r = std::get<0>(Intensities[b]);
    float I2_g = std::get<1>(Intensities[b]);
    float I2_b = std::get<2>(Intensities[b]);
    
    float I_r = (I1_r * (ys - y2) + I2_r * (y1 - ys)) / (y1 - y2);
    float I_g = (I1_g * (ys - y2) + I2_g * (y1 - ys)) / (y1 - y2);
    float I_b = (I1_b * (ys - y2) + I2_b * (y1 - ys)) / (y1 - y2);
    
    return std::make_tuple(I_r, I_g, I_b);

}

void Object::DrawXY(int point1, int point2, int level)
{
    Vec2 vertex1 = XYCoords[XYfaces[level][point1]];
    Vec2 vertex2 = XYCoords[XYfaces[level][point2]];
    DrawLine(vertex1, vertex2, point1, point2, level);

}

void Object::DrawXZ(int point1, int point2, int level)
{
    Vec2 vertex1 = XZCoords[XZfaces[level][point1]];
    Vec2 vertex2 = XZCoords[XZfaces[level][point2]];
    DrawLine(vertex1, vertex2, point1, point2, level);

}

void Object::DrawYZ(int point1, int point2, int level)
{
    Vec2 vertex1 = YZCoords[YZfaces[level][point1]];
    Vec2 vertex2 = YZCoords[YZfaces[level][point2]];
    DrawLine(vertex1, vertex2, point1, point2, level);
}

void Object::Rasterzition(const std::vector<int>& oneface, const std::vector<Vec2>& coords, int level)
{
    float minX = 100.0;
    float maxX = -99.0;
    float minY = 100.0;
    float maxY = -99.0;
    for(unsigned int i=0; i<oneface.size(); i++)
    {
        if(std::get<0>(coords[oneface[i]]) > maxX)
        {
            maxX = std::get<0>(coords[oneface[i]]);
        }
        if(std::get<0>(coords[oneface[i]]) < minX)
        {
            minX = std::get<0>(coords[oneface[i]]);
        }
        if(std::get<1>(coords[oneface[i]]) < minY)
        {
            minY = std::get<1>(coords[oneface[i]]);
        }
        if(std::get<1>(coords[oneface[i]]) > maxY)
        {
            maxY = std::get<1>(coords[oneface[i]]);
        }
    }
    
    for(float i = minX; i<maxX; i+=0.003)
    {
        for(float j = minY; j<maxY; j+=0.003)
        {
            Vec2 testpoint = std::make_tuple(i,j);

            if(Inside(testpoint, oneface, coords))
            {
              //  std::cout<<" testpoint x "<<std::get<0>(testpoint)<<" y "<<std::get<1>(testpoint)<<std::endl;
               Vec3 Ip = RasterIntensity(oneface, coords, testpoint, level);
                glColor3f(std::get<0>(Ip), std::get<1>(Ip), std::get<2>(Ip)); //pink color
               // glColor3f(0, 0,1);
                glBegin(GL_POINTS);
                glVertex2f(std::get<0>(testpoint), std::get<1>(testpoint));
                glEnd();//end drawing of polygon
            }
        }
    }
}

Vec3 Object::RasterIntensity(const std::vector<int>& oneface, const std::vector<Vec2>& coords, Vec2& testpoint, int level)
{
    std::vector<Vec5> intersec = Scanline1(oneface, coords, testpoint);
    
    if(intersec.size() == 0)
    {
        return std::make_tuple(0,0,0);
    }
    else if(intersec.size() == 1)
    {
        return std::make_tuple(0,0,0);
    }
    else{
        Vec3 Ip = Intensity3d(intersec, testpoint, coords);
      //  std::cout<<" ip r "<<std::get<0>(Ip)<<" g "<<std::get<1>(Ip)<<" b "<<std::get<2>(Ip)<<std::endl;
        return Ip;
    }

}

Vec3 Object::Intensity3d(std::vector<Vec5> intersec, Vec2 xp,const std::vector<Vec2>& coords)
{
    int point1 = std::get<1>(intersec[0]);
    int point2 = std::get<2>(intersec[0]);
    
    int point3 = std::get<1>(intersec[1]);
    int point4 = std::get<2>(intersec[1]);
    
    Vec2 xa = std::get<0>(intersec[0]);
    Vec2 xb = std::get<0>(intersec[1]);
    
    float x1, x2;
    
    if(std::get<0>(xa) > std::get<0>(xb))
    {
        x2 = std::get<0>(xa);
        x1 = std::get<0>(xb);
    }
    else
    {
        x1 = std::get<0>(xa);
        x2 = std::get<0>(xb);
    }
    
    Vec3 Ia = Intensity(coords[point1], coords[point2], xp, point1, point2);
    Vec3 Ib = Intensity(coords[point3], coords[point4], xp, point3, point4);
    
    float Ia_r = std::get<0>(Ia);
    float Ia_g = std::get<1>(Ia);
    float Ia_b = std::get<2>(Ia);
    
    float Ib_r = std::get<0>(Ib);
    float Ib_g = std::get<1>(Ib);
    float Ib_b = std::get<2>(Ib);
 
    float Ip_r = (Ia_r * (x2 - std::get<0>(xp)) + Ib_r * (std::get<0>(xp) - x1)) / ( x2 - x1 );
    float Ip_g = (Ia_g * (x2 - std::get<0>(xp)) + Ib_g * (std::get<0>(xp) - x1)) / ( x2 - x1 );
    float Ip_b = (Ia_b * (x2 - std::get<0>(xp)) + Ib_b * (std::get<0>(xp) - x1)) / ( x2 - x1 );
    
    return std::make_tuple(Ip_r, Ip_g, Ip_b);
}

std::vector<Vec5> Object::Scanline1(const std::vector<int> &oneface, const std::vector<Vec2> &coords, Vec2 &testpoint)
{
    std::vector<Vec5> intersec;
    float minX = 100.0;
    float maxX = -99.0;
    float minY = 100.0;
    float maxY = -99.0;
    for(unsigned int i=0; i<oneface.size(); i++)
    {
        if(std::get<0>(coords[oneface[i]]) > maxX)
        {
            maxX = std::get<0>(coords[oneface[i]]);
        }
        if(std::get<0>(coords[oneface[i]]) < minX)
        {
            minX = std::get<0>(coords[oneface[i]]);
        }
        if(std::get<1>(coords[oneface[i]]) < minY)
        {
            minY = std::get<1>(coords[oneface[i]]);
        }
        if(std::get<1>(coords[oneface[i]]) > maxY)
        {
            maxY = std::get<1>(coords[oneface[i]]);
        }
    }
    
        int point1 = oneface[0];
        int point2 = oneface[1];
        int point3 = oneface[2];
    
        Vec2 inter1 = EdgeFunction2(coords[point1], coords[point2], testpoint);
      //  float son1 = std::get<0>(inter1);
    
        Vec2 inter2 = EdgeFunction2(coords[point2], coords[point3], testpoint);
      //  float son2 = std::get<0>(inter2);
    
        Vec2 inter3 = EdgeFunction2(coords[point3], coords[point1], testpoint);
      //  float son3 = std::get<0>(inter3);
    
    std::vector<Vec2> mypoint;
    
    float x = std::get<0>(testpoint);
    float y = std::get<1>(testpoint);
    for(float i=x; i<=maxX; i+=0.003)
    {
        Vec2 point = std::make_tuple(i, y);
        if(!Inside(point, oneface, coords))
        {
            std::get<0>(point) = std::get<0>(point) - 0.003;
            mypoint.push_back(point);
            break;
        }
    }
    for(float i =x; i>=minX; i-=0.003)
    {
        Vec2 point = std::make_tuple(i, y);
        if(!Inside(point, oneface, coords))
        {
            std::get<0>(point) = std::get<0>(point) + 0.003;
            mypoint.push_back(point);
            break;
        }
    }
    if(mypoint.size() == 1)
    {
        return intersec;
    }
    else{
        float dis1 = DistanceCal(inter1, mypoint[0]);
        float dis2 = DistanceCal(inter2, mypoint[0]);
        float dis3 = DistanceCal(inter3, mypoint[0]);
        if(dis1 >= dis2)
        {
            if(dis2 > dis3)
            {
                //dis3 zuixiao
                intersec.push_back(std::make_tuple(mypoint[0], point3, point1));
            }else{
                //dis2 zuixiao
                intersec.push_back(std::make_tuple(mypoint[0], point2, point3));
            }
        }
        else
        {
            //dis1 < dis2
            if(dis1 >= dis3)
            {
                //dis3 zuixiao
                intersec.push_back(std::make_tuple(mypoint[0], point3, point1));
            }else{
                //dis1 zuixiao
                intersec.push_back(std::make_tuple(mypoint[0], point1, point2));
            }
        }
        
        float dis4 = DistanceCal(inter1, mypoint[1]);
        float dis5 = DistanceCal(inter2, mypoint[1]);
        float dis6 = DistanceCal(inter3, mypoint[1]);
        if(dis4 >= dis5)
        {
            if(dis5 > dis6)
            {
                //dis6 zuixiao
                intersec.push_back(std::make_tuple(mypoint[1], point3, point1));
            }else{
                //dis5 zuixiao
                intersec.push_back(std::make_tuple(mypoint[1], point2, point3));
            }
        }
        else
        {
            //dis4 < dis5
            if(dis4 >= dis6)
            {
                //dis6 zuixiao
                intersec.push_back(std::make_tuple(mypoint[1], point3, point1));
            }else{
                //dis4 zuixiao
                intersec.push_back(std::make_tuple(mypoint[1], point1, point2));
            }
        }
        return intersec;
    }
}

float Object::DistanceCal(Vec2 a, Vec2 b)
{
    float x1 = std::get<0>(a);
    float y1 = std::get<1>(a);
    
    float x2 = std::get<0>(b);
    float y2 = std::get<1>(b);
    
    float dx = x1 - x2;
    float dy = y1 - y2;
    float dis = sqrt(dx*dx + dy*dy);
    return dis;
}


Vec2 Object::EdgeFunction2(Vec2 a, Vec2 b, Vec2 c)
{
    float ax = std::get<0>(a);
    float ay = std::get<1>(a);
    
    float bx = std::get<0>(b);
    float by = std::get<1>(b);

    float cy = std::get<1>(c);

    //  std::cout<<" x1 "<<x1<<" y1 "<<y1<<" x2 "<<x2<<" y2 "<<y2<<std::endl;
    float dx = (ax - bx);
    float dy = (ay - by);
    float slope = dy/dx;
    float constant = ay - slope * ax;
    
    float cx = (cy - constant) / slope;
    return (std::make_tuple(cx,cy));
}

bool Object::Inside(Vec2 testpoint, const std::vector<int>& face, const std::vector<Vec2>& coords)
{
    bool inside = true;
    for(unsigned int i=1; i<face.size(); i++)
    {
        int point1 = face[i-1];
        int point2 = face[i];
        Vec2 a = coords[point1];
        Vec2 b = coords[point2];
        inside &= EdgeFunction(b, a, testpoint);
        
    }
    unsigned long point3 = face.size()-1;
    Vec2 c = coords[face[point3]];
    inside &= EdgeFunction(coords[face[0]],c, testpoint);
    
    return inside;
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage

//reference from upbove

bool Object::EdgeFunction(Vec2 a, Vec2 b, Vec2 c)
{
    return ((std::get<0>(c) - std::get<0>(a)) * (std::get<1>(b) - std::get<1>(a)) - (std::get<1>(c) - std::get<1>(a)) * (std::get<0>(b) - std::get<0>(a)) >= 0);
}


Vec3 Object::ComputeIp(Vec3 ka, Vec3 kd, Vec3 ks, float K, int n, Vec3 x, Vec3 f, float IA, float IL, Vec3 vertex, Vec3 normal)
{
    
    Vec3 Normal = normal;
    float lx = std::get<0>(x) - std::get<0>(vertex);
    float ly = std::get<1>(x) - std::get<1>(vertex);
    float lz = std::get<2>(x) - std::get<2>(vertex);
    float L = sqrt(lx*lx + ly*ly + lz*lz);
    Vec3 l = std::make_tuple(lx/L,ly/L,lz/L);
    
    float fx = std::get<0>(x) - std::get<0>(vertex);
    float fy = std::get<1>(x) - std::get<1>(vertex);
    float fz = std::get<2>(x) - std::get<2>(vertex);
    float F = sqrt(fx*fx + fy*fy + fz*fz);
    Vec3 v = std::make_tuple(fx/F,fy/F,fz/F);

    
    float nx = std::get<0>(normal);
    float ny = std::get<1>(normal);
    float nz = std::get<0>(normal);
    float n1 = sqrt(nx*nx + ny*ny + nz*nz);
    
    float n1x = nx/n1;
    float n1y = ny/n1;
    float n1z = nz/n1;
    Vec3 normalize = std::make_tuple(n1x,n1y,n1z);
    
    float NormalL_x = std::get<0>(l);
    float NormalL_y = std::get<1>(l);
    float NormalL_z = std::get<2>(l);
    float NormalL = sqrt(nx*nx + ny*ny + nz*nz);
    
    float L1x = NormalL_x/NormalL;
    float L1y = NormalL_y/NormalL;
    float L1z = NormalL_z/NormalL;
    Vec3 normalize_L = std::make_tuple(L1x,L1y,L1z);
    
    float dotproduct = std::get<0>(normalize)*std::get<0>(normalize_L) + std::get<1>(normalize)*std::get<1>(normalize_L) + std::get<2>(normalize)*std::get<2>(normalize_L);
    dotproduct*=2;
    std::get<0>(normalize) = std::get<0>(normalize) * dotproduct;
    std::get<1>(normalize) = std::get<1>(normalize) * dotproduct;
    std::get<2>(normalize) = std::get<2>(normalize) * dotproduct;
    float rx = std::get<0>(normalize) - std::get<0>(l) ;
    float ry = std::get<1>(normalize) - std::get<1>(l) ;
    float rz = std::get<2>(normalize) - std::get<2>(l) ;
    Vec3 r = std::make_tuple(rx,ry,rz);
    

    Vec3 Ip = IpFunction(ka, ks, IA, IL, f, vertex, K, kd, l, normal, r, v, n);
    if(std::get<0>(Ip) > 1.0)
    {
        std::get<0>(Ip) = 1.0;
    }
    if(std::get<1>(Ip) > 1.0)
    {
        std::get<1>(Ip) = 1.0;
    }
    if(std::get<2>(Ip) > 1.0)
    {
        std::get<2>(Ip) = 1.0;
    }
  //  std::cout<<"                Intensity r "<<std::get<0>(Ip)<<" g "<<std::get<1>(Ip)<<" b "<<std::get<2>(Ip)<<std::endl;
    return Ip;
}

Vec3 Object::IpFunction(Vec3 ka, Vec3 ks, float IA, float IL, Vec3 f, Vec3 p, float K, Vec3 kd, Vec3 l, Vec3 normal, Vec3 r, Vec3 v, int n)
{
    //1st part Ka * I_A
    float part1_r = std::get<0>(ka)*IA ;
    float part1_g = std::get<1>(ka)*IA ;
    float part1_b = std::get<2>(ka)*IA ;
    
    //2nd part IL/(..)
    float fx = std::get<0>(f) - std::get<0>(p);
    float fy = std::get<1>(f) - std::get<1>(p);
    float fz = std::get<2>(f) - std::get<2>(p);
    float F = sqrt(fx*fx + fy*fy + fz*fz);
    float part2 = IL / (F + K);

    
    //part3
    // Kd * (l . n)
    // Kd (1,0,0)
    float dot1 = std::get<0>(l)*std::get<0>(normal) + std::get<1>(l)*std::get<1>(normal) + std::get<2>(l)*std::get<2>(normal);
  //  std::cout<<"dot1 "<<dot1<<std::endl;
    
    float part3_r = std::get<0>(kd)*dot1 ;
    float part3_g = std::get<1>(kd)*dot1 ;
    float part3_b = std::get<2>(kd)*dot1 ;

    
    //part4
    //Ks (1,1,1)
    float dot2 = std::get<0>(r)*std::get<0>(v) + std::get<1>(r)*std::get<1>(v) + std::get<2>(r)*std::get<2>(v);
 //   std::cout<<"dot2 "<<dot2<<std::endl;
    
    dot2 = pow(dot2, n);
    float part4_r = std::get<0>(ks)*dot2 ;
    float part4_g = std::get<1>(ks)*dot2 ;
    float part4_b = std::get<2>(ks)*dot2 ;
    

    
    //part5 = part3 + part4
    float part5_r = part3_r + part4_r;
    float part5_g = part3_g + part4_g;
    float part5_b = part3_b + part4_b;
    
    if(part5_r < 0 || part5_g < 0 || part5_b <0 )
    {
        float part8_r = part1_r;
        float part8_g = part1_g;
        float part8_b = part1_b;
        return std::make_tuple(part8_r,part8_g,part8_b);
    }
    
    //part6 = part2 * part5
    float part6_r = part2 * part5_r;
    float part6_g = part2 * part5_g;
    float part6_b = part2 * part5_b;

    //part7 = part6 + part1
    float part7_r = part6_r + part1_r;
    float part7_g = part6_g + part1_g;
    float part7_b = part6_b + part1_b;

    return std::make_tuple(part7_r, part7_g, part7_b);
    
}

void Object::InitPhongData()
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
    std::string line = lines[0].substr(3);
    K = std::stof(line);
    
    line = lines[1].substr(3);
    n = std::stoi(line);
    
    line = lines[2].substr(5);
    I_L = std::stof(line);
    
    line = lines[4].substr(6);
    k_aR = std::stof(line);
    line = lines[5].substr(6);
    k_aG = std::stof(line);
    line = lines[6].substr(6);
    k_aB = std::stof(line);
    ka = std::make_tuple(k_aR, k_aG, k_aB);
    
    line = lines[9].substr(5);
    I_a = std::stof(line);
    
    line = lines[11].substr(6);
    k_dR = std::stof(line);
    line = lines[12].substr(6);
    k_dG = std::stof(line);
    line = lines[13].substr(6);
    k_dB = std::stof(line);
    kd = std::make_tuple(k_dR, k_dG, k_dB);
    
    line = lines[16].substr(6);
    k_sR = std::stof(line);
    line = lines[17].substr(6);
    k_sG = std::stof(line);
    line = lines[18].substr(6);
    k_sB = std::stof(line);
    ks = std::make_tuple(k_sR, k_sG, k_sB);
    
    line = lines[22].substr(5);
    ffX = std::stof(line);
    line = lines[23].substr(5);
    ffY = std::stof(line);
    line = lines[24].substr(5);
    ffZ = std::stof(line);
    f = std::make_tuple(ffX, ffY, ffZ);
    
    line = lines[28].substr(4);
    xX = std::stof(line);
    line = lines[29].substr(4);
    xY = std::stof(line);
    line = lines[30].substr(4);
    xZ = std::stof(line);
    x = std::make_tuple(xX, xY, xZ);
    
}


