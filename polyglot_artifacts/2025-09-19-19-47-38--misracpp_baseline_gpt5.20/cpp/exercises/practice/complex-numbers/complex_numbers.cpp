#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept : re_(0.0), im_(0.0) {}
Complex::Complex(double real) noexcept : re_(real), im_(0.0) {}
Complex::Complex(double real, double imag) noexcept : re_(real), im_(imag) {}

double Complex::real() const noexcept {
    return re_;
}

double Complex::imag() const noexcept {
    return im_;
}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex(re_ + other.re_, im_ + other.im_);
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex(re_ - other.re_, im_ - other.im_);
}

Complex Complex::operator*(const Complex& other) const noexcept {
    // (a + ib) * (c + id) = (ac - bd) + (bc + ad)i
    const double a = re_;
    const double b = im_;
    const double c = other.re_;
    const double d = other.im_;
    return Complex(a * c - b * d, b * c + a * d);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    // (a + ib) / (c + id) = (ac + bd)/(c^2 + d^2) + (bc - ad)/(c^2 + d^2)i
    const double a = re_;
    const double b = im_;
    const double c = other.re_;
    const double d = other.im_;
    const double denom = c * c + d * d;
    return Complex((a * c + b * d) / denom, (b * c - a * d) / denom);
}

Complex Complex::conj() const noexcept {
    return Complex(re_, -im_);
}

double Complex::abs() const noexcept {
    return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const noexcept {
    // e^(a + ib) = e^a * (cos b + i sin b)
    const double e_a = std::exp(re_);
    return Complex(e_a * std::cos(im_), e_a * std::sin(im_));
}

// Mixed-type operators

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
    // (d + 0i) / z
    return Complex(d, 0.0) / z;
}

// Free-function helpers
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
