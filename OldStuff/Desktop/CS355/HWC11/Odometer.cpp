#include <iostream>
#include <string>
#include <cstdlib>
#include <array>

struct Odometer {
std::array<int,9> digits;
Odometer() : digits{{0,0,0,0}} {}
Odometer& operator++() { // pre-increment
for (int i = 8; i >= 0; i--) {
const int d = digits[i] + 1;
digits[i] = d % 10;
if (d < 10) break;
}
return *this;
}
const Odometer operator++(int) { // post-increment
Odometer old(*this);
++(*this);
return old;
}
};


int main(){
Odometer foo;
Odometer bar = ++++++foo;

Odometer dad = bar++;

std::cout << foo.digits[8] << std::endl;

std::cout << bar.digits[8] << std::endl;

std::cout << dad.digits[8] << std::endl;

}