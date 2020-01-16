
gcc := /usr/bin/g++
ln := /usr/bin/g++
rm := rm -f

vpath %.cpp Core/Sources
vpath %.hpp Core/Headers
vpath main.cpp Core

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: build clean run

build: main

# Dit word de game, alle .o bestanden toevoegen die nodig zijn. de game executible
# main: 
# 	gcc -o Booh main.o game.o $(LIBS)

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

# main: main.o game.o player.o IObject.o wall.o door.o inputHandler.o keyboardMouse.o action.o
# 	$(gcc) -o Booh main.o game.o player.o IObject.o wall.o door.o inputHandler.o keyboardMouse.o action.o -I$(LIBS)
# main.o: main.cpp game.hpp
# game.o: game.cpp game.hpp IObject.hpp support.hpp action.hpp player.hpp
# IObject.o: IObject.cpp IObject.hpp
# action.o: action.cpp action.hpp support.hpp inputHandler.hpp
# inputHandler.o: inputHandler.cpp inputHandler.hpp support.hpp keyboardMouse.hpp
# keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
# player.o: player.cpp player.hpp IObject.hpp door.hpp wall.hpp
# door.o: door.cpp door.hpp IObject.hpp
# wall.o: wall.hpp wall.cpp  IObject.hpp
# %.o: %.cpp
# 	$(gcc) -o $@ -c $< -I$(LIBS) -ICore/Headers -ICore/Sources -ICore/

# toevoegen van alle hpp's
#main.o: main.cpp game.hpp
#	gcc -c main.cpp game.hpp -o main.o

# #Alle .o bestanden aanmaak
# game.o: game.cpp game.hpp IObject.hpp windowHandler.hpp inputHandler.hpp 
# 	gcc -c game.cpp game.hpp IObject.hpp windowHandler.hpp inputHandler.hpp game.o

# player.o: player.cpp player.hpp IObject.hpp door.hpp wall.hpp
# 	gcc -c player.cpp player.hpp IObject.hpp door.hpp wall.hpp -o player.o

# wall.o: wall.cpp wall.hpp IObject.hpp
# 	gcc -c wall.cpp wall.hpp IObject.hpp -o wall.o

# support.o: support.cpp support.hpp 
# 	gcc -c support.cpp support.hpp -o support.o

# door.o: door.cpp door.hpp IObject.hpp 
# 	gcc -c door.cpp door.hpp IObject.hpp -o door.o

# #heeft SFML
# IObject.o: IObject.cpp IObject.hpp 
# 	gcc -c IObject.cpp IObject.hpp $(LIBS) -o IObject.o

# windowHandler.o: windowHandler.cpp windowHandler.hpp IObject.hpp
# 	gcc -c windowHandler.cpp windowHandler.hpp $(LIBS) -o windowHandler.o

# inputListener.o: inputListener.cpp inputListener.hpp
# 	gcc -c inputListener.cpp inputListener.hpp $(LIBS) -o inputListener.o

# inputHandler.o: inputHandler.cpp inputHandler.hpp inputListener.hpp keyboardMouse.hpp
# 	gcc -c inputHandler.cpp inputHandler.hpp inputListener.hpp keyboardMouse.hpp -o inputHandler.o


# keyboardMouse.o: keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp
# 	gcc -c keyboardMouse.cpp keyboardMouse.hpp inputListener.hpp -o keyboardMouse.o


# make clean en make run.
clean:
	$(rm) main.o game.o player.o IObject.o wall.o support.o door.o windowHandler.o inputHandler.o inputListener.o keyboardMouse.o

run: main
	./Booh
