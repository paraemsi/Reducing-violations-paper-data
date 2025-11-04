#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

double Complex::real() const {
    return re_;
}

double Complex::imag() const {
    return im_;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(re_ + other.re_, im_ + other.im_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(re_ - other.re_, im_ - other.im_);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(re_ * other.re_ - im_ * other.im_,
                   im_ * other.re_ + re_ * other.im_);
}

Complex Complex::operator/(const Complex& other) const {
    const double denom = other.re_ * other.re_ + other.im_ * other.im_;
    return Complex((re_ * other.re_ + im_ * other.im_) / denom,
                   (im_ * other.re_ - re_ * other.im_) / denom);
}

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

Complex Complex::conj() const {
    return Complex(re_, -im_);
}

double Complex::abs() const {
    return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const {
    // e^(a + i b) = e^a * (cos b + i sin b)
    const double expa = std::exp(re_);
    return Complex(expa * std::cos(im_), expa * std::sin(im_));
}

Complex operator+(double value, const Complex& z) {
    return Complex(value + z.real(), z.imag());
}

Complex operator-(double value, const Complex& z) {
    // value - (a + bi) = (value - a) + (-b)i
    return Complex(value - z.real(), -z.imag());
}

Complex operator*(double value, const Complex& z) {
    return Complex(value * z.real(), value * z.imag());
}

Complex operator/(double value, const Complex& z) {
    // value / (a + bi) = value * (a - bi) / (a^2 + b^2)
    const double denom = z.real() * z.real() + z.imag() * z.imag();
    return Complex(value * z.real() / denom, -value * z.imag() / denom);
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

double real(const Complex& z) {
    return z.real();
}

double imag(const Complex& z) {
    return z.imag();
}

}  // namespace complex_numbers
