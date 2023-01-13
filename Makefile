

all:
	g++ -std=c++20 -Wall -Wpedantic -Wextra -Iinclude src/main.cpp -Llib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_gpu -o build/test.exe