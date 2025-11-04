#include "complex_numbers.h"
#include <cmath>
#include <limits>

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
    // e^(a + bi) = e^a * (cos(b) + i*sin(b))
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
    // (a + bi) * (c + di) = (a*c - b*d) + (b*c + a*d)i
    double real_part = (real_ * other.real_) - (imag_ * other.imag_);
    double imag_part = (imag_ * other.real_) + (real_ * other.imag_);
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    // Check for division by zero
    double denominator = (other.real_ * other.real_) + (other.imag_ * other.imag_);
    if (denominator == 0.0) {
        // Handle division by zero - perhaps throw an exception or return NaN
        // Since the behavior isn't specified, we'll return NaN
        return Complex(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
    }
    double real_part = ((real_ * other.real_) + (imag_ * other.imag_)) / denominator;
    double imag_part = ((imag_ * other.real_) - (real_ * other.imag_)) / denominator;
    return Complex(real_part, imag_part);
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
    // Implement directly using the formula for (a + 0i)/(c + di) = (a*c)/(c^2 + d^2) + (-a*d)/(c^2 + d^2)i
    double denominator = (rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_);
    if (denominator == 0.0) {
        return Complex(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
    }
    double real_part = (lhs * rhs.real_) / denominator;
    double imag_part = (-lhs * rhs.imag_) / denominator;
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
