
gcc := /usr/bin/g++
ln := /usr/bin/g++
rm := rm -f

vpath %.cpp Core/Sources
vpath %.hpp Core/Headers
vpath main.cpp Core

SFMLDIR = SFML-master/include

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: build clean run

build: main

# Dit word de game, alle .o bestanden toevoegen die nodig zijn. de game executible
# main: 
# 	gcc -o Booh main.o game.o $(LIBS)
main: main.o game.o player.o IObjects.o wall.o support.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o
main.o: main.cpp game.hpp
game.o: game.cpp game.hpp IObjects.hpp windowHandler.hpp inputHandler.hpp action.cpp action.hpp
player.o: player.cpp player.hpp IObjects.hpp door.hpp wall.hpp
support.o: support.cpp support.hpp 
door.o: door.cpp door.hpp IObject.hpp 
IObjects.o: IObjects.cpp IObjects.hpp
windowHandler.o: windowHandler.cpp windowHandler.hpp IObjects.hpp
inputListener.o: inputListener.cpp inputListener.hpp
inputHandler.o: inputHandler.cpp inputHandler.hpp inputListener.hpp keyboardMouse.hpp
keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
action.o: support.hpp inputHandler.hpp inputHandler.cpp
%.o: %.cpp
	gcc -c $< -o $@ -I$(SFMLDIR) $(LIBS) -ICore/Headers -ICore/Sources -ICore/

# toevoegen van alle hpp's
#main.o: main.cpp game.hpp
#	gcc -c main.cpp game.hpp -o main.o

# #Alle .o bestanden aanmaak
# game.o: game.cpp game.hpp IObjects.hpp windowHandler.hpp inputHandler.hpp 
# 	gcc -c game.cpp game.hpp IObjects.hpp windowHandler.hpp inputHandler.hpp game.o

# player.o: player.cpp player.hpp IObjects.hpp door.hpp wall.hpp
# 	gcc -c player.cpp player.hpp IObjects.hpp door.hpp wall.hpp -o player.o

# wall.o: wall.cpp wall.hpp IObjects.hpp
# 	gcc -c wall.cpp wall.hpp IObjects.hpp -o wall.o

# support.o: support.cpp support.hpp 
# 	gcc -c support.cpp support.hpp -o support.o

# door.o: door.cpp door.hpp IObject.hpp 
# 	gcc -c door.cpp door.hpp IObject.hpp -o door.o

# #heeft SFML
# IObjects.o: IObjects.cpp IObjects.hpp 
# 	gcc -c IObjects.cpp IObjects.hpp $(LIBS) -o IObjects.o

# windowHandler.o: windowHandler.cpp windowHandler.hpp IObjects.hpp
# 	gcc -c windowHandler.cpp windowHandler.hpp $(LIBS) -o windowHandler.o

# inputListener.o: inputListener.cpp inputListener.hpp
# 	gcc -c inputListener.cpp inputListener.hpp $(LIBS) -o inputListener.o

# inputHandler.o: inputHandler.cpp inputHandler.hpp inputListener.hpp keyboardMouse.hpp
# 	gcc -c inputHandler.cpp inputHandler.hpp inputListener.hpp keyboardMouse.hpp -o inputHandler.o


# keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
# 	gcc -c keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp -o keyboardMouse.o


# make clean en make run.
clean:
	$(rm) main.o game.o player.o IObjects.o wall.o support.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o

run: main
	./Booh
