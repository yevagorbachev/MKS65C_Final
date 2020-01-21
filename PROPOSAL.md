# Systems Level Programming Final Project
- PROJECT DUE: Friday 1/17, 8am
- PROPOSALS DUE: Thursday 1/2/20
- GitHub link: https://github.com/mks65/final.git

## Group Members
Amanda Chen, Yevgeniy Gorbachev, Bryan Lai

## Project Statement
To create a program where two users can play chess against one another through a terminal.

## User Interface
Once launching the program there will be a title screen that asks the user a few things:
### Instructions
  Informs the user on how the game is played through the terminal and can be accessed by typing “help” in the terminal.
  For example: Possibly using a spacebar to select a specific chess piece, while also using the arrow keys to move said piece. 
  Another approach would be through the use of the game prompting the user to type in specific coordinates. 
### Starting the Game
  The user will be prompted to either play on the same computer or against someone on a different computer.
  A chess board will be sent through a socket or named pipe each time a player makes a move. 
  There will also be an indicator to show whose turn it is while playing the game.
### Technical Design
4 Topics:
* Allocating memory to keep track of the board state.
* Writing moves to a file, to save for later
* Option to play from two terminal sessions on the same computer, or from different computers:
  * Networking
  * Named pipes

## Task Delegation
### Amanda Chen
Implement chess
### Yevgeniy Gorbachev	
Implement IPC  
Assist with implementing chess
### Bryan Lai
Rendering board

## Data Structures and Algorithms
### Utilizing a 2D Array (8x8) for the board
* Each piece is associated with a single char.
### Structs used to store the board and game pieces
### Implement chess

## Timeline
* 01/02/19 - Project approval and begin working on project
* 01/06/19 - Base game should be completed
  * User can take turns moving pieces to valid spaces on a board
* 01/08/19 - User can see a chess board on their terminal 
* 01/10/19 - Chess game should work between two players on the same computer
* 01/13/19 - Chess game should work between two players on different computers
* 01/14/19 - Title screen, help page, game statistics, and other small features
* 01/15/19 - Wrap up final parts of project
* 01/16/19 - Final testing and last commits
