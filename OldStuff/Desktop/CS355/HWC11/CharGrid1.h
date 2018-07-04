#ifndef CHARGRID1_H
#define CHARGRID1_H

class CharGrid1 {
private:
int _width, _height; // grid size
char *_grid; // _width*_height char’s in row-major order

public:
CharGrid1(int w, int h, char ch= ' ')
: _width{w}, _height{h}, _grid{new char[w*h]} {}

CharGrid1(const CharGrid1& other); // Copy Constructor
CharGrid1& operator=(const CharGrid1& other); // Copy Assign 

CharGrid1(CharGrid1&& other); // Move Constructor
CharGrid1& operator=(CharGrid1&& other); // Move Assign 

int width() const {return _width;}
int height() const {return _height;}


const char *operator[](int r) const {return &_grid[r*_width];} // read
char *operator[](int r) {return &_grid[r*_width];} // write
// ...
~CharGrid1() {delete[] _grid;}
};
#endif