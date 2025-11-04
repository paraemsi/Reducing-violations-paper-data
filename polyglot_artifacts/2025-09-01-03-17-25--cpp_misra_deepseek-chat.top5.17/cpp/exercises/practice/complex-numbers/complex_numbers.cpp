#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

double Complex::real() const {
    return real_;
}

double Complex::imag() const {
    return imag_;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex((real_ + other.real_), (imag_ + other.imag_));
}

Complex Complex::operator-(const Complex& other) const {
    return Complex((real_ - other.real_), (imag_ - other.imag_));
}

Complex Complex::operator*(const Complex& other) const {
    double real_part = ((real_ * other.real_) - (imag_ * other.imag_));
    double imag_part = ((imag_ * other.real_) + (real_ * other.imag_));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    double real_part = (((real_ * other.real_) + (imag_ * other.imag_)) / denominator);
    double imag_part = (((imag_ * other.real_) - (real_ * other.imag_)) / denominator);
    return Complex(real_part, imag_part);
}

double Complex::abs() const {
    return std::sqrt(((real_ * real_) + (imag_ * imag_)));
}

Complex Complex::conj() const {
    return Complex(real_, (-imag_));
}

Complex Complex::exp() const {
    // e^(a + bi) = e^a * (cos(b) + i*sin(b))
    double magnitude = std::exp(real_);
    return Complex((magnitude * std::cos(imag_)), (magnitude * std::sin(imag_)));
}

// Non-member operator implementations
Complex operator+(const Complex& lhs, double rhs) {
    return lhs + Complex(rhs, 0.0);
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0) + rhs;
}

Complex operator-(const Complex& lhs, double rhs) {
    return lhs - Complex(rhs, 0.0);
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0) - rhs;
}

Complex operator*(const Complex& lhs, double rhs) {
    return lhs * Complex(rhs, 0.0);
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0) * rhs;
}

Complex operator/(const Complex& lhs, double rhs) {
    return lhs / Complex(rhs, 0.0);
}

Complex operator/(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0) / rhs;
}

}  // namespace complex_numbers
