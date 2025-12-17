#ifndef DIAG45_HPP
#define DIAG45_HPP
#include "idraw.hpp"
namespace topit {
  struct Diag45: IDraw {
    explicit Diag45(p_t a_, p_t b_);
    Diag45(int x1, int y1, int x2, int y2);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a;
    p_t b;
  };
}
#endif

