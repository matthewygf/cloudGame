# Makefile
CC = gcc
CPP = g++
F77 = f77
F9X = gfortran
LD = g++
CFLAGS =  -Wall -g 
LIBS = -lGL -lGLU -lglut -lm -lpthread


# files to be compiled
FILES = client.cpp main.cpp ai/animalStates.cpp bots/mouse.cpp bots/cat.cpp bots/animal.cpp #src/tileMap/tileMap.cpp src/gameModel.cpp src/gameController.cpp src/gameView.cpp src/camera/camera.cpp supports/stb_image.h src/bots/animal.cpp src/bots/cat.cpp src/bots/mouse.cpp supports/matrix/src/Matrices.cpp src/tileMap/box.cpp supports/vbo/src/Timer.cpp src/ai/animalStates.cpp #src/rawModel/rawModel.cpp src/rawModel/loader.cpp

AUXFILES := 

# output file
OUTPUT = client

# target which compiles executable
all : $(FILES)
	$(CPP) $(AUXFILES) $(CFLAGS) $(FILES) $(LIBS) -o $(OUTPUT)

clean :
	rm -f $(OUTPUT)
