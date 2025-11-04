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
    // (a + bi)*(c + di) = (ac - bd) + (ad + bc)i
    double real_part = real_ * other.real_ - imag_ * other.imag_;
    double imag_part = real_ * other.imag_ + imag_ * other.real_;
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + bi)/(c + di) = [(ac + bd)/(c^2 + d^2)] + [(bc - ad)/(c^2 + d^2)]i
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    double real_part = (real_ * other.real_ + imag_ * other.imag_) / denominator;
    double imag_part = (imag_ * other.real_ - real_ * other.imag_) / denominator;
    return Complex(real_part, imag_part);
}

// Non-member operator implementations
Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real() + rhs, lhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real() - rhs, lhs.imag());
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real() * rhs, lhs.imag() * rhs);
}

Complex operator/(double lhs, const Complex& rhs) {
    // Treat lhs as a complex number (lhs + 0i)
    // (lhs + 0i)/(c + di) = (lhs*c + 0*d)/(c^2 + d^2) + (0*c - lhs*d)/(c^2 + d^2)i
    double denominator = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    double real_part = (lhs * rhs.real()) / denominator;
    double imag_part = (-lhs * rhs.imag()) / denominator;
    return Complex(real_part, imag_part);
}

Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real() / rhs, lhs.imag() / rhs);
}

}  // namespace complex_numbers
