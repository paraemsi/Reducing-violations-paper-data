#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept : real_(0.0), imag_(0.0) {}

Complex::Complex(double real, double imag) noexcept : real_(real), imag_(imag) {}

Complex::Complex(double real) noexcept : real_(real), imag_(0.0) {}

double Complex::real() const noexcept
{
    return real_;
}

double Complex::imag() const noexcept
{
    return imag_;
}

Complex Complex::operator+(const Complex& other) const noexcept
{
    return Complex((real_ + other.real_), (imag_ + other.imag_));
}

Complex Complex::operator-(const Complex& other) const noexcept
{
    return Complex((real_ - other.real_), (imag_ - other.imag_));
}

Complex Complex::operator*(const Complex& other) const noexcept
{
    const double r = ((real_ * other.real_) - (imag_ * other.imag_));
    const double i = ((imag_ * other.real_) + (real_ * other.imag_));
    return Complex(r, i);
}

Complex Complex::operator/(const Complex& other) const noexcept
{
    const double denom = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    const double r = (((real_ * other.real_) + (imag_ * other.imag_)) / denom);
    const double i = (((imag_ * other.real_) - (real_ * other.imag_)) / denom);
    return Complex(r, i);
}

Complex Complex::operator+(double rhs) const noexcept
{
    return Complex((real_ + rhs), imag_);
}

Complex Complex::operator-(double rhs) const noexcept
{
    return Complex((real_ - rhs), imag_);
}

Complex Complex::operator*(double rhs) const noexcept
{
    const double r = (real_ * rhs);
    const double i = (imag_ * rhs);
    return Complex(r, i);
}

Complex Complex::operator/(double rhs) const noexcept
{
    const double r = (real_ / rhs);
    const double i = (imag_ / rhs);
    return Complex(r, i);
}

Complex Complex::conj() const noexcept
{
    return Complex(real_, (0.0 - imag_));
}

double Complex::abs() const noexcept
{
    return std::sqrt(((real_ * real_) + (imag_ * imag_)));
}

Complex Complex::exp() const noexcept
{
    const double e = std::exp(real_);
    return Complex((e * std::cos(imag_)), (e * std::sin(imag_)));
}

/* Non-member operators to support real-Complex mixed operations */
Complex operator+(double lhs, const Complex& rhs) noexcept
{
    const double r = (lhs + rhs.real());
    const double i = rhs.imag();
    return Complex(r, i);
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    const double r = (lhs - rhs.real());
    const double i = (0.0 - rhs.imag());
    return Complex(r, i);
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    const double r = (lhs * rhs.real());
    const double i = (lhs * rhs.imag());
    return Complex(r, i);
}

Complex operator/(double lhs, const Complex& rhs) noexcept
{
    const double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    const double r = ((lhs * rhs.real()) / denom);
    const double i = ((0.0 - (lhs * rhs.imag())) / denom);
    return Complex(r, i);
}

}  // namespace complex_numbers
