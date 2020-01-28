gcc := /usr/bin/g++
ln := /usr/bin/g++
rm := rm -f

vpath %.cpp Core/Sources
vpath %.hpp Core/Headers
vpath main.cpp Core

LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.PHONY: build clean run

build: main

#windowHandler.o : windowHandler.hpp windowHandler.cpp iObject.hpp
# iCircle.o: iObject.hpp iCircle.hpp iCircle.cpp

action.o: action.hpp action.cpp support.hpp inputHandler.hpp
door.o: door.cpp door.hpp iRectangle.hpp
floor.o: floor.hpp floor.cpp
fileFactory.o: fileFactory.hpp fileFactory.cpp support.hpp gridCell.hpp wall.hpp player.hpp monster.hpp switch.hpp door.hpp uiElement.hpp iException.hpp floor.hpp
game.o: game.cpp game.hpp action.hpp gridCell.hpp iObject.hpp monster.hpp player.hpp support.hpp switch.hpp uiElement.hpp iException.hpp floor.hpp sound.hpp
gridCell.o: gridCell.hpp gridCell.cpp iRectangle.hpp
inputHandler.o: inputHandler.cpp inputHandler.hpp support.hpp keyboardMouse.hpp inputListener.hpp
inputListener.o: inputListener.hpp inputListener.cpp
iObject.o: iObject.hpp iObject.cpp
iRectangle.o: iRectangle.hpp iRectangle.cpp iObject.hpp
keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
monster.o : monster.hpp monster.cpp door.hpp iRectangle.hpp wall.hpp player.hpp
player.o: player.cpp player.hpp iObject.hpp iRectangle.hpp door.hpp wall.hpp
sound.o: sound.hpp sound.cpp
switch.o: switch.hpp switch.cpp iRectangle.hpp player.hpp
uiElement.o : uiElement.hpp uiElement.cpp
wall.o: wall.hpp wall.cpp iRectangle.hpp iRectangle.hpp
main.o: main.cpp game.hpp

%.o: %.cpp
	$(gcc) -c $< $(LIBS) -ICore/Headers -ICore/Sources -ICore/ -o $@

main: action.o door.o floor.o fileFactory.o game.o gridCell.o inputHandler.o inputListener.o iObject.o iRectangle.o keyboardMouse.o monster.o player.o switch.o wall.o uiElement.o sound.o main.o
	$(gcc) -o Booh action.o door.o floor.o fileFactory.o game.o gridCell.o inputHandler.o inputListener.o iObject.o iRectangle.o keyboardMouse.o monster.o player.o switch.o wall.o uiElement.o sound.o main.o $(LIBS)

clean:
	$(rm) main.o game.o player.o wall.o support.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o action.o floor.o fileFactory.o gridCell.o iObject.o iRectangle.o monster.o switch.o uiElement.o sound.o Booh

run: main
	./Booh