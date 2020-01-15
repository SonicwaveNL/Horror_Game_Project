
gcc := /usr/bin/g++
ln := /usr/bin/g++
rm := rm -f

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: build clean run

build: main

# Dit word de game, alle .o bestanden toevoegen die nodig zijn.
main: main.o game.o player.o IObjects.o wall.o support.o actions.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o
	gcc -o Booh main.o game.o $(LIBS)

# toevoegen van alle hpp's
main.o:  

#Alle .o bestanden aanmaak
game.o: game.cpp game.hpp IObjects.hpp windowHandler.hpp inputHandler.hpp actions.hpp
	gcc -c game.cpp game.hpp IObjects.hpp windowHandler.hpp inputHandler.hpp game.o

player.o: player.cpp player.hpp IObjects.hpp
	gcc -c player.cpp player.hpp IObjects.hpp -o player.o

#heeft SFML
IObjects.o: IObjects.cpp IObjects.hpp 
	gcc -c IObjects.cpp IObjects.hpp $(LIBS) -o IObjects.o

wall.o: wall.cpp wall.hpp
	gcc -c wall.cpp wall.hpp -o wall.o

support.o: support.cpp support.hpp actions.hpp
	gcc -c support.cpp support.hpp actions.hpp -o support.o

actions.o: actions.hpp
	gcc -c actions.hpp $(LIBS) -o actions.o

door.o: door.cpp door.hpp IObjects.hpp 
	gcc -c door.cpp door.hpp IObjects.hpp -o door.o

#heeft SFML
windowHandler.o: windowHandler.cpp windowHandler.hpp 
	gcc -c windowHandler.cpp windowHandler.hpp $(LIBS) -o windowHandler.o

inputHandler.o: inputHandler.cpp inputHandler.hpp inputListener.hpp
	gcc -c inputHandler.cpp inputHandler.hpp inputListener.hpp -o inputHandler.o

#heeft SFML
inputListener.o: inputListener.cpp inputListener.hpp
	gcc -c inputListener.cpp inputListener.hpp $(LIBS) -o inputListener.o

keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
	gcc -c keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp -o keyboardMouse.o


# make clean en make run.
clean:
	$(rm) main.o game.o player.o IObjects.o wall.o support.o actions.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o

run:
	make; ./Booh
