#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

double Complex::abs() const {
  return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::operator/(const Complex& other) const {
  const double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
  return {(real_ * other.real_ + imag_ * other.imag_) / denom,
          (imag_ * other.real_ - real_ * other.imag_) / denom};
}

Complex Complex::exp() const {
  // e^(a + i b) = e^a * (cos b + i sin b)
  const double factor = std::exp(real_);
  return {factor * std::cos(imag_), factor * std::sin(imag_)};
}

// Free operators with scalar on the left-hand side
Complex operator+(double lhs, const Complex& rhs) {
  return {lhs + rhs.real(), rhs.imag()};
}

Complex operator-(double lhs, const Complex& rhs) {
  return {lhs - rhs.real(), -rhs.imag()};
}

Complex operator*(double lhs, const Complex& rhs) {
  return {lhs * rhs.real(), lhs * rhs.imag()};
}

Complex operator/(double lhs, const Complex& rhs) {
  const double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
  return {(lhs * rhs.real()) / denom, (-lhs * rhs.imag()) / denom};
}

// Free function wrappers
Complex conj(const Complex& z) { return z.conj(); }
double  abs(const Complex& z)  { return z.abs(); }
Complex exp(const Complex& z)  { return z.exp(); }

}  // namespace complex_numbers
