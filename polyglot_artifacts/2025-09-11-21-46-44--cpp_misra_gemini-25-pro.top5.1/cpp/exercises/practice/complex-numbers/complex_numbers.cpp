#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {


real_t Complex::abs() const noexcept {
    return std::sqrt(((real_ * real_) + (imag_ * imag_)));
}

Complex Complex::exp() const noexcept {
    const real_t r = (std::exp(real_) * std::cos(imag_));
    const real_t i = (std::exp(real_) * std::sin(imag_));
    return Complex(r, i);
}


}  // namespace complex_numbers
