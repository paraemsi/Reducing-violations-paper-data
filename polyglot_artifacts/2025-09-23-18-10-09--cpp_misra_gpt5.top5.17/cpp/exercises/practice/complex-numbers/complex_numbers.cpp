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

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex((re_ + other.re_), (im_ + other.im_));
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex((re_ - other.re_), (im_ - other.im_));
}

Complex Complex::operator*(const Complex& other) const noexcept {
    double real = ((re_ * other.re_) - (im_ * other.im_));
    double imag = ((im_ * other.re_) + (re_ * other.im_));
    return Complex(real, imag);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    double denom = ((other.re_ * other.re_) + (other.im_ * other.im_));
    double real = (((re_ * other.re_) + (im_ * other.im_)) / denom);
    double imag = (((im_ * other.re_) - (re_ * other.im_)) / denom);
    return Complex(real, imag);
}

Complex Complex::conjugate() const noexcept {
    return Complex(re_, -im_);
}

Complex Complex::conj() const noexcept {
    return conjugate();
}

double Complex::abs() const noexcept {
    return std::sqrt((re_ * re_) + (im_ * im_));
}

Complex Complex::exp() const noexcept {
    double exp_real = std::exp(re_);
    return Complex((exp_real * std::cos(im_)), (exp_real * std::sin(im_)));
}

// Free-function overloads to interoperate with real numbers (double)
Complex operator+(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() + rhs), lhs.imag());
}

Complex operator+(double lhs, const Complex& rhs) noexcept {
    return (rhs + lhs);
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
    return (rhs * lhs);
}

Complex operator/(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    double real = (((lhs * rhs.real()) / denom));
    double imag = (((0.0 - (lhs * rhs.imag())) / denom));
    return Complex(real, imag);
}

Complex conjugate(const Complex& z) noexcept {
    return z.conjugate();
}

double abs(const Complex& z) noexcept {
    return z.abs();
}

Complex exp(const Complex& z) noexcept {
    return z.exp();
}

}  // namespace complex_numbers
