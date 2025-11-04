#include "complex_numbers.h"

#include <cmath>  // std::sqrt, std::exp, std::cos, std::sin

namespace complex_numbers {

Complex::Complex() noexcept
    : r_{0.0}, i_{0.0} {
}

Complex::Complex(double real, double imag) noexcept
    : r_{real}, i_{imag} {
}

double Complex::real() const noexcept {
    return r_;
}

double Complex::imag() const noexcept {
    return i_;
}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex((r_ + other.r_), (i_ + other.i_));
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex((r_ - other.r_), (i_ - other.i_));
}

Complex Complex::operator*(const Complex& other) const noexcept {
    return Complex(((r_ * other.r_) - (i_ * other.i_)),
                   ((i_ * other.r_) + (r_ * other.i_)));
}

Complex Complex::operator/(const Complex& other) const noexcept {
    const double denom = ((other.r_ * other.r_) + (other.i_ * other.i_));
    return Complex((((r_ * other.r_) + (i_ * other.i_)) / denom),
                   (((i_ * other.r_) - (r_ * other.i_)) / denom));
}

Complex Complex::operator+(double scalar) const noexcept {
    return Complex((r_ + scalar), i_);
}

Complex Complex::operator-(double scalar) const noexcept {
    return Complex((r_ - scalar), i_);
}

Complex Complex::operator*(double scalar) const noexcept {
    return Complex((r_ * scalar), (i_ * scalar));
}

Complex Complex::operator/(double scalar) const noexcept {
    return Complex((r_ / scalar), (i_ / scalar));
}

Complex Complex::conj() const noexcept {
    return Complex(r_, (0.0 - i_));
}

double Complex::abs() const noexcept {
    return std::sqrt(((r_ * r_) + (i_ * i_)));
}

Complex Complex::exp() const noexcept {
    const double ea = std::exp(r_);
    return Complex((ea * std::cos(i_)), (ea * std::sin(i_)));
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
    return Complex(((lhs * rhs.real()) / denom), ((0.0 - (lhs * rhs.imag())) / denom));
}

Complex conj(const Complex& z) noexcept {
    return z.conj();
}

double abs(const Complex& z) noexcept {
    return z.abs();
}

Complex exp(const Complex& z) noexcept {
    return z.exp();
}

double real(const Complex& z) noexcept {
    return z.real();
}

double imag(const Complex& z) noexcept {
    return z.imag();
}

}  // namespace complex_numbers
