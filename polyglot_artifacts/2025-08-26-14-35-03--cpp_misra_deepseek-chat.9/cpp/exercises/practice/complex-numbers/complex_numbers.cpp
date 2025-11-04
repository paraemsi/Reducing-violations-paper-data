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
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    double real_part = (real_ * other.real_) - (imag_ * other.imag_);
    double imag_part = (imag_ * other.real_) + (real_ * other.imag_);
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = (other.real_ * other.real_) + (other.imag_ * other.imag_);
    // Check for division by zero
    if (denominator == 0.0) {
        // Handle division by zero - according to IEEE 754, this will produce infinity or NaN
        // which is probably what we want
    }
    double real_part = ((real_ * other.real_) + (imag_ * other.imag_)) / denominator;
    double imag_part = ((imag_ * other.real_) - (real_ * other.imag_)) / denominator;
    return Complex(real_part, imag_part);
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

// Implement non-member operators
Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real() + rhs, lhs.imag());
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real() - rhs, lhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real() * rhs, lhs.imag() * rhs);
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real() / rhs, lhs.imag() / rhs);
}

Complex operator/(double lhs, const Complex& rhs) {
    // To divide a double by a complex number, we can treat the double as a complex number with imaginary part 0
    // and use the complex division formula
    Complex lhs_complex(lhs, 0.0);
    return lhs_complex / rhs;
}

}  // namespace complex_numbers
