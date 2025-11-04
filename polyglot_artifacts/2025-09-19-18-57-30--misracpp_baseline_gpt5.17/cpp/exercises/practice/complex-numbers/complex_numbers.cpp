#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

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
    return Complex(re_ * other.re_ - im_ * other.im_,
                   im_ * other.re_ + re_ * other.im_);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    const double den = other.re_ * other.re_ + other.im_ * other.im_;
    return Complex((re_ * other.re_ + im_ * other.im_) / den,
                   (im_ * other.re_ - re_ * other.im_) / den);
}

Complex Complex::conj() const noexcept { return Complex(re_, -im_); }

double Complex::abs() const noexcept { return std::sqrt(re_ * re_ + im_ * im_); }

Complex Complex::exp() const noexcept {
    const double exp_real = std::exp(re_);
    return Complex(exp_real * std::cos(im_), exp_real * std::sin(im_));
}

// Scalar overloads
Complex operator+(const Complex& z, double r) noexcept {
    return Complex(z.real() + r, z.imag());
}

Complex operator+(double r, const Complex& z) noexcept {
    return z + r;
}

Complex operator-(const Complex& z, double r) noexcept {
    return Complex(z.real() - r, z.imag());
}

Complex operator-(double r, const Complex& z) noexcept {
    return Complex(r - z.real(), -z.imag());
}

Complex operator*(const Complex& z, double r) noexcept {
    return Complex(z.real() * r, z.imag() * r);
}

Complex operator*(double r, const Complex& z) noexcept {
    return z * r;
}

Complex operator/(const Complex& z, double r) noexcept {
    return Complex(z.real() / r, z.imag() / r);
}

Complex operator/(double r, const Complex& z) noexcept {
    const double den = z.real() * z.real() + z.imag() * z.imag();
    return Complex(r * z.real() / den, -r * z.imag() / den);
}

}  // namespace complex_numbers
