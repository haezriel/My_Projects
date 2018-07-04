#include <iostream>
#include <map>
#include <cstdlib>

//
// Class for function object that computes
// (n choose k) using memoization.
//
class Binomial {
  mutable std::map<std::pair<int,int>,unsigned long> table;
public:
  unsigned long operator()(int n, int k) const {
    if (k > n/2)
      k = n - k;
    if (k == 0)
      return 1;
    if (k == 1)
      return n;
    if (k == 2)
      return n*(n-1)/2;
    // really slow version
    if (table[std::make_pair(n,k)]==0){
      table[std::make_pair(n,k)]= 
       (*this)(n-1,k-1) + (*this)(n-1,k);
    }
    return table[std::make_pair(n,k)];
  }
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "usage: " << argv[0] << " n k " << std::endl;
    exit(1);
  }
  const int n = atoi(argv[1]);
  const int k = atoi(argv[2]);
  if (n < 0 || k < 0 || k > n) {
    std::cerr << "k must be in range: 0 <= k <= n" << std::endl;
    exit(2);
  }
  Binomial choose;
  const unsigned long b = choose(n,k);
  std::cout << b << std::endl;
  return 0;
}
