Michael Allen-Bond
michael.allen-bond@email.wsu.edu

This Sudoku Solver takes in a string of 81 characters converting anything in the string that isn't 1-9 into 0's, and then will attempt to solve the sudoku puzzle.  It first deduces cell values by finding unique pencils values within a block, column, and row.  It then exhaustively solves the rest via backtracking solver.

The Original Puzzle, followed by the Deduced and Solved puzzles, will all be output.

To build, just enter 'make'.

To run, enter './solvesudoku', and then enter your 81 character string. You can also send your strings from a text file through stdin using './solvesudoku < sample.txt'.  This will only read the first puzzle out of your file, unless you uncomment the 'while' loop in solvesudoku.cpp's main function, which will allow it to continuously read and solve all the puzzles in a file.


Archive Contents:

	README.txt
	Makefile
	SudokuGrid.h
	solvesudoku.cpp

This program will not allow strings of any length other than 81. That said, it's possible to break the program if you put in a string containing numbers that cause the sudoku puzzle to be unsolvable.  The program won't crash, but it will put out a puzzle that is incomplete.