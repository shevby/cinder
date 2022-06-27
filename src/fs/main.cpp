#include "fs.h"



int main() {

  for(auto i : fs::lsr()) {
    std::cout << i << std::endl;;
  }

  return 0;
}