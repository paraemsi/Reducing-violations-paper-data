#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept : real_(0.0), imag_(0.0) {}

Complex::Complex(double real, double imag) noexcept : real_(real), imag_(imag) {}

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
    double r2 = (real_ * real_);
    double i2 = (imag_ * imag_);
    return std::sqrt((r2 + i2));
}

Complex Complex::exp() const noexcept {
    double ea = std::exp(real_);
    return Complex((ea * std::cos(imag_)), (ea * std::sin(imag_)));
}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex((real_ + other.real_), (imag_ + other.imag_));
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex((real_ - other.real_), (imag_ - other.imag_));
}

Complex Complex::operator*(const Complex& other) const noexcept {
    double r = ((real_ * other.real_) - (imag_ * other.imag_));
    double i = ((imag_ * other.real_) + (real_ * other.imag_));
    return Complex(r, i);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    double denom = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    double real_num = ((real_ * other.real_) + (imag_ * other.imag_));
    double imag_num = ((imag_ * other.real_) - (real_ * other.imag_));
    return Complex((real_num / denom), (imag_num / denom));
}

Complex operator+(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() + rhs), lhs.imag());
}

Complex operator+(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() - rhs), lhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs - rhs.real()), (0.0 - rhs.imag()));
}

Complex operator*(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    double c = rhs.real();
    double d = rhs.imag();
    double denom = ((c * c) + (d * d));
    double real_num = (lhs * c);
    double imag_num = (0.0 - (lhs * d));
    return Complex((real_num / denom), (imag_num / denom));
}

Complex conjugate(const Complex& z) noexcept {
    return Complex(z.real(), (0.0 - z.imag()));
}

double abs(const Complex& z) noexcept {
    double r2 = (z.real() * z.real());
    double i2 = (z.imag() * z.imag());
    return std::sqrt((r2 + i2));
}

Complex exp(const Complex& z) noexcept {
    double a = z.real();
    double b = z.imag();
    double ea = std::exp(a);
    return Complex((ea * std::cos(b)), (ea * std::sin(b)));
}

}  // namespace complex_numbers
