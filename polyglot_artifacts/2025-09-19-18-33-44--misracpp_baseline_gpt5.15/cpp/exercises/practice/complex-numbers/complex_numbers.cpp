#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() = default;
Complex::Complex(double real) : real_(real), imag_(0) {}
Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }

double Complex::abs() const {
    return complex_numbers::abs(*this);
}

Complex Complex::conj() const {
    return complex_numbers::conj(*this);
}

Complex Complex::exp() const {
    return complex_numbers::exp(*this);
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(
        real_ * other.real_ - imag_ * other.imag_,
        imag_ * other.real_ + real_ * other.imag_);
}

Complex Complex::operator/(const Complex& other) const {
    const double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    return Complex(
        (real_ * other.real_ + imag_ * other.imag_) / denom,
        (imag_ * other.real_ - real_ * other.imag_) / denom);
}

Complex Complex::operator+(double value) const {
    return Complex(real_ + value, imag_);
}

Complex Complex::operator-(double value) const {
    return Complex(real_ - value, imag_);
}

Complex Complex::operator*(double value) const {
    return Complex(real_ * value, imag_ * value);
}

Complex Complex::operator/(double value) const {
    return Complex(real_ / value, imag_ / value);
}

Complex operator+(double value, const Complex& self) {
    return self + value;
}

Complex operator-(double value, const Complex& self) {
    return Complex(value - self.real(), -self.imag());
}

Complex operator*(double value, const Complex& self) {
    return self * value;
}

Complex operator/(double value, const Complex& self) {
    const double denom = self.real() * self.real() + self.imag() * self.imag();
    return Complex(value * self.real() / denom, -value * self.imag() / denom);
}

Complex conj(const Complex& z) {
    return Complex(z.real(), -z.imag());
}

double abs(const Complex& z) {
    return std::hypot(z.real(), z.imag());
}

Complex exp(const Complex& z) {
    const double exp_real = std::exp(z.real());
    return Complex(exp_real * std::cos(z.imag()), exp_real * std::sin(z.imag()));
}

}  // namespace complex_numbers
