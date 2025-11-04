#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

// Constructors
Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

// Accessors
double Complex::real() const { return re_; }
double Complex::imag() const { return im_; }

// Arithmetic between complex numbers
Complex Complex::operator+(const Complex& other) const {
    return Complex(re_ + other.re_, im_ + other.im_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(re_ - other.re_, im_ - other.im_);
}

Complex Complex::operator*(const Complex& other) const {
    // (a + ib) * (c + id) = (ac - bd) + (bc + ad)i
    double a = re_, b = im_;
    double c = other.re_, d = other.im_;
    return Complex(a * c - b * d, b * c + a * d);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + ib) / (c + id) = [(ac + bd) + (bc - ad)i] / (c^2 + d^2)
    double a = re_, b = im_;
    double c = other.re_, d = other.im_;
    double denom = c * c + d * d;
    return Complex((a * c + b * d) / denom, (b * c - a * d) / denom);
}

// Member versions of additional operations
Complex Complex::conj() const {
    return complex_numbers::conj(*this);
}

double Complex::abs() const {
    return complex_numbers::abs(*this);
}

Complex Complex::exp() const {
    return complex_numbers::exp(*this);
}

// Arithmetic with scalars (double)
Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real() + rhs, lhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real() - rhs, lhs.imag());
}

Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real() * rhs, lhs.imag() * rhs);
}

Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real() / rhs, lhs.imag() / rhs);
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
    // lhs / (c + id) = lhs * (c - id) / (c^2 + d^2)
    double c = rhs.real(), d = rhs.imag();
    double denom = c * c + d * d;
    return Complex((lhs * c) / denom, (-lhs * d) / denom);
}

// Additional operations
Complex conj(const Complex& c) {
    return Complex(c.real(), -c.imag());
}

double abs(const Complex& c) {
    // Use hypot for numerical stability: sqrt(x*x + y*y)
    return std::hypot(c.real(), c.imag());
}

Complex exp(const Complex& c) {
    // e^(a + ib) = e^a * (cos b + i sin b)
    double a = c.real();
    double b = c.imag();
    double factor = std::exp(a);
    return Complex(factor * std::cos(b), factor * std::sin(b));
}

}  // namespace complex_numbers
