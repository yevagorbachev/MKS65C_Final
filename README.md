## Systems Level Programming Final Project

### Group Members: <p> Amanda Chen, Yevgeniy Gorbachev, Bryan Lai

### Project Statement: <p> To create a program where users can play chess against one another through a terminal.

### User Interface:
Once launching the program there will be a title screen that asks the user a few things:
#### Instructions:
  Informs the user on how the game is played through the terminal and can be accessed by typing “help” in the terminal.
  For example: Possibly using a spacebar to select a specific chess piece, while also using the arrow keys to move said piece. 
  Another approach would be through the use of the game prompting the user to type in specific coordinates. 
#### Starting the Game:
  The user will be prompted to either play on the same computer or against someone on a different computer. (Essentially, networked vs same-computer games)
  A chess board will be sent continuously through the terminal, updating each time a player makes a move. 
  There will also be an indicator to show whose turn it is while playing the game.
### Technical Design:
Topics:
The 5 topics that will be utilized within this project are the following:
<li>
<ul> Allocating memory to keep track of the board state. </ul>
<ul> The fact that the program requires two players to play on separate computers, means these following topics are used as well: </ul>
  <ul> Pipes to facilitate and show user input between the two users. </ul>
  <ul>Shared Memory in order to show that two users are playing in specifically one game. (Different types of shared memory for different games between people).</ul>
<ul>Signals to factor in user input.</ul>
 </li>

#### Task Delegation:
##### Amanda Chen
In charge of implementing game mechanics and functionality.
This includes game states, specific turns, move validity, etc.
##### Yevgeniy Gorbachev	
In charge of networking (for two player games not on the same computer)
Will then focus on implementing game mechanics with Amanda.
##### Bryan Lai
In charge of rendering the board and making the graphical user interface.
Once done, will focus on helping with game functionality. 

#### Data Structures and Algorithms:
##### Utilizing a 2D Array (8x8) for the board.
Each piece is associated with a single char.
##### Structs used to differentiate between the board and game pieces.
##### Implement chess itself, with its specific ruleset. 
This involves different turns for players
Move Validity for specific pieces
Castling, move diagonally, forward, backwards, etc.
Winning requirements.

#### Timeline:
