NAME: ZHONGQUAN CHEN 
ID: 913875678 
Mail: czqchen@ucdavis.edu

How to compile project type:
make
./project1

How to run:
.Two Data files in this project. 1. "data.txt" file is to store all the phong data. 2. "data2.txt" file is to store all the vertices and its normal vector.

.You can change the parameter in "data.txt" file

.If you want to test other vertices you would have to have the normal vectors for each of the object. Because I manually calculate the normal vector for each vertices

.Rasterzition function is reference from:
https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage


Notice:

.Did not implement half toning algorithm. So it would not have half toning choice
 
.Phong lighting model is confirmed to work properly. But for some how, Ka is larger tham Kd + Ks but if you using provided data, it will work properly.

.Object can take as many as you have, as long as you provide normal for each Object 

.Below is my data fashion.

3 			// number of object 

4 			// number of vertices 
67.6679 112.857 115.989
77.6679 146.318 107.023
58.7021 127.857 148.309
101.129 110.537 130.989
4 			// number of faces
2 1 0
3 2 0
1 3 0
1 2 3
4 			// number of normals 
0.260226 0.354463 0.282971
0.0199687 -0.17556 0.224462
0.216075 0.0128297 -0.183862
-0.21277 0.187904 -0.00878833

