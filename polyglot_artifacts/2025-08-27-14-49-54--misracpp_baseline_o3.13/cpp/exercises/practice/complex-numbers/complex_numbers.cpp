#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(float real, float imag) : r_{real}, i_{imag} {}

float Complex::real() const { return r_; }
float Complex::imag() const { return i_; }

Complex Complex::operator+(const Complex& other) const {
  return Complex{r_ + other.r_, i_ + other.i_};
}

Complex Complex::operator-(const Complex& other) const {
  return Complex{r_ - other.r_, i_ - other.i_};
}

Complex Complex::operator*(const Complex& other) const {
  return Complex{r_ * other.r_ - i_ * other.i_,
                 i_ * other.r_ + r_ * other.i_};
}

Complex Complex::operator/(const Complex& other) const {
  float denominator = other.r_ * other.r_ + other.i_ * other.i_;
  return Complex{(r_ * other.r_ + i_ * other.i_) / denominator,
                 (i_ * other.r_ - r_ * other.i_) / denominator};
}

bool Complex::operator==(const Complex& other) const {
  constexpr float kEpsilon = 1e-6f;
  return std::fabs(r_ - other.r_) < kEpsilon &&
         std::fabs(i_ - other.i_) < kEpsilon;
}

bool Complex::operator!=(const Complex& other) const {
  return !(*this == other);
}

Complex Complex::conj() const {
  return Complex{r_, -i_};
}

float Complex::abs() const {
  return std::sqrt(r_ * r_ + i_ * i_);
}

Complex Complex::exp() const {
  float factor = std::exp(r_);
  return Complex{factor * std::cos(i_), factor * std::sin(i_)};
}

Complex operator+(double lhs, const Complex& rhs) {
  return Complex(static_cast<float>(lhs), 0.0f) + rhs;
}

Complex operator-(double lhs, const Complex& rhs) {
  return Complex(static_cast<float>(lhs), 0.0f) - rhs;
}

Complex operator*(double lhs, const Complex& rhs) {
  return Complex(static_cast<float>(lhs), 0.0f) * rhs;
}

Complex operator/(double lhs, const Complex& rhs) {
  return Complex(static_cast<float>(lhs), 0.0f) / rhs;
}

Complex operator+(const Complex& lhs, double rhs) {
  return lhs + Complex(static_cast<float>(rhs), 0.0f);
}

Complex operator-(const Complex& lhs, double rhs) {
  return lhs - Complex(static_cast<float>(rhs), 0.0f);
}

Complex operator*(const Complex& lhs, double rhs) {
  return lhs * Complex(static_cast<float>(rhs), 0.0f);
}

Complex operator/(const Complex& lhs, double rhs) {
  return lhs / Complex(static_cast<float>(rhs), 0.0f);
}

Complex conj(const Complex& value) { return value.conj(); }
float   abs (const Complex& value) { return value.abs();  }
Complex exp (const Complex& value) { return value.exp();  }

}  // namespace complex_numbers
