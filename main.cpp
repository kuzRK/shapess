#include <iostream>
namespace topit
{
  struct p_t {
    int x, y;
  };
  bool operator==(p_t, p_t);
  bool operator!=(p_t, p_t);
  struct f_t {
    p_t aa;
    p_t bb;
  };
  struct IDraw {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
    virtual ~IDraw() = default;
  };
  struct Dot: IDraw {
    Dot(int x, int y);
    explicit Dot(p_t dd);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t d;
  };
  int min(int a, int b);
  int max(int a, int b);
  struct HSeg: IDraw {
    HSeg(int x1, int x2, int y);
    p_t begin() const override;
    p_t next(p_t) const override;
    int x1, x2, y;
  };
  size_t points(const IDraw& d, pt** pts,l size_t s);
  f_t frame(const p_t* pts, size_t s);
  char * canvas(f_t fr, char fill);
  void paint(char * cnv, f_t fr, p_t p, char fill);
  void flush(std::ostream& os, const char * cnv, f_t fr);
}
int main()
{
  using topit::Dot;
  using topit::IDraw;
  using topit::f_t;
  using topit::p_t;
  using topit::HSeg;
  IDraw * shps[4] = {};
  p_t * pts = nullptr;
  size_t s = 0;
  int err = 0;
  try {
    shps[0] = new Dot(0,0);
    shps[1] = new Dot(5,7);
    shps[2] = new Dot(-5,-2);
    shps[3] = new HSeg(6, 2, 1);
    for (size_t i = 0; i < 3; ++i) {
      s += points(*(shps[i]), &pts, s)
    }
    f_t fr = frame(pts, s);
    char * cnv = canvas(fr, '.');
    for (size_t i = 0; i < s; ++i) {
      paint(cnv, fr, pts[i], '#');
    }
    flush(std::cout, cnv, fr);
    delete[] cnv;
  } catch (...) {
    err = 2;
    std::cerr << "bad drawing\n";
  }
  for (size_t i = 0; i < 4; ++i) {
    delete shps[i];
  }
  delete[] pts;
  return err;
}
bool topit::operator==(p_t a, p_t b) {
  return a.x == b.x && a.y == b.y;
}
bool topit::operator!=(p_t a, p_t b) {
  return !(a == b);
}
topit::Dot::Dot(int x, int y):
  IDraw(), d{x, y}
{}
topit::p_t topit::Dot::next(p_t prev) const {
  if (prev != begin()) {
    throw std::logic_error("bad input\n");
  }
  return d;
}
topit::Dot::Dot(p_t dd):
  IDraw(), d{dd}
{}
int topit::min(int a, int b) {
  return (a < b) ? a : b;
}
int topit::max(int a, int b) {
  return (a > b) ? a : b;
}
topit::HSeg::HSeg(int x1, int x2, int y):
  IDraw(), x1(min(x1,x2)), x2(max(x1,x2)), y(y)
{}
