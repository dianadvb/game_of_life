  Project Overview

This repository contains my C++ implementation of Conway’s Game of Life, following the requirements outlined in this snippet. The program reads an initial board state from a file, applies the Game of Life rules for a set number of iterations, and outputs the final or intermediate states.

  How to Run It

1. Clone the Repository
   
git clone https://github.com/dianadvb/game_of_life.git

2. Navigate to the Executable

cd game_of_life/runnable

3. Run the Program

game_of_life.exe --input initial.txt --iterations 5 --all

(initial.txt can be replaced with any valid board file.)
Example files are included in the repository.

Tested on another PC (without Qt installed), and it worked correctly thanks to the included DLLs.


  Why Qt Creator?

I chose Qt Creator because it’s what I’ve been working with recently, and it has built-in CMake support.

After reinstalling my personal PC, I hadn’t set up Visual Studio, so Qt was the only IDE I had installed.

Future plans included adding a visualization feature, but I ran out of time—overestimated my available hours!

  Challenges Encountered & Solutions

1. Running Command Line Programs in Qt
Qt Creator is typically used for graphical projects, and I hadn’t used it for command-line programs before.
Solution: Learned how to set Run Parameters in Qt to execute command-line instructions.

2. Missing CMake Installation
   
Initially, my project wasn’t working outside Qt Creator because I didn’t have CMake installed.

Solution: Installed CMake separately and confirmed it worked across different systems. 


  Features & Additions

Persistent Data Storage

Each run stores its results by date and time in a folder instead of overwriting old outputs.

Alternative approach: Could store runs in a temporary folder with .gitignore, but for this small project, I left them stored.


  Code Optimization

Used const where necessary to prevent unwanted modifications and improve efficiency.

Possibly overused const, but aimed to make data handling safer.


  Code Structure

The logic is implemented in main.cpp for simplicity.

Potential improvement: Split functionality into multiple files or introduce classes for better organization.

Since the project was small, I kept it in one file to maintain simplicity.


  Future Improvements

Add a graphical visualization to watch the Game of Life evolve in real-time.

Improve modularity by separating logic into different classes.

Include more tests to validate board transformations.
