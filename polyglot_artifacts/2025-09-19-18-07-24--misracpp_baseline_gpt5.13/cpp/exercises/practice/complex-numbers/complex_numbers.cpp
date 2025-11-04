#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

double Complex::real() const { return re_; }
double Complex::imag() const { return im_; }

Complex Complex::operator+(const Complex& other) const {
  return Complex(re_ + other.re_, im_ + other.im_);
}

Complex Complex::operator-(const Complex& other) const {
  return Complex(re_ - other.re_, im_ - other.im_);
}

Complex Complex::operator*(const Complex& other) const {
  return Complex(re_ * other.re_ - im_ * other.im_,
                 im_ * other.re_ + re_ * other.im_);
}

Complex Complex::operator/(const Complex& other) const {
  double denom = other.re_ * other.re_ + other.im_ * other.im_;
  return Complex((re_ * other.re_ + im_ * other.im_) / denom,
                 (im_ * other.re_ - re_ * other.im_) / denom);
}

Complex Complex::conj() const {
  return Complex(re_, -im_);
}

double Complex::abs() const {
  return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const {
  double e_to_a = std::exp(re_);
  return Complex(e_to_a * std::cos(im_), e_to_a * std::sin(im_));
}

 // Free function wrappers
Complex conj(const Complex& z) { return z.conj(); }
double abs(const Complex& z) { return z.abs(); }
Complex exp(const Complex& z) { return z.exp(); }

// Operators with double on the left-hand side
Complex operator+(double lhs, const Complex& rhs) {
  return Complex(lhs, 0.0) + rhs;
}
Complex operator-(double lhs, const Complex& rhs) {
  return Complex(lhs, 0.0) - rhs;
}
Complex operator*(double lhs, const Complex& rhs) {
  return Complex(lhs, 0.0) * rhs;
}
Complex operator/(double lhs, const Complex& rhs) {
  return Complex(lhs, 0.0) / rhs;
}

}  // namespace complex_numbers
