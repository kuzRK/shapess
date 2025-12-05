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
    virtual p_t next() const = 0;
    virtual ~IDraw() = default;
  };
  struct Dot: IDraw {
    Dot(int x, int y);
    explicit Dot(p_t dd);
    p_t begin() const override;
    p_t next() const override;
    p_t d;
  };

}
int main()
{
  using namespace topit;
  IDraw * shps[3] = {};
  p_t * pts = nullptr;
  size_t s = 0;
  int err = 0;
  try {
    shps[0] = new Dot(0,0);
    shps[1] = new Dot(5,7);
    shps[2] = new Dot(-5,-2);
  } catch (...) {
    err = 2;
    std::cerr << "bad drawing\n";
  }
  delete shps[0];
  delete shps[1];
  delete shps[2];
  delete[] pts;
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
    throw std::logic_error("bad impl\n");
  }
  return d;
}
topit::Dot::Dot(p_t dd):
  IDraw(), d{dd}
{}
