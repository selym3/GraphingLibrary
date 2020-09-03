all: compile
	clang++ main.cpp bin/*.o -lSDL2 -lm -o main

compile:
	clang++ impl/Graph.cpp -c -o bin/Graph.o
	clang++ impl/Vec2.cpp -c -o bin/Vec2.o
	clang++ impl/Camera.cpp -c -o bin/Camera.o
	clang++ impl/Mouse.cpp -c -o bin/Mouse.o
	clang++ impl/Keyboard.cpp -c -o bin/Keyboard.o
	clang++ impl/Filter.cpp -c -o bin/Filter.o
