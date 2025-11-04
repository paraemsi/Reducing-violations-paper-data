#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept
    : real_(0.0), imag_(0.0) {
}

Complex::Complex(double real, double imag) noexcept
    : real_(real), imag_(imag) {
}

double Complex::real() const noexcept {
    return real_;
}

double Complex::imag() const noexcept {
    return imag_;
}

Complex Complex::conjugate() const noexcept {
    return Complex(real_, (-imag_));
}

Complex Complex::conj() const noexcept {
    return Complex(real_, (-imag_));
}

double Complex::abs() const noexcept {
    return std::sqrt(((real_ * real_) + (imag_ * imag_)));
}

Complex Complex::exp() const noexcept {
    const double exp_real = std::exp(real_);
    const double real_part = (exp_real * std::cos(imag_));
    const double imag_part = (exp_real * std::sin(imag_));
    return Complex(real_part, imag_part);
}

Complex Complex::operator+(const Complex& rhs) const noexcept {
    const double real_part = (real_ + rhs.real_);
    const double imag_part = (imag_ + rhs.imag_);
    return Complex(real_part, imag_part);
}

Complex Complex::operator-(const Complex& rhs) const noexcept {
    const double real_part = (real_ - rhs.real_);
    const double imag_part = (imag_ - rhs.imag_);
    return Complex(real_part, imag_part);
}

Complex Complex::operator*(const Complex& rhs) const noexcept {
    const double a = real_;
    const double b = imag_;
    const double c = rhs.real_;
    const double d = rhs.imag_;
    const double real_part = ((a * c) - (b * d));
    const double imag_part = ((b * c) + (a * d));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& rhs) const noexcept {
    const double a = real_;
    const double b = imag_;
    const double c = rhs.real_;
    const double d = rhs.imag_;
    const double denom = ((c * c) + (d * d));
    const double real_part = (((a * c) + (b * d)) / denom);
    const double imag_part = (((b * c) - (a * d)) / denom);
    return Complex(real_part, imag_part);
}

Complex Complex::operator+(double rhs) const noexcept {
    const double real_part = (real_ + rhs);
    const double imag_part = imag_;
    return Complex(real_part, imag_part);
}

Complex Complex::operator-(double rhs) const noexcept {
    const double real_part = (real_ - rhs);
    const double imag_part = imag_;
    return Complex(real_part, imag_part);
}

Complex Complex::operator*(double rhs) const noexcept {
    const double real_part = (real_ * rhs);
    const double imag_part = (imag_ * rhs);
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(double rhs) const noexcept {
    const double real_part = (real_ / rhs);
    const double imag_part = (imag_ / rhs);
    return Complex(real_part, imag_part);
}

bool Complex::operator==(const Complex& rhs) const noexcept {
    return ((real_ == rhs.real_) && (imag_ == rhs.imag_));
}

bool Complex::operator!=(const Complex& rhs) const noexcept {
    return (!((*this) == rhs));
}

// Free-function helpers
Complex add(const Complex& lhs, const Complex& rhs) noexcept {
    return (lhs + rhs);
}

Complex subtract(const Complex& lhs, const Complex& rhs) noexcept {
    return (lhs - rhs);
}

Complex multiply(const Complex& lhs, const Complex& rhs) noexcept {
    return (lhs * rhs);
}

Complex divide(const Complex& lhs, const Complex& rhs) noexcept {
    return (lhs / rhs);
}

Complex operator+(double lhs, const Complex& rhs) noexcept {
    const double real_part = (lhs + rhs.real());
    const double imag_part = rhs.imag();
    return Complex(real_part, imag_part);
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    const double real_part = (lhs - rhs.real());
    const double imag_part = (0.0 - rhs.imag());
    return Complex(real_part, imag_part);
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    const double real_part = (lhs * rhs.real());
    const double imag_part = (lhs * rhs.imag());
    return Complex(real_part, imag_part);
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    const double a = rhs.real();
    const double b = rhs.imag();
    const double denom = ((a * a) + (b * b));
    const double real_part = ((lhs * a) / denom);
    const double imag_part = ((-lhs * b) / denom);
    return Complex(real_part, imag_part);
}

double abs(const Complex& z) noexcept {
    return z.abs();
}

Complex conjugate(const Complex& z) noexcept {
    return z.conjugate();
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
