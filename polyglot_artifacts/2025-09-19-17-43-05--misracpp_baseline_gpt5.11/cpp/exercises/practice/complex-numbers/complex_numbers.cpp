#include "complex_numbers.h"

#include <cmath>
#include <ostream>

namespace complex_numbers {

Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

double Complex::real() const {
    return re_;
}

double Complex::imag() const {
    return im_;
}

// Complex-Complex arithmetic
Complex Complex::operator+(const Complex& other) const {
    return Complex(re_ + other.re_, im_ + other.im_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(re_ - other.re_, im_ - other.im_);
}

Complex Complex::operator*(const Complex& other) const {
    // (a + i*b) * (c + i*d) = (a*c - b*d) + (b*c + a*d) * i
    const double a = re_;
    const double b = im_;
    const double c = other.re_;
    const double d = other.im_;
    return Complex(a * c - b * d, b * c + a * d);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + i*b) / (c + i*d) = ((a*c + b*d) + (b*c - a*d) * i) / (c^2 + d^2)
    const double a = re_;
    const double b = im_;
    const double c = other.re_;
    const double d = other.im_;
    const double denom = c * c + d * d;
    return Complex((a * c + b * d) / denom, (b * c - a * d) / denom);
}

// Complex-scalar arithmetic (rhs scalar)
Complex Complex::operator+(double value) const {
    return Complex(re_ + value, im_);
}

Complex Complex::operator-(double value) const {
    return Complex(re_ - value, im_);
}

Complex Complex::operator*(double value) const {
    return Complex(re_ * value, im_ * value);
}

Complex Complex::operator/(double value) const {
    return Complex(re_ / value, im_ / value);
}

// Unary operations
Complex Complex::conj() const {
    return Complex(re_, -im_);
}

double Complex::abs() const {
    return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const {
    // e^(a + i*b) = e^a * (cos b + i sin b)
    const double ea = std::exp(re_);
    return Complex(ea * std::cos(im_), ea * std::sin(im_));
}

// Scalar-Complex arithmetic (lhs scalar)
Complex operator+(double value, const Complex& c) {
    return Complex(value + c.real(), c.imag());
}

Complex operator-(double value, const Complex& c) {
    // (x) - (a + i*b) = (x - a) + (-b) * i
    return Complex(value - c.real(), -c.imag());
}

Complex operator*(double value, const Complex& c) {
    return Complex(value * c.real(), value * c.imag());
}

Complex operator/(double value, const Complex& c) {
    // (x) / (a + i*b) = x * (a - i*b) / (a^2 + b^2)
    const double a = c.real();
    const double b = c.imag();
    const double denom = a * a + b * b;
    return Complex(value * a / denom, -value * b / denom);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << '(' << c.real() << (c.imag() < 0 ? " - i*" : " + i*") << std::abs(c.imag()) << ')';
    return os;
}

}  // namespace complex_numbers
