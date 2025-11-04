#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() : real_(0.0), imag_(0.0) {}
Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }

Complex Complex::operator+(const Complex& other) const {
  return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
  return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
  return Complex(real_ * other.real_ - imag_ * other.imag_,
                 imag_ * other.real_ + real_ * other.imag_);
}

Complex Complex::operator/(const Complex& other) const {
  const double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
  return Complex((real_ * other.real_ + imag_ * other.imag_) / denom,
                 (imag_ * other.real_ - real_ * other.imag_) / denom);
}

Complex Complex::conj() const { return Complex(real_, -imag_); }

double Complex::abs() const { return std::sqrt(real_ * real_ + imag_ * imag_); }

Complex Complex::exp() const {
  const double ea = std::exp(real_);
  return Complex(ea * std::cos(imag_), ea * std::sin(imag_));
}

Complex operator+(double lhs, const Complex& rhs) {
  return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
  return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator*(double lhs, const Complex& rhs) {
  return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator/(double lhs, const Complex& rhs) {
  const double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
  return Complex((lhs * rhs.real()) / denom, (-lhs * rhs.imag()) / denom);
}

double real(const Complex& z) {
  return z.real();
}

double imag(const Complex& z) {
  return z.imag();
}

Complex conj(const Complex& z) {
  return z.conj();
}

double abs(const Complex& z) {
  return z.abs();
}

Complex exp(const Complex& z) {
  return z.exp();
}

}  // namespace complex_numbers
