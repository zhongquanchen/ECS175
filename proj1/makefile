All: project1 

project1: main.cpp FileProcessor.o Polygon.o
	g++ -Wall -std=c++14 -o project1 main.cpp FileProcessor.o Polygon.o -lglut -lGL

FileProcessor.o: FileProcessor.cpp FileProcessor.h
	g++ -g -Wall -std=c++14 -c FileProcessor.cpp

Polygon.o: Polygon.cpp Polygon.h data.txt
	g++ -g -Wall -std=c++14 -c Polygon.cpp

clean:
	rm -f *.o project1