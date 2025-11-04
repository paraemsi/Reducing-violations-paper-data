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
    return Complex(real() + other.real(), imag() + other.imag());
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real() - other.real(), imag() - other.imag());
}

Complex Complex::operator*(const Complex& other) const {
    double real_part = (real() * other.real()) - (imag() * other.imag());
    double imag_part = (imag() * other.real()) + (real() * other.imag());
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = (other.real() * other.real()) + (other.imag() * other.imag());
    double real_part = ((real() * other.real()) + (imag() * other.imag())) / denominator;
    double imag_part = ((imag() * other.real()) - (real() * other.imag())) / denominator;
    return Complex(real_part, imag_part);
}

double Complex::abs() const {
    return std::sqrt((real() * real()) + (imag() * imag()));
}

Complex Complex::conj() const {
    return Complex(real(), -imag());
}

Complex Complex::exp() const {
    // e^(a + bi) = e^a * (cos(b) + i*sin(b))
    double magnitude = std::exp(real());
    return Complex(magnitude * std::cos(imag()), magnitude * std::sin(imag()));
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
