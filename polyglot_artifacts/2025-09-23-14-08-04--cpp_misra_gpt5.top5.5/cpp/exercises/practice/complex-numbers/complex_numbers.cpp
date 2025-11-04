#include "complex_numbers.h"

#include <cmath>  // std::sqrt, std::exp, std::cos, std::sin

#if defined(abs)
#undef abs
#endif
#if defined(conj)
#undef conj
#endif
#if defined(exp)
#undef exp
#endif

namespace complex_numbers {

Complex::Complex(double real, double imag) noexcept
    : real_(real), imag_(imag) { }

double Complex::real() const noexcept {
    return real_;
}

double Complex::imag() const noexcept {
    return imag_;
}

Complex Complex::conj() const noexcept {
    return Complex(real_, (0.0 - imag_));
}

double Complex::abs() const noexcept {
    return std::sqrt((real_ * real_) + (imag_ * imag_));
}

Complex Complex::exp() const noexcept {
    const double e_to_a = std::exp(real_);
    const double cos_b = std::cos(imag_);
    const double sin_b = std::sin(imag_);
    return Complex((e_to_a * cos_b), (e_to_a * sin_b));
}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex((real_ + other.real_), (imag_ + other.imag_));
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex((real_ - other.real_), (imag_ - other.imag_));
}

Complex Complex::operator*(const Complex& other) const noexcept {
    const double real_part = ((real_ * other.real_) - (imag_ * other.imag_));
    const double imag_part = ((imag_ * other.real_) + (real_ * other.imag_));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    const double denom = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    const double real_part = (((real_ * other.real_) + (imag_ * other.imag_)) / denom);
    const double imag_part = (((imag_ * other.real_) - (real_ * other.imag_)) / denom);
    return Complex(real_part, imag_part);
}

// Free function helpers
Complex conj(const Complex& z) noexcept {
    return z.conj();
}

double abs(const Complex& z) noexcept {
    return z.abs();
}

Complex exp(const Complex& z) noexcept {
    return z.exp();
}

// Mixed-type operations with doubles
Complex operator+(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() + rhs), lhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() - rhs), lhs.imag());
}

Complex operator*(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator/(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
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
    const double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    const double real_part = ((lhs * rhs.real()) / denom);
    const double imag_part = (((0.0 - lhs) * rhs.imag()) / denom);
    return Complex(real_part, imag_part);
}


}  // namespace complex_numbers
