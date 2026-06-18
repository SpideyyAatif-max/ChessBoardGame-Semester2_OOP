# Chess Board Game

This project was developed in C language during Semester Two, under Object Oriented Programming Course.

A simple **console-based Chess Board Game written in C++**.  
This project demonstrates object-oriented programming concepts such as classes, inheritance, constructors, destructors, encapsulation, operator overloading, file handling, and basic chess movement validation.

## Features

### Chess Board Features

- Displays an 8x8 chess board
- Shows chess pieces using symbols
- Supports board coordinates like:
  - `a2`
  - `a4`
  - `e2`
  - `e4`
- Allows users to move chess pieces
- Validates basic movement rules for:
  - Pawn
  - Rook
  - Knight
  - Bishop
  - Queen
  - King
- Prevents moving from an empty position
- Prevents capturing a piece of the same color
- Allows capturing opponent pieces

## Player Features

- Player sign-up
- Stores player details:
  - name
  - game ID
  - flex statement/Bio
  - level
  - experience
  - player points
- Displays player information using operator overloading
- Allows two players to chat
- Saves player data to a file
- Reads player data from a file

## Technologies Used

- C++ Programming Language
- Object-Oriented Programming
- File Handling
- Standard C++ Libraries:
  - `iostream`
  - `string`
  - `fstream`
  - `cmath`

Main Classes

1. ChessPiece
Represents a chess piece.
Stores:
piece name
piece color
piece symbol

2. ChessBoard
Represents the chess board.
Responsibilities:
initialize the board
place chess pieces
display the board
move pieces
validate moves
handle captures
delete dynamically allocated pieces

3. Player
Represents a player.
Responsibilities:
sign up player
display player profile
play game
chat with another player
save player data to file
read player data from file

Chess Piece Symbols

Symbol	  Piece	Color
p	        Pawn	White
r	        Rook	White
n	        Knight	White
b	        Bishop	White
q	        Queen	White
k	        King	White
P	        Pawn	Black
R	        Rook	Black
N	        Knight	Black
B	        Bishop	Black
Q	        Queen	Black
K	        King	Black

Board Coordinates
The board uses standard chess-style coordinates.
Example:
a b c d e f g h
Rows are numbered from 1 to 8.
Example moves:
a2 to a4
b1 to c3
e2 to e4

How to Compile and Run

Using g++
Compile:
g++ ChessBoardGame.cpp -o ChessBoardGame
Run:
./ChessBoardGame

On Windows
Compile:
g++ ChessBoardGame.cpp -o ChessBoardGame.exe
Run:
ChessBoardGame.exe


## Project File

```text
ChessBoardGame.cpp
