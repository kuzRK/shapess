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
    HSeg(int x1, int y1, int x2, int y2);
    explicit HSeg(p_t a_, p_t b_);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a;
    p_t b;
  };
  struct VSeg: IDraw {
    explicit VSeg(p_t a_, p_t b_);
    VSeg(int x1, int y1, int x2, int y2);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a;
    p_t b;
  };
  struct Diag45: IDraw {
    explicit Diag45(p_t a_, p_t b_);
    Diag45(int x1, int y1, int x2, int y2);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a;
    p_t b;
  };
  size_t points(const IDraw& d, p_t** pts, size_t s);
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
      s += points(*(shps[i]), &pts, s);
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
topit::HSeg::HSeg(int x1, int y1,  int x2, int y2):
  IDraw(), a{min(x1,x2), y1}, b{max(x1, x2), y2}
{
  if (y1 != y2) {
    throw std::logic_error("Its not horisontal segment\n");
  }
}
topit::HSeg::HSeg(p_t a_, p_t b_):
  IDraw(), a{min(a_.y, b_.y), a_.y}, b{max(a_.y, b_.y), b_.y}
{
  if (a_.y != b_.y) {
    throw std::logic_error("its not horisontal segment\n");
  }
}
topit::VSeg::VSeg(p_t a_, p_t b_):
  IDraw(), a{a_.x, min(a_.y, b_.y)}, b{b_.x, max(a_.y, b_.y)}
{
  if (a_.x != b_.x) {
    throw std::logic_error("its not vertical segment\n");
  }
}
topit::VSeg::VSeg(int x1, int y1, int x2, int y2):
  IDraw(), a{x1, min(y1, y2)}, b{x2, max(y1,y2)}
{
  if (x1 != x2) {
    throw std::logic_error("its not vertical segment");
  }
}
topit::Diag45:Diag45(p_t a_, p_t b_):
  IDraw(), a{a_}, b{b_}
{
  int dx = b_.x - a_.x;
  int dy = b_.y - a_.y;
  if (std::abs(dx) != std::abs(dy)) {
    throw std::logic_error("its not 45 degree segment\n");
  }
}
topit::Diag45::Diag45(int x1, int y1, int x2, int y2):
  IDraw(), a{x1, y1}, b{x2, y2}
{
  int dx = x1 - x2;
  int dy = y1 - y2;
  if (std::abs(dx) != std::abs(dy)) {
    throw std::logic_error("its not 45 degree segment\n");
  }
}
topit::f_t topit::frame(const p_t * pts, size_t s)
{
  f_t fr;
  int min_x = pts[0].x;
  int max_x = pts[0].x;
  int min_y = pts[0].y;
  int max_y = pts[0].y;
  for (size_t i = 0; i < s; ++i) {
    if (pts[i].x < min_x) {
      min_x = pts[i].x;
    }
    if (pts[i].x > max_x) {
      max_x = pts[i].x;
    }
    if (pts[i].y < min_y) {
      min_y = pts[i].y;
    }
    if (pts[i].y > max_y) {
      max_y = pts[i].y;
    }
  }
  fr.aa = {min_x, min_y};
  fr.bb = {max_x, max_y};
  return fr;
}
