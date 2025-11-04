#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

using std::cos;
using std::exp;
using std::sin;
using std::hypot;

/* member function definitions that require <cmath> */
double Complex::abs() const noexcept {
    return std::hypot(real_, imag_);
}

Complex Complex::operator/(const Complex& other) const {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    return {(real_ * other.real_ + imag_ * other.imag_) / denom,
            (imag_ * other.real_ - real_ * other.imag_) / denom};
}

Complex Complex::exp() const {
    double e_real = std::exp(real_);
    return {e_real * cos(imag_), e_real * sin(imag_)};
}

}  // namespace complex_numbers
