#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() : re_(0.0), im_(0.0) {}
Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

double Complex::real() const {
    return re_;
}

double Complex::imag() const {
    return im_;
}

Complex Complex::conjugate() const {
    return Complex(re_, -im_);
}

Complex Complex::conj() const {
    return Complex(re_, -im_);
}

double Complex::abs() const {
    return std::hypot(re_, im_);
}

Complex Complex::exp() const {
    const double e_to_real = std::exp(re_);
    return Complex(e_to_real * std::cos(im_), e_to_real * std::sin(im_));
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

// Operations with a real scalar on the right-hand side
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

// Operations with a real scalar on the left-hand side
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
    const double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return Complex((lhs * rhs.real()) / denom, (-lhs * rhs.imag()) / denom);
}

}  // namespace complex_numbers
