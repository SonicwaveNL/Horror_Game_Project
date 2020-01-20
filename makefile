
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
game.o: game.cpp game.hpp iObject.hpp support.hpp action.hpp player.hpp
player.o: player.cpp player.hpp iObject.hpp door.hpp wall.hpp
door.o: door.cpp door.hpp iObject.hpp
wall.o: iObject.hpp wall.hpp wall.cpp
monster.o: monster.cpp monster.hpp
iObject.o: iObject.cpp iObject.hpp
inputListener.o: inputListener.hpp inputListener.cpp
inputHandler.o: inputHandler.cpp inputHandler.hpp support.hpp keyboardMouse.hpp inputListener.hpp
keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
action.o: action.hpp action.cpp support.hpp inputHandler.hpp
%.o: %.cpp
	$(gcc) -c $< $(LIBS) -ICore/Headers -ICore/Sources -ICore/ -o $@

main: main.o game.o player.o iObject.o wall.o door.o monster.o inputHandler.o keyboardMouse.o action.o inputListener.o
	$(gcc) -o Booh main.o game.o player.o iObject.o wall.o door.o monster.o inputHandler.o inputListener.o keyboardMouse.o action.o $(LIBS)

clean:
	$(rm) main.o game.o player.o iObject.o wall.o support.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o action.o Booh

run: main
	./Booh
