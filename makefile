all: compile link delete

compile:
	g++ -c main.cpp src/*.cpp src/lang/tinyxml2.cpp

link:
	g++ *.o -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run:
	./main

delete:
	rm -rf *.o 
