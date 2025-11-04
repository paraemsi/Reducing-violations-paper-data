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
    return {real_ + other.real_, imag_ + other.imag_};
}

Complex Complex::operator-(const Complex& other) const {
    return {real_ - other.real_, imag_ - other.imag_};
}

Complex Complex::operator*(const Complex& other) const {
    return {real_ * other.real_ - imag_ * other.imag_,
            imag_ * other.real_ + real_ * other.imag_};
}

Complex Complex::operator/(const Complex& other) const {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    return {(real_ * other.real_ + imag_ * other.imag_) / denom,
            (imag_ * other.real_ - real_ * other.imag_) / denom};
}

Complex Complex::conj() const {
    return {real_, -imag_};
}

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::exp() const {
    double factor = std::exp(real_);
    return {factor * std::cos(imag_), factor * std::sin(imag_)};
}

// Non-member arithmetic operators with a double lhs
Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs) + rhs;
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs) - rhs;
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs) * rhs;
}

Complex operator/(double lhs, const Complex& rhs) {
    return Complex(lhs) / rhs;
}

}  // namespace complex_numbers
