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
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

Complex Complex::exp() const {
    // Using Euler's formula: e^(a + bi) = e^a * (cos(b) + i*sin(b))
    double exp_real = std::exp(real_);
    return Complex(exp_real * std::cos(imag_), exp_real * std::sin(imag_));
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real_ * other.real_ - imag_ * other.imag_,
                  imag_ * other.real_ + real_ * other.imag_);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    return Complex((real_ * other.real_ + imag_ * other.imag_) / denominator,
                  (imag_ * other.real_ - real_ * other.imag_) / denominator);
}

// Implementation of friend functions for mixed-type operations
Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ + rhs, lhs.imag_);
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real_, rhs.imag_);
}

Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ - rhs, lhs.imag_);
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real_, -rhs.imag_);
}

Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ * rhs, lhs.imag_ * rhs);
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real_, lhs * rhs.imag_);
}

Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ / rhs, lhs.imag_ / rhs);
}

Complex operator/(double lhs, const Complex& rhs) {
    double denominator = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
    return Complex((lhs * rhs.real_) / denominator, 
                  (-lhs * rhs.imag_) / denominator);
}

}  // namespace complex_numbers
