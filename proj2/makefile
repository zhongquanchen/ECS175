All: project2

project2: main.cpp FileProcessor.o Object.o
	g++ -Wall -std=c++14 -o project2 main.cpp FileProcessor.o Object.o -lglut -lGL

FileProcessor.o: FileProcessor.cpp FileProcessor.h
	g++ -g -Wall -std=c++14 -c FileProcessor.cpp

Object.o: Object.cpp Object.h
	g++ -g -Wall -std=c++14 -c Object.cpp

clean:
	rm -f *.o project2
