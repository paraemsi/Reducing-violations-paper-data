#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept : re_(0.0), im_(0.0) {}

Complex::Complex(double real, double imag) noexcept : re_(real), im_(imag) {}

double Complex::real() const noexcept { return re_; }
double Complex::imag() const noexcept { return im_; }

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex(re_ + other.re_, im_ + other.im_);
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex(re_ - other.re_, im_ - other.im_);
}

Complex Complex::operator*(const Complex& other) const noexcept {
    // (a + i b) * (c + i d) = (ac - bd) + (bc + ad) i
    double a = re_, b = im_;
    double c = other.re_, d = other.im_;
    return Complex(a * c - b * d, b * c + a * d);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    // (a + i b) / (c + i d) = (ac + bd)/(c^2 + d^2) + (bc - ad)/(c^2 + d^2) i
    double a = re_, b = im_;
    double c = other.re_, d = other.im_;
    double denom = c * c + d * d;
    return Complex((a * c + b * d) / denom, (b * c - a * d) / denom);
}

Complex Complex::conj() const noexcept {
    return Complex(re_, -im_);
}

double Complex::abs() const noexcept {
    return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const noexcept {
    // e^(a + i b) = e^a * (cos b + i sin b)
    double ea = std::exp(re_);
    return Complex(ea * std::cos(im_), ea * std::sin(im_));
}

// Scalar operations with double

Complex operator+(const Complex& z, double d) noexcept {
    return Complex(z.real() + d, z.imag());
}

Complex operator+(double d, const Complex& z) noexcept {
    return z + d;
}

Complex operator-(const Complex& z, double d) noexcept {
    return Complex(z.real() - d, z.imag());
}

Complex operator-(double d, const Complex& z) noexcept {
    return Complex(d - z.real(), -z.imag());
}

Complex operator*(const Complex& z, double d) noexcept {
    return Complex(z.real() * d, z.imag() * d);
}

Complex operator*(double d, const Complex& z) noexcept {
    return z * d;
}

Complex operator/(const Complex& z, double d) noexcept {
    return Complex(z.real() / d, z.imag() / d);
}

Complex operator/(double d, const Complex& z) noexcept {
    // d / (a + i b) = d * (a - i b) / (a^2 + b^2)
    double a = z.real(), b = z.imag();
    double denom = a * a + b * b;
    return Complex(d * a / denom, -d * b / denom);
}

// Free function helpers

Complex conj(const Complex& z) noexcept {
    return z.conj();
}

double abs(const Complex& z) noexcept {
    return z.abs();
}

Complex exp(const Complex& z) noexcept {
    return z.exp();
}

}  // namespace complex_numbers
