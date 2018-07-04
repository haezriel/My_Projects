#include <iostream>
#include <cstdlib>
#include <array>
#include <bitset>
#include <string>


struct Cell{
	int number=0;
	std::bitset<9> pencils;
	int solved=0;
};

class SudokuGrid {
private:
	std::array<std::array<Cell,9>,9> grid;

public:

	SudokuGrid(std::string s);
	int number(int row, int col) const {
		return grid[row][col].number;
	}
	void setNumber(int row, int col, int num){
		grid[row][col].number=num;
	}
	bool isFixed(int row, int col) const{
		if(grid[row][col].solved==0)
			return false;
		else
			return true;
	}
	bool isSolved(int row, int col) const{
		if(grid[row][col].solved==0)
			return false;
		else
			return true;
	}
	void setSolved(int row, int col){
		grid[row][col].solved=1;
	}
	bool isPencilSet(int row, int col, int n) const{
			if(grid[row][col].pencils[n-1]==1)
				return true;
			else
				return false;
	}
	bool anyPencilsSet(int row, int col) const{
		for(int i=1;i<=9;i++){
			if(isPencilSet(row,col,i-1))
				return true;
		}
		return false;
	}
	void setPencil(int row, int col, int n){
		grid[row][col].pencils.set(n-1);;
	}
	void setAllPencils(int row, int col){
		grid[row][col].pencils.set();
	}
	void clearPencil(int row, int col, int n){
		grid[row][col].pencils.reset(n-1);
	}
	void clearAllPencils(int row, int col){
		grid[row][col].pencils.reset();
	}
	void out(){
	for (int i=0;i<9;i++){
			if (i==3 || i==6)
				std::cout<< " ------+-------+------"<<std::endl;
		for(int j=0;j<9;j++){
			if (j==3 || j== 6)
				std::cout << ' '<< '|';
			if (grid[i][j].number==0)
				std::cout<< ' '<< '.';
			else
				std::cout <<' '<< grid[i][j].number;
		}
		std::cout << std::endl;
	}
	}
};

class Balls {};