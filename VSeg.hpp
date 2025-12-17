#ifndef VSEG_HPP
#define VSEG_HPP
#include "idraw.hpp"
namespace topit {
  struct VSeg: IDraw {
    explicit VSeg(p_t a_, p_t b_);
    VSeg(int x1, int y1, int x2, int y2);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a;
    p_t b;
   };
}
#endif
