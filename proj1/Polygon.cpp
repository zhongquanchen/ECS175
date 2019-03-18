//
//  Vertices.cpp
//  play
//
//  Created by Oscar on 2018/10/17.
//  Copyright © 2018年 Oscar. All rights reserved.
//

#include "Polygon.h"

#define PI 3.1415926

Polygon::Polygon(std::vector<std::tuple<float, float>> array, int Lenght, int Height)
{
    for(auto i : array)
    {
        coordinates.push_back(i);
    }
    mLength = Lenght;
    mHeight = Height;
    ConvertCoordinateToPoint();
    FindMinMax();
}

void Polygon::ConvertCoordinateToPoint()
{
    Points.clear();
    for(auto i:coordinates)
    {
        int mx = (mLength/10) * std::get<0>(i) + mLength/2;
        int my = (mHeight/10) * std::get<1>(i) + mHeight/2;
        Points.push_back(std::make_tuple(mx, my));
    }
}

void Polygon::DrawPixel(float* PixelBuffer, int chooseOfAlgorithm)
{
    if(chooseOfAlgorithm == 1)
    {
        unsigned int i =1;
        for(; i < Points.size(); i++)
        {
            DigitalDifferential(std::get<0>(Points[i-1]), std::get<1>(Points[i-1]), std::get<0>(Points[i]), std::get<1>(Points[i]), PixelBuffer);
        }
        DigitalDifferential(std::get<0>(Points[0]), std::get<1>(Points[0]), std::get<0>(Points[i-1]), std::get<1>(Points[i-1]), PixelBuffer);
    }
    else{
        unsigned int i =1;
        for(; i < Points.size(); i++)
        {
            BresenHam(std::get<0>(Points[i-1]), std::get<1>(Points[i-1]), std::get<0>(Points[i]), std::get<1>(Points[i]), PixelBuffer);
        }
        BresenHam(std::get<0>(Points[0]), std::get<1>(Points[0]), std::get<0>(Points[i-1]), std::get<1>(Points[i-1]), PixelBuffer);
    }
    FindHorizontal(PixelBuffer);
}

void Polygon::DigitalDifferential(float x1, float y1, float x2, float y2, float* PixelBuffer)
{
    float slope = (y2-y1)/(x2-x1);
    if( slope <= 1 && slope >= -1 )
    {
        if(x1 < x2)
        {
            for(unsigned int i = 0; i <= x2-x1; i++)
            {
                int index = GetLineCoordinateToIndex( x1, y1, i, slope );
                //     std::cout<<"index is : "<<index <<std::endl;
                PixelBuffer[index] = 255;
                //std::cout<<"Index : "<<index<<" ";
            }
        }
        else
        {
            for(unsigned int i = 0; i >= x2-x1; i--)
            {
                int index = GetLineCoordinateToIndex( x1, y1, i, slope );
                //     std::cout<<"index is : "<<index <<std::endl;
                PixelBuffer[index] = 255;
                //std::cout<<"Index : "<<index<<" ";
            }
        }
    }
    else{
        if(y2 > y1)
        {
            for(unsigned int i=0; i <= y2-y1; i++)
            {
                int index = GetLineCoordinateToIndex(x1, y1, i, slope);
                PixelBuffer[index] = 255;
                //std::cout<<"Index : "<<index<<" ";
            }
        }
        else{
            for(unsigned int i=0; i >= y2-y1; i--)
            {
                int index = GetLineCoordinateToIndex(x1, y1, i, slope);
                PixelBuffer[index] = 255;
                //std::cout<<"Index : "<<index<<" ";
            }
        }
    }
}

int Polygon::GetLineCoordinateToIndex(float x, float y, int val, float slope)
{
    int index = 0;
    if(slope <= 1 && slope >= -1)
    {
        float y_new = slope * val + y;
        int y_aix = 0;
        if(y_new + 0.5 >= y+1)
        {
            y_aix = ceil(y_new);
        }
        else
        {
            y_aix = floor(y_new);
        }
        index = y_aix * mHeight + val + x;
    }
    else
    {
        float x_new = 1 / slope * val + x;
        int x_aix = 0;
        if(x_new + 0.5 >= y+1)
        {
            x_aix = ceil(x_new);
        }
        else
        {
            x_aix = floor(x_new);
        }
        index = (val + y) * mHeight + x_aix;
    }
    return index;
}

void Polygon::BresenHam(float x1, float y1, float x2, float y2, float* PixelBuffer)
{
    float slope = (y2-y1)/(x2-x1);
    if( slope <= 1 && slope >= -1 )
    {
        if(x1 < x2)
        {
            for(unsigned int i = 0; i <= x2-x1; i++)
            {
                int index = GetLineCoordinateToIndexBresenham( x1, y1, i, slope );
                //     std::cout<<"index is : "<<index <<std::endl;
                PixelBuffer[index] = 255;
            }
        }
        else
        {
            for(int i = 0; i >= x2-x1; i--)
            {
                int index = GetLineCoordinateToIndexBresenham( x1, y1, i, slope );
                //     std::cout<<"index is : "<<index <<std::endl;
                PixelBuffer[index] = 255;
            }
        }
    }
    else{
        if(y2 > y1)
        {
            for(int i=0; i <= y2-y1; i++)
            {
                int index = GetLineCoordinateToIndex(x1, y1, i, slope);
                PixelBuffer[index] = 255;
            }
        }
        else{
            for(int i=0; i >= y2-y1; i--)
            {
                int index = GetLineCoordinateToIndex(x1, y1, i, slope);
                PixelBuffer[index] = 255;
            }
        }
    }
}

int Polygon::GetLineCoordinateToIndexBresenham(float x, float y, int val, float slope)
{
    int index = 0;
    int y_aix = 0;
    if(slope <= 1 && slope >= -1)
    {
        float y_new = slope * val + y;
        if(abs(y_new+1 - y_new) < abs(y_new-ceil(y_new)))
        {
            y_aix = y_new+1;
        }
        else{
            y_aix = y_new;
        }
        index = y_aix * mLength + val + x;
    }
    else{
        float x_new = 1 / slope * val + x;
        int x_aix = 0;
        if(abs(x_new+1 - x_new) < abs(x_new-ceil(x_new)))
        {
            x_aix = x_new+1;
        }
        else
        {
            x_aix = x_new;
        }
        index = (val + y) * mLength + x_aix;
    }
    return index;
}

void Polygon::DebugDrawLine(float* PixelBuffer)
{
    for(int i = 20; i<300; i++)
    {
        PixelBuffer[200 * 200 + i] = 255;
    }
}

void Polygon::Rasterzing(float *Pixel)
{
    //std::cout<<"Draw completed. Rasterzing now..."<<std::endl;
    //find horizontal point
    
    //  std::cout<<"Max H "<<maxHeight <<" Min H " << minHeight << " Max W "<<maxWeight<<" Min W " << minWeight<<std::endl;
    
    bool RasterIndicate = false;
    FindMinMax();

    for(int i = minHeight+1; i < maxHeight; i++)
    {
        for(int j = minWeight; j<= maxWeight; j++)
        {
            int index = i * 200 + j;
            //     std::cout<<"index "<<index <<" "<<Pixel[index]<<std::endl;
            if(Pixel[index] == 255 && Pixel[index + 1] == 0)
            {
                if(RasterIndicate)
                    RasterIndicate = false;
                else
                    RasterIndicate = true;
                
            }
            if(RasterIndicate)
            {
                Pixel[index] = 255;
            }
        }
        RasterIndicate = false;
    }

}

void Polygon::FindMinMax()
{
    for(int i = 0; i < Points.size(); i++)
    {
        // std::cout<<"i: "<<i;
        if(std::get<1>(Points[i]) <= minHeight)
        {
            minHeight = std::get<1>(Points[i]);
        }
        if(std::get<1>(Points[i]) >= maxHeight)
        {
            maxHeight = std::get<1>(Points[i]);
        }
    }
    for(unsigned int j = 0; j< Points.size(); j++)
    {
        if(std::get<0>(Points[j]) <= minWeight)
        {
            minWeight = std::get<0>(Points[j]);
        }
        if(std::get<0>(Points[j]) >= maxWeight)
        {
            maxWeight = std::get<0>(Points[j]);
        }
    }

}

/*
void Polygon::FindHorizontal(float* Pixel)
{
    std::vector<std::tuple<float, float>> temp;
    for(int i = minHeight+1; i < maxHeight; i++)
    {
        for(int j = minWeight; j<= maxWeight; j++)
        {
            if(Pixel[i * mHeight + j] == 255)
            
        }
    }
}
 */

void Polygon::Translation(float vec1, float vec2)
{
    for(int i=0; i<coordinates.size(); i++)
    {
        std::get<0>(coordinates[i]) += vec1;
        std::get<1>(coordinates[i]) += vec2;
    }
    
    ConvertCoordinateToPoint();
}


void Polygon::Rotation( double degree ){

    double centery = (maxHeight - minHeight)/40.0;
    double centerx = (maxWeight - minWeight)/40.0;
  //  std::cout<<"central" << centerx <<" "<<centery<<std::endl;
    Translation( -centerx, -centery );
    
    for(int i = 0; i<coordinates.size(); i++)
    {
        double tempArray = std::get<0>(coordinates[i]);
        std::get<0>(coordinates[i]) = std::get<0>(coordinates[i]) * cos(degree * PI / 180.0) + std::get<1>(coordinates[i]) * sin(degree * PI / 180);
        std::get<1>(coordinates[i]) = std::get<1>(coordinates[i]) * cos(degree* PI / 180.0) - tempArray * sin( degree*PI/180.0);
    }

    Translation(centerx, centery);
}

void Polygon::Scalling( int scalx, int scaly){
    if(scaly == 0)
    {
        scaly = scalx;
    }
    for(int i = 0; i< coordinates.size(); i++)
    {
        std::get<0>(coordinates[i]) *= scalx;
        std::get<1>(coordinates[i]) *= scaly;
    }
    ConvertCoordinateToPoint();
}

void Polygon::FindHorizontal(float* Pixel)
{
  //  std::cout<<"I enter FindHorizontal"<<std::endl;
    FindMinMax();
    std::vector<std::tuple<int, int>> temp;
    for(int i=minHeight+1; i<maxHeight; i++)
    {
        for(int j=minWeight; j<=maxWeight; j++)
        {

            int index = i * mHeight + j;
            if(Pixel[index] == 255 && Pixel[index+1] == 0)
            {
                temp.push_back(std::make_tuple(j,i));
              //  std::cout<<"index "<<index<<std::endl;
            }
        }
        if(temp.size() == 2)
        {
            horizontal.push_back(std::make_tuple(std::get<0>(temp[1]), std::get<1>(temp[1]), std::get<0>(temp[0]), std::get<1>(temp[0])));
       //     std::cout<<"horizontal "<<std::get<0>(horizontal[0])<<std::get<1>(horizontal[0])<<std::get<2>(horizontal[0])<<std::endl;
        }
        else if(temp.size() == 3)
        {
            for(int x=1; x< temp.size(); x++)
            {
                horizontal.push_back(std::make_tuple(std::get<0>(temp[x-1]), std::get<1>(temp[x-1]), std::get<0>(temp[x]), std::get<1>(temp[x])));
            }
        }
        else if(temp.size() == 4)
        {
            for(int x = 1; x<temp.size(); x+=2 )
            {
                horizontal.push_back(std::make_tuple(std::get<0>(temp[x-1]), std::get<1>(temp[x-1]), std::get<0>(temp[x]), std::get<1>(temp[x])));
            }
        }
        temp.clear();
    }
}

