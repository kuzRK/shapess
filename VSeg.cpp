#include "VSeg.hpp"
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
topit::p_t topit::VSeg::begin() const
{
  return a;
}
topit::p_t topit::VSeg::next(p_t prev) const
{
  if (prev == b) {
    return b;
  }
  if (prev.x != a.x) {
    throw std::logic_error("bad impl");
  }
  int next_y = (b.y > a.y) ? prev.y + 1 : prev.y - 1;
  if ((b.y > a.y && next_y > b.y) || (b.y < a.y && next_y < b.y)) {
    return b;
  }
  return {a.x, next_y};
}
