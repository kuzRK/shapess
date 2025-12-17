#ifndef HSEG_HPP
#define HSEG_HPP
#include "idraw.hpp"
namespace topit {
  struct HSeg: IDraw {
    HSeg(int x1, int y1, int x2, int y2);
    explicit HSeg(p_t a_, p_t b_);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a;
    p_t b;
  };
}
#endif

