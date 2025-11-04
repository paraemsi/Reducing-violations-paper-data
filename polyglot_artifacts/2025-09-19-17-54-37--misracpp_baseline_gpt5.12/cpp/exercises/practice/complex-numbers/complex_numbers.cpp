#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : r_(real), i_(imag) {}
Complex::Complex(double real) : r_(real), i_(0.0) {}

double Complex::real() const { return r_; }
double Complex::imag() const { return i_; }

Complex Complex::operator+(const Complex& other) const {
    return Complex(r_ + other.r_, i_ + other.i_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(r_ - other.r_, i_ - other.i_);
}

Complex Complex::operator*(const Complex& other) const {
    // (a + ib) * (c + id) = (ac - bd) + (bc + ad)i
    double a = r_, b = i_, c = other.r_, d = other.i_;
    return Complex(a * c - b * d, b * c + a * d);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + ib) / (c + id) = ((ac + bd) / (c^2 + d^2)) + ((bc - ad) / (c^2 + d^2)) i
    double a = r_, b = i_, c = other.r_, d = other.i_;
    double denom = c * c + d * d;
    return Complex((a * c + b * d) / denom, (b * c - a * d) / denom);
}

// Unary operators
Complex Complex::operator+() const {
    return *this;
}

Complex Complex::operator-() const {
    return Complex(-r_, -i_);
}

// Scalar (rhs) operations
Complex Complex::operator+(double value) const {
    return Complex(r_ + value, i_);
}

Complex Complex::operator-(double value) const {
    return Complex(r_ - value, i_);
}

Complex Complex::operator*(double value) const {
    return Complex(r_ * value, i_ * value);
}

Complex Complex::operator/(double value) const {
    return Complex(r_ / value, i_ / value);
}

Complex Complex::conjugate() const {
    return Complex(r_, -i_);
}

Complex Complex::conj() const {
    return Complex(r_, -i_);
}

double Complex::abs() const {
    return std::hypot(r_, i_);
}

Complex Complex::exp() const {
    // e^(a + ib) = e^a * (cos b + i sin b)
    double ea = std::exp(r_);
    return Complex(ea * std::cos(i_), ea * std::sin(i_));
}

// Free-function wrappers
Complex conjugate(const Complex& z) {
    return z.conjugate();
}

double abs(const Complex& z) {
    return z.abs();
}

// Free-function wrapper for exponent
Complex exp(const Complex& z) {
    return z.exp();
}

double real(const Complex& z) {
    return z.real();
}

double imag(const Complex& z) {
    return z.imag();
}

// Real scalar (lhs) operations
Complex operator+(double value, const Complex& z) {
    return Complex(value + z.real(), z.imag());
}

Complex operator-(double value, const Complex& z) {
    return Complex(value - z.real(), -z.imag());
}

Complex operator*(double value, const Complex& z) {
    return z * value;
}

Complex operator/(double value, const Complex& z) {
    const double a = z.real();
    const double b = z.imag();
    const double denom = a * a + b * b;
    return Complex((value * a) / denom, (-value * b) / denom);
}

}  // namespace complex_numbers
