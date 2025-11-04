#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

double Complex::real() const { return re_; }
double Complex::imag() const { return im_; }

Complex Complex::conj() const { return Complex(re_, -im_); }

double Complex::abs() const { return std::hypot(re_, im_); }

Complex Complex::exp() const {
    const double ea = std::exp(re_);
    return Complex(ea * std::cos(im_), ea * std::sin(im_));
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

Complex operator+(double value, const Complex& z) {
    return Complex(value + z.re_, z.im_);
}

Complex operator-(double value, const Complex& z) {
    return Complex(value - z.re_, -z.im_);
}

Complex operator*(double value, const Complex& z) {
    return Complex(value * z.re_, value * z.im_);
}

Complex operator/(double value, const Complex& z) {
    const double denom = z.re_ * z.re_ + z.im_ * z.im_;
    return Complex((value * z.re_) / denom, (-value * z.im_) / denom);
}

Complex conj(const Complex& z) { return z.conj(); }
double abs(const Complex& z) { return z.abs(); }
Complex exp(const Complex& z) { return z.exp(); }

}  // namespace complex_numbers
