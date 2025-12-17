#include "HSeg.hpp"
#include <stdexcept>
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
topit::p_t topit::HrzLine::begin() const
{
  return a;
}
topit::p_t topit::HrzLine::next(p_t prev) const
{
  if (prev == b) {
    return b;
  }
  if (prev.y != a.y) {
    throw std::logic_error("bad impl");
  }
  int next_x = (b.x > a.x) ? prev.x + 1 : prev.x - 1;
  if ((b.x > a.x && next_x > b.x) || (b.x < a.x && next_x < b.x)) {
    return b;
  }
  return {next_x, a.y};
}
