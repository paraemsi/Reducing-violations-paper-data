#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() : re_(0.0), im_(0.0) {}

Complex::Complex(double real) : re_(real), im_(0.0) {}

Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

double Complex::real() const { return re_; }
double Complex::imag() const { return im_; }

Complex Complex::conj() const { return Complex(re_, -im_); }

double Complex::abs() const { return std::sqrt(re_ * re_ + im_ * im_); }

Complex Complex::exp() const {
    const double factor = std::exp(re_);
    return Complex(factor * std::cos(im_), factor * std::sin(im_));
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

Complex Complex::operator+(double rhs) const {
    return Complex(re_ + rhs, im_);
}

Complex Complex::operator-(double rhs) const {
    return Complex(re_ - rhs, im_);
}

Complex Complex::operator*(double rhs) const {
    return Complex(re_ * rhs, im_ * rhs);
}

Complex Complex::operator/(double rhs) const {
    return Complex(re_ / rhs, im_ / rhs);
}

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
    const double c = rhs.real();
    const double d = rhs.imag();
    const double denom = c * c + d * d;
    return Complex((lhs * c) / denom, (-lhs * d) / denom);
}

}  // namespace complex_numbers
