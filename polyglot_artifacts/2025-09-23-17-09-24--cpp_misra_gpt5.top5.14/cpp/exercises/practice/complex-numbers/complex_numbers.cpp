#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() : real_(0.0), imag_(0.0) {}

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
    return Complex(((real_ * other.real_) - (imag_ * other.imag_)),
                   ((imag_ * other.real_) + (real_ * other.imag_)));
}

Complex Complex::operator/(const Complex& other) const {
    const double denom = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    const double real_part = (((real_ * other.real_) + (imag_ * other.imag_)) / denom);
    const double imag_part = (((imag_ * other.real_) - (real_ * other.imag_)) / denom);
    return Complex(real_part, imag_part);
}

Complex Complex::conjugate() const {
    return Complex(real_, (-imag_));
}

double Complex::abs() const {
    return std::sqrt(((real_ * real_) + (imag_ * imag_)));
}

Complex Complex::exp() const {
    const double e_real = std::exp(real_);
    const double real_part = (e_real * std::cos(imag_));
    const double imag_part = (e_real * std::sin(imag_));
    return Complex(real_part, imag_part);
}

Complex Complex::conj() const {
    return Complex(real_, (-imag_));
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(((lhs + rhs.real())), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(((lhs - rhs.real())), (-rhs.imag()));
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(((lhs * rhs.real())), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) {
    const double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    const double real_part = ((lhs * rhs.real()) / denom);
    const double imag_part = ((-(lhs * rhs.imag())) / denom);
    return Complex(real_part, imag_part);
}

Complex operator+(const Complex& lhs, double rhs) {
    return Complex((lhs.real() + rhs), lhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) {
    return Complex((lhs.real() - rhs), lhs.imag());
}

Complex operator*(const Complex& lhs, double rhs) {
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator/(const Complex& lhs, double rhs) {
    const double inv = (1.0 / rhs);
    return Complex((lhs.real() * inv), (lhs.imag() * inv));
}

// Free-function helpers
double real(const Complex& z) {
    return z.real();
}

double imag(const Complex& z) {
    return z.imag();
}

Complex conj(const Complex& z) {
    return z.conj();
}

double abs(const Complex& z) {
    return z.abs();
}

Complex exp(const Complex& z) {
    return z.exp();
}

}  // namespace complex_numbers
