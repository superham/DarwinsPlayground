# Darwin's Playground
Authors: Alex Kaariainen, Dusten Knull, and Ellis Archuleta
_______________________________________________________________

## About:

Darwin's Playground is an arcade-style RTS game, inspired by the mechanics of other games
such as Sid Meier's Civilization, Plague Inc., Spore, and Settlers of Catan.

In this game, you create and evolve a species over time to make them grow and survive in their environment. As the species' populatioon grows, it's population will spread throughout the surrounding regions as well. You must continue to balance the species' traits and evolutionary status so that it may survive and thrive as it spreads and becomes dominant over the land. 
_______________________________________________________________
## Application Screenshot

![alt text](https://i.imgur.com/Nedmx2U.png4)

_______________________________________________________________
## Build instructions:

For Windows:
- In a MinGW terminal, cd to the 'Windows' directory in the root folder of this project
- On a 32-bit OS, simply run 'make all' or just 'make'
- On a 64-bit OS, run 'make all_64'
    
For Linux:
- In a unix terminal, cd to the 'Linux' directory
- Run the configure script provided via './configure.sh'. This script utilizes the 'apt-get' command, so if your system does not 
  support the apt package manager, you will have to manually install the packages specifed using your system's package manager
- After you have successfully installed the required packages, simply run 'make all' or just 'make'
_______________________________________________________________
