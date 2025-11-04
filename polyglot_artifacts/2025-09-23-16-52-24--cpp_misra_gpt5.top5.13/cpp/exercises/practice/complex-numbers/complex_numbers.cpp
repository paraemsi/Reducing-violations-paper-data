#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept : re_(0.0), im_(0.0) {}
Complex::Complex(double real, double imag) noexcept : re_(real), im_(imag) {}

double Complex::real() const noexcept {
    return re_;
}

double Complex::imag() const noexcept {
    return im_;
}

Complex Complex::conj() const noexcept {
    return Complex(re_, (-im_));
}

double Complex::abs() const noexcept {
    return std::sqrt(((re_ * re_) + (im_ * im_)));
}

Complex Complex::exp() const noexcept {
    const double ea = std::exp(re_);
    const double cosb = std::cos(im_);
    const double sinb = std::sin(im_);
    return Complex((ea * cosb), (ea * sinb));
}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex((re_ + other.re_), (im_ + other.im_));
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex((re_ - other.re_), (im_ - other.im_));
}

Complex Complex::operator*(const Complex& other) const noexcept {
    return Complex(((re_ * other.re_) - (im_ * other.im_)), ((im_ * other.re_) + (re_ * other.im_)));
}

Complex Complex::operator/(const Complex& other) const noexcept {
    const double denom = ((other.re_ * other.re_) + (other.im_ * other.im_));
    return Complex((((re_ * other.re_) + (im_ * other.im_)) / denom), (((im_ * other.re_) - (re_ * other.im_)) / denom));
}

// Scalar operations with double

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
    return Complex((lhs - rhs.real()), (-rhs.imag()));
}

Complex operator*(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    const double a = rhs.real();
    const double b = rhs.imag();
    const double denom = ((a * a) + (b * b));
    return Complex(((lhs * a) / denom), ((-lhs * b) / denom));
}

Complex operator+(const Complex& value) noexcept {
    return Complex(value.real(), value.imag());
}

Complex operator-(const Complex& value) noexcept {
    return Complex((-value.real()), (-value.imag()));
}

}  // namespace complex_numbers
