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

Complex Complex::operator+(const Complex& other) const {
    return Complex((re_ + other.re_), (im_ + other.im_));
}

Complex Complex::operator-(const Complex& other) const {
    return Complex((re_ - other.re_), (im_ - other.im_));
}

Complex Complex::operator*(const Complex& other) const {
    const double r = ((re_ * other.re_) - (im_ * other.im_));
    const double i = ((im_ * other.re_) + (re_ * other.im_));
    return Complex(r, i);
}

Complex Complex::operator/(const Complex& other) const {
    const double denom = ((other.re_ * other.re_) + (other.im_ * other.im_));
    const double r = (((re_ * other.re_) + (im_ * other.im_)) / denom);
    const double i = (((im_ * other.re_) - (re_ * other.im_)) / denom);
    return Complex(r, i);
}

Complex Complex::operator+(double scalar) const {
    return Complex((re_ + scalar), im_);
}

Complex Complex::operator-(double scalar) const {
    return Complex((re_ - scalar), im_);
}

Complex Complex::operator*(double scalar) const {
    const double r = (re_ * scalar);
    const double i = (im_ * scalar);
    return Complex(r, i);
}

Complex Complex::operator/(double scalar) const {
    const double r = (re_ / scalar);
    const double i = (im_ / scalar);
    return Complex(r, i);
}

// scalar-Complex non-member operators
Complex operator+(double scalar, const Complex& z) {
    return Complex((scalar + z.re_), z.im_);
}

Complex operator-(double scalar, const Complex& z) {
    return Complex((scalar - z.re_), (0.0 - z.im_));
}

Complex operator*(double scalar, const Complex& z) {
    const double r = (scalar * z.re_);
    const double i = (scalar * z.im_);
    return Complex(r, i);
}

Complex operator/(double scalar, const Complex& z) {
    const double denom = ((z.re_ * z.re_) + (z.im_ * z.im_));
    const double r = ((scalar * z.re_) / denom);
    const double i = ((0.0 - (scalar * z.im_)) / denom);
    return Complex(r, i);
}

Complex Complex::conj() const {
    return Complex(re_, (0.0 - im_));
}

double Complex::abs() const {
    return std::sqrt(((re_ * re_) + (im_ * im_)));
}

Complex Complex::exp() const {
    // e^(a + i*b) = e^a * (cos(b) + i*sin(b))
    const double e_to_a = std::exp(re_);
    const double cos_b = std::cos(im_);
    const double sin_b = std::sin(im_);
    const double r = (e_to_a * cos_b);
    const double i = (e_to_a * sin_b);
    return Complex(r, i);
}

}  // namespace complex_numbers
