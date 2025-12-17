#include <iostream>
#include "ascii_draw.hpp"
int main() {
  using namespace topit;
  int err = 0;
  IDraw* shps[6] = {};
  p_t * pts = nullptr;
  size_t s = 0;
  try {
    shps[0] = new Dot(0, 0);
    shps[1] = new Dot(5, 7);
    shps[2] = new Dot(-5, -2);
    shps[3] = new HSeg(6, 2, 9, 2);
    shps[4] = new VSeg(2, 1, 2, 7);
    shps[5] = new Diag45(4, 4, 8, 8);
    for (size_t i = 0; i < 6; ++i) {
      s += points(*(shps[i]), &pts, s);
    }
    f_t fr = frame(pts, s);
    char * cnv = canvas(fr, '.');
    for (size_t i = 0; i < s; ++i) {
      paint(cnv, fr, pts[i], '#');
    }
    flush(std::cout, cnv, fr);
    delete [] cnv;
  } catch (...) {
    err = 2;
    std::cerr << "Bad drawing\n";
  }
  delete [] pts;
  for (size_t i = 0; i < 6; ++i) {
    delete shps[i];
  }
  return err;
}
