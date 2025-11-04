#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept : real_(0.0), imag_(0.0) {}

Complex::Complex(double real, double imag) noexcept : real_(real), imag_(imag) {}

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
    return Complex(((real_ * other.real_) - (imag_ * other.imag_)),
                   ((imag_ * other.real_) + (real_ * other.imag_)));
}

Complex Complex::operator/(const Complex& other) const noexcept
{
    const double denom = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    return Complex((((real_ * other.real_) + (imag_ * other.imag_)) / denom),
                   (((imag_ * other.real_) - (real_ * other.imag_)) / denom));
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
    const double e_to_a = std::exp(real_);
    return Complex((e_to_a * std::cos(imag_)), (e_to_a * std::sin(imag_)));
}

Complex conjugate(const Complex& z) noexcept
{
    return Complex(z.real(), (0.0 - z.imag()));
}

double abs(const Complex& z) noexcept
{
    return std::sqrt(((z.real() * z.real()) + (z.imag() * z.imag())));
}

Complex exp(const Complex& z) noexcept
{
    const double e_to_a = std::exp(z.real());
    return Complex((e_to_a * std::cos(z.imag())), (e_to_a * std::sin(z.imag())));
}

Complex operator+(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() + rhs), lhs.imag());
}

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() - rhs), lhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs - rhs.real()), (0.0 - rhs.imag()));
}

Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

Complex operator/(double lhs, const Complex& rhs) noexcept
{
    const double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    return Complex(((lhs * rhs.real()) / denom), (((0.0 - lhs) * rhs.imag()) / denom));
}

}  // namespace complex_numbers
