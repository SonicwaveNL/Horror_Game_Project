Horror Game Project
======
###### By Team Booh
###### January 2020

# Information
## About this game
We are making an SFML top-down, rogue-like horror game, where the user has to navigate their way through a maze, finding multiple 'levers' and eventually opening the level's door.  
During this entire time, the user is being chased by a monster and the player's view is limited, due to darkness, only having access to a lantern.  
The player can purchase powerups to make their journey easier, by going to the store via the main menu.
You can buy these powerups via 'points', which the user earns by winning levels.
The user can make their own levels, but can also use a number of pre-made levels.
    
## About the team
We are just a group of students, trying to finish a university project.  
Striving to make a scary, exciting game to scare the hell out of our teachers.

# Installation
## Prerequisites
To compile this game, you need to have the following installed:
* G++ (gcc)
* Make
* SFML

To create the doxygen(documentation) file, you need to have the following installed:
* Doxygen

## Compiling
To compile the game, go to the root directory and run:
```bash
make build
```

## Running the game
To run the game, go to the root directory after compiling and run:
```bash
make run
```
or, if the game has already been compiled:
```bash
./Booh
```

## Documentation
To generate the documentation, go to the root folder and run 'doxygen Doxyfile'.
After that, you can open any html file with your preferred webbrowser.

# Playing the game
## The monster 
You are being chased by an evil pig, oh no!
How does it work?
In simple terms: it tries to take the shortest path to your last known location.
This location the monster knows is delayed by a little bit, to make it more doable for the player.
In more advanced terms:
We use a modified version of the BFS algorithm based on a delayed location to follow the player accurately, but still have it be possible. 

## The Power-ups
As of the end of the project, only 2 powerups have been added.
These are the following powerups:
* Player Speed      - This gives the player 10 seconds of god-like running
* Monster Freezer   - This pauses the AI's movement for 30 seconds

## Your Goal
Your goal is to stay alive whilst trying to navigate your way through the maze and find all switches.
Once you find a switch, you have to flip it and then quickly continue on your way.
When all switches are flipped, you need to find the door and go through it. 

And that's it! 
When you complete levels, you earn points.
You can use these to buy powerups and complete even harder levels!

