#include "complex_numbers.h"

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
    // (a + bi) * (c + di) = (ac - bd) + (bc + ad)i
    double real = re_ * other.re_ - im_ * other.im_;
    double imag = im_ * other.re_ + re_ * other.im_;
    return Complex(real, imag);
}

Complex Complex::operator*(double value) const {
    return Complex(re_ * value, im_ * value);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + bi) / (c + di) = [(ac + bd) / (c^2 + d^2)] + [(bc - ad) / (c^2 + d^2)]i
    double denom = other.re_ * other.re_ + other.im_ * other.im_;
    double real = (re_ * other.re_ + im_ * other.im_) / denom;
    double imag = (im_ * other.re_ - re_ * other.im_) / denom;
    return Complex(real, imag);
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
    // e^(a + bi) = e^a * (cos(b) + i sin(b))
    double exp_real = std::exp(re_);
    double real = exp_real * std::cos(im_);
    double imag = exp_real * std::sin(im_);
    return Complex(real, imag);
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
    // lhs / (a + bi) = (lhs * (a - bi)) / (a^2 + b^2)
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    double real = lhs * rhs.real() / denom;
    double imag = -lhs * rhs.imag() / denom;
    return Complex(real, imag);
}

}  // namespace complex_numbers
