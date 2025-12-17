#include Diag45.hpp
#include <stdexcept>
topit::Diag45::Diag45(int x1, int y1, int x2, int y2):
  IDraw(), a{x1, y1}, b{x2, y2}
{
  int dx = x1 - x2;
  int dy = y1 - y2;
  if (std::abs(dx) != std::abs(dy)) {
    throw std::logic_error("its not 45 degree segment\n");
  }
}
topit::p_t topit::Diag45::begin() const
{
  return a;
}
topit::p_t topit::Diag45::next(p_t prev) const
{
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    int step_x = (dx > 0) ? 1 : -1;
    int step_y = (dy > 0) ? 1 : -1;
    int kx = prev.x - a.x;
    int ky = prev.y - a.y;
    if (kx * step_x < 0 || ky * step_y < 0 ||
        std::abs(kx) != std::abs(ky) ||
        std::abs(kx) > std::abs(dx)) {
      throw std::logic_error("Diag45 bad prev");
    }
    if (prev == b) {
      return prev;
    }
    return p_t{ prev.x + step_x, prev.y + step_y };
}
