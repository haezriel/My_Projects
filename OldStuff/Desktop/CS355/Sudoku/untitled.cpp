std::array<std::array<Cell,9>,9> grid;

std::bitset<9> pencils; // value 0..8 represent pencils 1..9

std::string puzzle;
std::cin >> puzzle;
// validate input
SudokuGrid grid(puzzle);

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
autopencil(grid);
changed = true;
break;
}
} while(changed);
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