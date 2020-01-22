
gcc := /usr/bin/g++
ln := /usr/bin/g++
rm := rm -f

vpath %.cpp Core/Sources
vpath %.hpp Core/Headers
vpath main.cpp Core

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: build clean run

build: main

<<<<<<< HEAD
#windowHandler.o : windowHandler.hpp windowHandler.cpp iObject.hpp
# iCircle.o: iObject.hpp iCircle.hpp iCircle.cpp

action.o: action.hpp action.cpp support.hpp inputHandler.hpp
=======
main.o: main.cpp game.hpp
game.o: game.cpp game.hpp iObject.hpp support.hpp action.hpp player.hpp gridCell.hpp switch.hpp
gridCell.o: iRectangle.hpp gridCell.hpp gridCell.cpp
fileFactory.o: fileFactory.hpp fileFactory.cpp support.hpp wall.hpp player.hpp switch.hpp monster.hpp door.hpp gridCell.hpp
# iCircle.o: iObject.hpp iCircle.hpp iCircle.cpp
monster.o: monster.hpp monster.cpp door.hpp iRectangle.hpp wall.hpp
switch.o: switch.hpp switch.cpp
iObject.o: iObject.hpp iObject.cpp
iRectangle.o: iObject.hpp iRectangle.hpp iRectangle.cpp
player.o: player.cpp player.hpp iObject.hpp iRectangle.hpp door.hpp wall.hpp
>>>>>>> 4f3abc5c2b84cf3a007a36ca872b87ca12a0ba6b
door.o: door.cpp door.hpp iRectangle.hpp
game.o: game.cpp game.hpp action.hpp gridCell.hpp iObject.hpp monster.hpp player.hpp support.hpp switch.hpp
gridCell.o: gridCell.hpp gridCell.cpp iRectangle.hpp
inputHandler.o: inputHandler.cpp inputHandler.hpp support.hpp keyboardMouse.hpp inputListener.hpp
inputListener.o: inputListener.hpp inputListener.cpp
iObject.o: iObject.hpp iObject.cpp
iRectangle.o: iRectangle.hpp iRectangle.cpp iObject.hpp
keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
monster.o : monster.hpp monster.cpp door.hpp iRectangle.hpp wall.hpp
player.o: player.cpp player.hpp iObject.hpp iRectangle.hpp door.hpp wall.hpp
switch.o: switch.hpp switch.cpp iRectangle.hpp player.hpp
wall.o: wall.hpp wall.cpp iRectangle.hpp iRectangle.hpp
main.o: main.cpp game.hpp

%.o: %.cpp
	$(gcc) -c $< $(LIBS) -ICore/Headers -ICore/Sources -ICore/ -o $@

<<<<<<< HEAD
main: action.o door.o game.o gridCell.o inputHandler.o inputListener.o iObject.o iRectangle.o keyboardMouse.o monster.o player.o switch.o wall.o main.o
	$(gcc) -o Booh action.o door.o game.o gridCell.o inputHandler.o inputListener.o iObject.o iRectangle.o keyboardMouse.o monster.o player.o switch.o wall.o main.o $(LIBS)
=======
main: main.o game.o player.o wall.o door.o inputHandler.o fileFactory.o switch.o iRectangle.o gridCell.o monster.o iObject.o keyboardMouse.o action.o inputListener.o
	$(gcc) -o Booh main.o game.o player.o wall.o iObject.o fileFactory.o switch.o iRectangle.o gridCell.o monster.o door.o inputHandler.o inputListener.o keyboardMouse.o action.o $(LIBS)
>>>>>>> 4f3abc5c2b84cf3a007a36ca872b87ca12a0ba6b

clean:
	$(rm) main.o game.o player.o wall.o support.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o action.o Booh

run: main
	./Booh
