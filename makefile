
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
game.o: game.cpp game.hpp iObject.hpp support.hpp action.hpp player.hpp gridCell.hpp switch.hpp
gridCell.o: iRectangle.hpp gridCell.hpp gridCell.cpp
# iCircle.o: iObject.hpp iCircle.hpp iCircle.cpp
switch.o: switch.hpp switch.cpp
iObject.o: iObject.hpp iObject.cpp
iRectangle.o: iObject.hpp iRectangle.hpp iRectangle.cpp
player.o: player.cpp player.hpp iObject.hpp iRectangle.hpp door.hpp wall.hpp
door.o: door.cpp door.hpp iRectangle.hpp
wall.o: iRectangle.hpp wall.hpp wall.cpp
inputListener.o: inputListener.hpp inputListener.cpp
inputHandler.o: inputHandler.cpp inputHandler.hpp support.hpp keyboardMouse.hpp inputListener.hpp
keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
action.o: action.hpp action.cpp support.hpp inputHandler.hpp
%.o: %.cpp
	$(gcc) -c $< $(LIBS) -ICore/Headers -ICore/Sources -ICore/ -o $@

main: main.o game.o player.o wall.o door.o inputHandler.o switch.o iRectangle.o gridCell.o iObject.o keyboardMouse.o action.o inputListener.o
	$(gcc) -o Booh main.o game.o player.o wall.o iObject.o switch.o iRectangle.o gridCell.o door.o inputHandler.o inputListener.o keyboardMouse.o action.o $(LIBS)

clean:
	$(rm) main.o game.o player.o wall.o support.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o action.o Booh

run: main
	./Booh
