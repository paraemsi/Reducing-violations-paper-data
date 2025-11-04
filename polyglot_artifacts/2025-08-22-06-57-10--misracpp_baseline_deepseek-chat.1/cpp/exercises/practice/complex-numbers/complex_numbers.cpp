#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

Complex Complex::exp() const {
    double magnitude = std::exp(real_);
    return Complex(magnitude * std::cos(imag_), magnitude * std::sin(imag_));
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

// Implement friend operators
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
    // To compute lhs / (a + bi), which is the same as lhs * (a - bi)/(a² + b²)
    double denominator = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
    return Complex((lhs * rhs.real_) / denominator, 
                   (-lhs * rhs.imag_) / denominator);
}

}  // namespace complex_numbers
