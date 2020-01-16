
gcc := /usr/bin/g++
ln := /usr/bin/g++
rm := rm -f

vpath %.cpp Core/Sources
vpath %.hpp Core/Headers
vpath main.cpp Core

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: build clean run

build: main

main.o: main.cpp game.hpp
game.o: game.cpp game.hpp IObject.hpp support.hpp action.hpp player.hpp
player.o: player.cpp player.hpp IObject.hpp door.hpp wall.hpp
door.o: door.cpp door.hpp IObject.hpp
wall.o: IObject.hpp wall.hpp wall.cpp
IObject.o: IObject.cpp IObject.hpp
inputListener.o: inputListener.hpp inputListener.cpp
# windowHandler.o: windowHandler.cpp windowHandler.hpp IObject.hpp
inputHandler.o: inputHandler.cpp inputHandler.hpp support.hpp keyboardMouse.hpp inputListener.hpp
keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
action.o: action.hpp action.cpp support.hpp inputHandler.hpp
%.o: %.cpp
	$(gcc) -c $< $(LIBS) -ICore/Headers -ICore/Sources -ICore/ -o $@

main: main.o game.o player.o IObject.o wall.o door.o inputHandler.o keyboardMouse.o action.o inputListener.o
	$(gcc) -o Booh main.o game.o player.o IObject.o wall.o door.o inputHandler.o inputListener.o keyboardMouse.o action.o $(LIBS)

clean:
	$(rm) main.o game.o player.o IObject.o wall.o support.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o action.o Booh

run: main
	./Booh
