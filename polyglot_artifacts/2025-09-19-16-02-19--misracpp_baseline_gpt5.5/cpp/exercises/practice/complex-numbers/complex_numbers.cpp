#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() : re_(0.0), im_(0.0) {}
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
    // (a + ib) * (c + id) = (ac - bd) + (bc + ad)i
    double a = re_, b = im_, c = other.re_, d = other.im_;
    return Complex(a * c - b * d, b * c + a * d);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + ib) / (c + id) = ((ac + bd) / (c^2 + d^2)) + ((bc - ad) / (c^2 + d^2)) i
    double a = re_, b = im_, c = other.re_, d = other.im_;
    double den = c * c + d * d;
    return Complex((a * c + b * d) / den, (b * c - a * d) / den);
}

Complex Complex::conj() const {
    return Complex(re_, -im_);
}

double Complex::abs() const {
    return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const {
    // e^(a + ib) = e^a * (cos b + i sin b)
    double ea = std::exp(re_);
    return Complex(ea * std::cos(im_), ea * std::sin(im_));
}

// Operations with real numbers (double)

Complex operator+(const Complex& z, double d) {
    return Complex(z.real() + d, z.imag());
}

Complex operator+(double d, const Complex& z) {
    return z + d;
}

Complex operator-(const Complex& z, double d) {
    return Complex(z.real() - d, z.imag());
}

Complex operator-(double d, const Complex& z) {
    // (d + 0i) - (a + bi) = (d - a) + (-b)i
    return Complex(d - z.real(), -z.imag());
}

Complex operator*(const Complex& z, double d) {
    return Complex(z.real() * d, z.imag() * d);
}

Complex operator*(double d, const Complex& z) {
    return z * d;
}

Complex operator/(const Complex& z, double d) {
    return Complex(z.real() / d, z.imag() / d);
}

Complex operator/(double d, const Complex& z) {
    // (d + 0i) / (a + bi) = (d*a)/(a^2 + b^2) + (-d*b)/(a^2 + b^2) i
    double a = z.real();
    double b = z.imag();
    double den = a * a + b * b;
    return Complex(d * a / den, -d * b / den);
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
