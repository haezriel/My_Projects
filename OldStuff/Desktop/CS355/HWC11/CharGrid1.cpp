#include "CharGrid1.h"
#include <cstdlib>

CharGrid1::CharGrid1(const CharGrid1& other)
 : _width{other._width},
 _height{other._height},
 _grid{new char[other._width*other._height]}
 {
 for (int i = 1; i <= _width*_height; i++)
 	_grid[i]=other._grid[i];
 }

CharGrid1& CharGrid1::operator=(const CharGrid1& other) {
 if (this != &other) {
 _width = other._width;
 _height = other._height;
 delete[] _grid;
 _grid = new char[_width*_height];
 for (int i = 1; i <= _width*_height; i++)
 	_grid[i]=other._grid[i];
 }
 return *this;
 }

CharGrid1::CharGrid1(CharGrid1&& other) : _width{0},
_height{0},
 _grid{nullptr}
{
 _width = other._width;
 _height = other._height;
 _grid = other._grid;
 other._width = 0;
 other._height = 0;
 other._grid = nullptr;
}

CharGrid1& CharGrid1::operator=(CharGrid1&& other) {
 if (this != &other) {
 _width= other._width;
 _height = other._height;
 delete[] _grid;
 _grid = other._grid;
 other._height = 0;
 other._width = 0;
 other._grid = nullptr;
 }
 return *this;
}
