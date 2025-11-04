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

Complex Complex::operator+(double value) const {
    return Complex(re_ + value, im_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(re_ - other.re_, im_ - other.im_);
}

Complex Complex::operator-(double value) const {
    return Complex(re_ - value, im_);
}

Complex Complex::operator*(const Complex& other) const {
    // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
    double real = re_ * other.re_ - im_ * other.im_;
    double imag = re_ * other.im_ + im_ * other.re_;
    return Complex(real, imag);
}

Complex Complex::operator*(double value) const {
    return Complex(re_ * value, im_ * value);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + bi) / (c + di) = [(ac + bd) + (bc - ad)i] / (c^2 + d^2)
    double denom = other.re_ * other.re_ + other.im_ * other.im_;
    double real = (re_ * other.re_ + im_ * other.im_) / denom;
    double imag = (im_ * other.re_ - re_ * other.im_) / denom;
    return Complex(real, imag);
}

Complex Complex::operator/(double value) const {
    return Complex(re_ / value, im_ / value);
}

// Non-member friend functions for double op Complex
Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.re_, rhs.im_);
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.re_, -rhs.im_);
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.re_, lhs * rhs.im_);
}

Complex operator/(double lhs, const Complex& rhs) {
    // (a) / (c + di) = (a * c)/(c^2 + d^2) - (a * d)/(c^2 + d^2) * i
    double denom = rhs.re_ * rhs.re_ + rhs.im_ * rhs.im_;
    double real = lhs * rhs.re_ / denom;
    double imag = -lhs * rhs.im_ / denom;
    return Complex(real, imag);
}

Complex Complex::conj() const {
    return Complex(re_, -im_);
}

double Complex::abs() const {
    return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const {
    // e^(a + bi) = e^a * (cos(b) + i sin(b))
    double exp_real = std::exp(re_);
    return Complex(exp_real * std::cos(im_), exp_real * std::sin(im_));
}

}  // namespace complex_numbers
