#include "complex_numbers.h"

namespace complex_numbers {

Complex::Complex(double real, double imag) : real_{real}, imag_{imag} {}

double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }

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
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    return Complex((real_ * other.real_ + imag_ * other.imag_) / denom,
                   (imag_ * other.real_ - real_ * other.imag_) / denom);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::exp() const {
    // e^(a + i b) = e^a (cos b + i sin b)
    double factor = std::exp(real_);
    return Complex(factor * std::cos(imag_), factor * std::sin(imag_));
}

// Operations with real numbers
Complex Complex::operator+(double value) const {
    return Complex(real_ + value, imag_);
}

Complex Complex::operator-(double value) const {
    return Complex(real_ - value, imag_);
}

Complex Complex::operator*(double value) const {
    return Complex(real_ * value, imag_ * value);
}

Complex Complex::operator/(double value) const {
    return Complex(real_ / value, imag_ / value);
}

// Unary operators
Complex Complex::operator+() const {
    return *this;
}

Complex Complex::operator-() const {
    return Complex(-real_, -imag_);
}

// Non-member arithmetic with a real number on the left-hand side
Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator/(double lhs, const Complex& rhs) {
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return Complex((lhs * rhs.real()) / denom, (-lhs * rhs.imag()) / denom);
}

// Non-member absolute value implementation
double abs(const Complex& c) {
    return c.abs();
}

}  // namespace complex_numbers
