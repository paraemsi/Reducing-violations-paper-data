#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

double Complex::abs() const {
    return std::sqrt(((real_ * real_) + (imag_ * imag_)));
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

Complex Complex::exp() const {
    double magnitude = std::exp(real_);
    return Complex(
        magnitude * std::cos(imag_),
        magnitude * std::sin(imag_)
    );
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(
        ((real_ * other.real_) - (imag_ * other.imag_)),
        ((imag_ * other.real_) + (real_ * other.imag_))
    );
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    return Complex(
        (((real_ * other.real_) + (imag_ * other.imag_)) / denominator),
        (((imag_ * other.real_) - (real_ * other.imag_)) / denominator)
    );
}

// Scalar operations
Complex Complex::operator+(double scalar) const {
    return Complex(real_ + scalar, imag_);
}

Complex Complex::operator-(double scalar) const {
    return Complex(real_ - scalar, imag_);
}

Complex Complex::operator*(double scalar) const {
    return Complex(real_ * scalar, imag_ * scalar);
}

Complex Complex::operator/(double scalar) const {
    return Complex(real_ / scalar, imag_ / scalar);
}

// Global operators for scalar on the left side
Complex operator+(double scalar, const Complex& c) {
    return c + scalar;
}

Complex operator-(double scalar, const Complex& c) {
    return Complex(scalar - c.real(), -c.imag());
}

Complex operator*(double scalar, const Complex& c) {
    return c * scalar;
}

Complex operator/(double scalar, const Complex& c) {
    // scalar / (a + bi) = scalar * (a - bi) / (a^2 + b^2)
    double denominator = ((c.real() * c.real()) + (c.imag() * c.imag()));
    return Complex(
        ((scalar * c.real()) / denominator),
        ((-scalar * c.imag()) / denominator)
    );
}

}  // namespace complex_numbers
