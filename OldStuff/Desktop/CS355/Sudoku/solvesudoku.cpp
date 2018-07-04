#include "SudokuGrid.h"
#include <cstdlib>
#include <iostream>
#include <array>
#include <bitset>
#include <string>


SudokuGrid::SudokuGrid(std::string s){
	int l=0;

	for (int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			grid[i][j].pencils.reset();
			if((s[l]-48)<10 && (s[l]-48)>0){
				grid[i][j].number= (s[l]-48);
				grid[i][j].solved=1;
			}
			else grid[i][j].number = 0;
			l++;
		}

}

bool conflictingNumber(SudokuGrid& grid, int row, int col, int n){
	for(int i=0;i<9;i++){
		if (grid.number(row,i)==n)
			return true;
		if (grid.number(i,col)==n)
			return true;
	}
	int k;
	int h;
	if (row<3) k=0;
	else if (row<6) k=3;
	else k=6;
	if (col<3) h=0;
	else if (col<6) h=3;
	else h=6;
	for (int i=0; i<3;i++)
		for (int j=0;j<3;j++){
			if (grid.number(i+k,j+h)==n)
				return true;
		}
return false;
}


void autoPencil(SudokuGrid& grid) {
for (int r = 0; r < 9; r++)
for (int c = 0; c < 9; c++)
if (grid.number(r,c) == 0) {
grid.setAllPencils(r,c);
for (int n = 1; n <= 9; n++)
if (conflictingNumber(grid,r,c,n))
grid.clearPencil(r,c,n);
}
}

int numPencilsInRow(SudokuGrid& grid, int row, int n){
	int count =0;
	for (int i=0; i<9;i++){
		if (grid.isPencilSet(row, i,n))
			count++;
	}
	return count;
}
int numPencilsInColumn(SudokuGrid& grid, int col, int n ){
	int count =0;
	for (int i=0; i<9;i++){
		if (grid.isPencilSet(i, col,n))
			count++;
	}
	return count;
}
int numPencilsInBlock(SudokuGrid& grid, int row, int col, int n){
	int count =0;
	int k;
	int h;
	if (row<3) k=0;
	else if (row<6) k=3;
	else k=6;
	if (col<3) h=0;
	else if (col<6) h=3;
	else h=6;
	for (int i=0; i<3;i++)
		for (int j=0;j<3;j++){
			if (grid.isPencilSet(i+k,j+h,n))
				count++;
		}
	return count;
}

void deduce(SudokuGrid& grid) {
bool changed;
do { // repeat until no changes made
autoPencil(grid);
changed = false;
for (int row = 0; row < 9; row++)
for (int col = 0; col < 9; col++)
for (int n = 1; n <= 9; n++)
if (grid.isPencilSet(row, col, n) &&
(numPencilsInRow(grid, row, n) == 1 ||
numPencilsInColumn(grid, col, n) == 1 ||
numPencilsInBlock(grid, row, col, n) == 1)) {
grid.clearAllPencils(row, col);
grid.setNumber(row,col,n);
grid.setSolved(row,col);
autoPencil(grid);
changed = true;
break;
}
} while(changed);
}

bool findUnassignedLocation(SudokuGrid& grid, int& row, int& col){
	for(row=0;row<9;row++)
		for(col=0;col<9;col++)
			if(grid.number(row,col)==0)
				return true;
	return false;
}

bool solveSudoku(SudokuGrid& grid) {
int row, col;
if (!findUnassignedLocation(grid, row, col))
return true; // puzzle filled, solution found!
for (int num = 1; num <= 9; num++)
if (!conflictingNumber(grid, row, col, num)) {
grid.setNumber(row, col, num); // try next number
if (solveSudoku(grid))
return true; // solved!
grid.setNumber(row, col, 0); // not solved, clear number
}
return false; // not solved, back track
}

main(){

	std::string puzzle;
	//while(1){
		std::cin >> puzzle;
		if(puzzle.length()!=81){
			exit(1);
		}
		SudokuGrid grid(puzzle);
		std::cout<<"Original:"<<std::endl;
		grid.out();
		std::cout<<std::endl;
		deduce(grid);
		std::cout<<"Deduced:"<<std::endl;
		grid.out();
		std::cout<<std::endl;
		solveSudoku(grid);
		std::cout<<"Solved:"<<std::endl;
		grid.out();
		std::cout<<std::endl;
	//}


}