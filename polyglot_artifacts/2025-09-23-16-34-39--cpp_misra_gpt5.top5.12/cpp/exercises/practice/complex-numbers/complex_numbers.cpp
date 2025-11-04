#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept
    : re_(0.0), im_(0.0) {}

Complex::Complex(double real, double imag) noexcept
    : re_(real), im_(imag) {}

double Complex::real() const noexcept {
    return re_;
}

double Complex::imag() const noexcept {
    return im_;
}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex((re_ + other.re_), (im_ + other.im_));
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex((re_ - other.re_), (im_ - other.im_));
}

Complex Complex::operator*(const Complex& other) const noexcept {
    const double real_part = ((re_ * other.re_) - (im_ * other.im_));
    const double imag_part = ((im_ * other.re_) + (re_ * other.im_));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    const double denom = ((other.re_ * other.re_) + (other.im_ * other.im_));
    const double real_part = (((re_ * other.re_) + (im_ * other.im_)) / denom);
    const double imag_part = (((im_ * other.re_) - (re_ * other.im_)) / denom);
    return Complex(real_part, imag_part);
}

Complex Complex::conj() const noexcept {
    return Complex(re_, (0.0 - im_));
}

double Complex::abs() const noexcept {
    return std::sqrt(((re_ * re_) + (im_ * im_)));
}

Complex Complex::exp() const noexcept {
    const double e_to_a = std::exp(re_);
    const double real_part = (e_to_a * std::cos(im_));
    const double imag_part = (e_to_a * std::sin(im_));
    return Complex(real_part, imag_part);
}

// Scalar operations

Complex operator+(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() + rhs), lhs.imag());
}

Complex operator+(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() - rhs), lhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs - rhs.real()), (0.0 - rhs.imag()));
}

Complex operator*(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(const Complex& lhs, double rhs) noexcept {
    const double inv = (1.0 / rhs);
    return Complex((lhs.real() * inv), (lhs.imag() * inv));
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    const double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    const double real_part = ((lhs * rhs.real()) / denom);
    const double imag_part = (((0.0 - lhs) * rhs.imag()) / denom);
    return Complex(real_part, imag_part);
}

// Free-function utilities

Complex conj(const Complex& c) noexcept {
    return c.conj();
}

double abs(const Complex& c) noexcept {
    return c.abs();
}

Complex exp(const Complex& c) noexcept {
    return c.exp();
}

}  // namespace complex_numbers
