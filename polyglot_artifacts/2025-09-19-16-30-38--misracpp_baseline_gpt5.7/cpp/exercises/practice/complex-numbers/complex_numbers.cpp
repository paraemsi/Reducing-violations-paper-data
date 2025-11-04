#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

Complex::Complex() : re_(0.0), im_(0.0) {}

Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

double Complex::real() const { return re_; }

double Complex::imag() const { return im_; }

Complex Complex::conj() const { return Complex(re_, -im_); }

double Complex::abs() const { return std::hypot(re_, im_); }

Complex Complex::exp() const {
    // e^(a + i b) = e^a * (cos b + i sin b)
    const double ea = std::exp(re_);
    return Complex(ea * std::cos(im_), ea * std::sin(im_));
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.real() + rhs.real(), lhs.imag() + rhs.imag());
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.real() - rhs.real(), lhs.imag() - rhs.imag());
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
    const double a = lhs.real();
    const double b = lhs.imag();
    const double c = rhs.real();
    const double d = rhs.imag();
    return Complex(a * c - b * d, b * c + a * d);
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    const double a = lhs.real();
    const double b = lhs.imag();
    const double c = rhs.real();
    const double d = rhs.imag();
    const double denom = c * c + d * d;
    return Complex((a * c + b * d) / denom, (b * c - a * d) / denom);
}

Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real() + rhs, lhs.imag());
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real() - rhs, lhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real() * rhs, lhs.imag() * rhs);
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real() / rhs, lhs.imag() / rhs);
}

Complex operator/(double lhs, const Complex& rhs) {
    const double a = rhs.real();
    const double b = rhs.imag();
    const double denom = a * a + b * b;
    return Complex((lhs * a) / denom, (-lhs * b) / denom);
}

}  // namespace complex_numbers
