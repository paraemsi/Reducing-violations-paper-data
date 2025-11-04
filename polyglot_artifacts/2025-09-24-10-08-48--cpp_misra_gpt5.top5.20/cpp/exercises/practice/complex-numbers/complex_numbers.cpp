#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept
    : real_(0.0), imag_(0.0) {}

Complex::Complex(double real, double imag) noexcept
    : real_(real), imag_(imag) {}

double Complex::real() const noexcept {
    return real_;
}

double Complex::imag() const noexcept {
    return imag_;
}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex((real_ + other.real_), (imag_ + other.imag_));
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex((real_ - other.real_), (imag_ - other.imag_));
}

Complex Complex::operator*(const Complex& other) const noexcept {
    const double r = ((real_ * other.real_) - (imag_ * other.imag_));
    const double i = ((imag_ * other.real_) + (real_ * other.imag_));
    return Complex(r, i);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    const double den = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    const double r = (((real_ * other.real_) + (imag_ * other.imag_)) / den);
    const double i = (((imag_ * other.real_) - (real_ * other.imag_)) / den);
    return Complex(r, i);
}

Complex Complex::operator+(double value) const noexcept {
    return Complex((real_ + value), imag_);
}

Complex Complex::operator-(double value) const noexcept {
    return Complex((real_ - value), imag_);
}

Complex Complex::operator*(double value) const noexcept {
    return Complex((real_ * value), (imag_ * value));
}

Complex Complex::operator/(double value) const noexcept {
    return Complex((real_ / value), (imag_ / value));
}

Complex Complex::conj() const noexcept {
    return Complex(real_, (0.0 - imag_));
}

double Complex::abs() const noexcept {
    return std::sqrt(((real_ * real_) + (imag_ * imag_)));
}

Complex Complex::exp() const noexcept {
    const double exponent = std::exp(real_);
    const double cos_b = std::cos(imag_);
    const double sin_b = std::sin(imag_);
    return Complex((exponent * cos_b), (exponent * sin_b));
}

Complex operator+(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs - rhs.real()), (0.0 - rhs.imag()));
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    const double den = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    const double r = ((lhs * rhs.real()) / den);
    const double i = ((0.0 - (lhs * rhs.imag())) / den);
    return Complex(r, i);
}

Complex conj(const Complex& value) noexcept {
    return value.conj();
}

double abs(const Complex& value) noexcept {
    return value.abs();
}

Complex exp(const Complex& value) noexcept {
    return value.exp();
}

}  // namespace complex_numbers
