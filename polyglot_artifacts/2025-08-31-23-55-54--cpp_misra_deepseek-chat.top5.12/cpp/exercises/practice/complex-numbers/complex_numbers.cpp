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

double Complex::abs() const {
    return std::sqrt((real_ * real_) + (imag_ * imag_));
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

Complex Complex::exp() const {
    double magnitude = std::exp(real_);
    return Complex(magnitude * std::cos(imag_), magnitude * std::sin(imag_));
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.real() + rhs.real(), lhs.imag() + rhs.imag());
}

Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real() + rhs, lhs.imag());
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.real() - rhs.real(), lhs.imag() - rhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real() - rhs, lhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
    double real_part = (lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag());
    double imag_part = (lhs.imag() * rhs.real()) + (lhs.real() * rhs.imag());
    return Complex(real_part, imag_part);
}

Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real() * rhs, lhs.imag() * rhs);
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    double denominator = (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag());
    double real_part = ((lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag())) / denominator;
    double imag_part = ((lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag())) / denominator;
    return Complex(real_part, imag_part);
}

Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real() / rhs, lhs.imag() / rhs);
}

Complex operator/(double lhs, const Complex& rhs) {
    // Treat lhs as a complex number (lhs + 0i) and divide by rhs
    double denominator = (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag());
    double real_part = (lhs * rhs.real()) / denominator;
    double imag_part = (-lhs * rhs.imag()) / denominator;
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
