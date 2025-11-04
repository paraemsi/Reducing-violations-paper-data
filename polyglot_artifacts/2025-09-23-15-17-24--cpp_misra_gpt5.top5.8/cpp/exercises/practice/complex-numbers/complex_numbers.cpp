#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() : re_(0.0), im_(0.0) {}
Complex::Complex(double real) : re_(real), im_(0.0) {}
Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

double Complex::real() const {
    return re_;
}

double Complex::imag() const {
    return im_;
}

Complex Complex::conj() const {
    return Complex(re_, (0.0 - im_));
}

double Complex::abs() const {
    return std::sqrt(((re_ * re_) + (im_ * im_)));
}

Complex Complex::exp() const {
    const double ea = std::exp(re_);
    return Complex((ea * std::cos(im_)), (ea * std::sin(im_)));
}

Complex Complex::operator+(const Complex& rhs) const {
    return Complex((re_ + rhs.real()), (im_ + rhs.imag()));
}

Complex Complex::operator-(const Complex& rhs) const {
    return Complex((re_ - rhs.real()), (im_ - rhs.imag()));
}

Complex Complex::operator*(const Complex& rhs) const {
    const double a = re_;
    const double b = im_;
    const double c = rhs.real();
    const double d = rhs.imag();
    return Complex(((a * c) - (b * d)), ((b * c) + (a * d)));
}

Complex Complex::operator/(const Complex& rhs) const {
    const double a = re_;
    const double b = im_;
    const double c = rhs.real();
    const double d = rhs.imag();
    const double denom = ((c * c) + (d * d));
    return Complex((((a * c) + (b * d)) / denom), (((b * c) - (a * d)) / denom));
}

Complex Complex::operator+(double rhs) const {
    return Complex((re_ + rhs), im_);
}

Complex Complex::operator-(double rhs) const {
    return Complex((re_ - rhs), im_);
}

Complex Complex::operator*(double rhs) const {
    return Complex((re_ * rhs), (im_ * rhs));
}

Complex Complex::operator/(double rhs) const {
    return Complex((re_ / rhs), (im_ / rhs));
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex((lhs - rhs.real()), (0.0 - rhs.imag()));
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) {
    // lhs / (c + d i) = lhs * (c - d i) / (c^2 + d^2)
    const double c = rhs.real();
    const double d = rhs.imag();
    const double denom = ((c * c) + (d * d));
    return Complex(((lhs * c) / denom), ((0.0 - (lhs * d)) / denom));
}

Complex conj(const Complex& value) {
    return Complex(value.real(), (0.0 - value.imag()));
}

double abs(const Complex& value) {
    const double a = value.real();
    const double b = value.imag();
    return std::sqrt(((a * a) + (b * b)));
}

Complex exp(const Complex& value) {
    const double a = value.real();
    const double b = value.imag();
    const double ea = std::exp(a);
    return Complex((ea * std::cos(b)), (ea * std::sin(b)));
}

}  // namespace complex_numbers
