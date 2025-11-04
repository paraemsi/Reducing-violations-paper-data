#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() : real_(0.0), imag_(0.0) {}

Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

double Complex::real() const {
  return real_;
}

double Complex::imag() const {
  return imag_;
}

Complex Complex::operator+(const Complex& other) const {
  return Complex{real_ + other.real_, imag_ + other.imag_};
}

Complex Complex::operator-(const Complex& other) const {
  return Complex{real_ - other.real_, imag_ - other.imag_};
}

Complex Complex::operator*(const Complex& other) const {
  // (a + bi) * (c + di) = (ac - bd) + (bc + ad)i
  const double a = real_;
  const double b = imag_;
  const double c = other.real_;
  const double d = other.imag_;
  return Complex{a * c - b * d, b * c + a * d};
}

Complex Complex::operator/(const Complex& other) const {
  // (a + bi) / (c + di) = ((ac + bd)/(c^2 + d^2)) + ((bc - ad)/(c^2 + d^2)) i
  const double a = real_;
  const double b = imag_;
  const double c = other.real_;
  const double d = other.imag_;
  const double denom = c * c + d * d;
  return Complex{(a * c + b * d) / denom, (b * c - a * d) / denom};
}

Complex Complex::conj() const {
  return Complex{real_, -imag_};
}

double Complex::abs() const {
  return std::hypot(real_, imag_);
}

Complex Complex::exp() const {
  // e^(a + bi) = e^a * (cos b + i sin b)
  const double ea = std::exp(real_);
  return Complex{ea * std::cos(imag_), ea * std::sin(imag_)};
}

 // Overloads with real numbers
Complex operator+(double lhs, const Complex& rhs) {
  return Complex{lhs + rhs.real(), rhs.imag()};
}

Complex operator+(const Complex& lhs, double rhs) {
  return Complex{lhs.real() + rhs, lhs.imag()};
}

Complex operator-(double lhs, const Complex& rhs) {
  return Complex{lhs - rhs.real(), -rhs.imag()};
}

Complex operator-(const Complex& lhs, double rhs) {
  return Complex{lhs.real() - rhs, lhs.imag()};
}

Complex operator*(double lhs, const Complex& rhs) {
  return Complex{lhs * rhs.real(), lhs * rhs.imag()};
}

Complex operator*(const Complex& lhs, double rhs) {
  return Complex{lhs.real() * rhs, lhs.imag() * rhs};
}

Complex operator/(double lhs, const Complex& rhs) {
  const double c = rhs.real();
  const double d = rhs.imag();
  const double denom = c * c + d * d;
  return Complex{(lhs * c) / denom, (-lhs * d) / denom};
}

Complex operator/(const Complex& lhs, double rhs) {
  return Complex{lhs.real() / rhs, lhs.imag() / rhs};
}

// Non-member helpers
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
