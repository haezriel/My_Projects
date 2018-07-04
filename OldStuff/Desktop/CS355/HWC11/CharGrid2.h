#ifndef CHARGRID2_H
#define CHARGRID2_H

#include <vector>

class CharGrid2 {
private:
std::vector<std::vector<char>> _grid;
public:
CharGrid2(int w, int h, char ch = ' ')
: _grid(h, std::vector<char>(w,ch)) {}
int width() const {return _grid[0].capacity();}
int height() const {return _grid.capacity();}
const std::vector<char>& operator[](int r) const { // read
return _grid[r];
}
std::vector<char>& operator[](int r) { // write
return _grid[r];
}
};
#endif // CHARGRID2_H
