#include "complex_numbers.h"

#include <cmath>
#include <limits>

namespace complex_numbers {

Complex::Complex(double real, double imag) noexcept : real_{real}, imag_{imag} {}

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
    const double a = real_;
    const double b = imag_;
    const double c = other.real_;
    const double d = other.imag_;

    const double real_part = ((a * c) - (b * d));
    const double imag_part = ((b * c) + (a * d));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const noexcept
{
    const double c = other.real_;
    const double d = other.imag_;
    const double denom = ((c * c) + (d * d));

    if ((denom == 0.0)) {
        const double nanv = std::numeric_limits<double>::quiet_NaN();
        return Complex(nanv, nanv);
    }

    const double real_part = (((real_ * c) + (imag_ * d)) / denom);
    const double imag_part = (((imag_ * c) - (real_ * d)) / denom);
    return Complex(real_part, imag_part);
}

// Operations with real scalars (member overloads)
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
    return Complex((real_ * rhs), (imag_ * rhs));
}

Complex Complex::operator/(double rhs) const noexcept
{
    if ((rhs == 0.0)) {
        const double nanv = std::numeric_limits<double>::quiet_NaN();
        return Complex(nanv, nanv);
    }
    const double inv = (1.0 / rhs);
    return Complex((real_ * inv), (imag_ * inv));
}

Complex Complex::conj() const noexcept
{
    return Complex(real_, -imag_);
}

double Complex::abs() const noexcept
{
    return std::sqrt(((real_ * real_) + (imag_ * imag_)));
}

Complex Complex::exp() const noexcept
{
    const double e_a = std::exp(real_);
    const double real_part = (e_a * std::cos(imag_));
    const double imag_part = (e_a * std::sin(imag_));
    return Complex(real_part, imag_part);
}

// Non-member overloads for operations with real scalars
Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs - rhs.real()), (-rhs.imag()));
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) noexcept
{
    const double c = rhs.real();
    const double d = rhs.imag();
    const double denom = ((c * c) + (d * d));
    if ((denom == 0.0)) {
        const double nanv = std::numeric_limits<double>::quiet_NaN();
        return Complex(nanv, nanv);
    }
    const double real_part = ((lhs * c) / denom);
    const double imag_part = ((-lhs * d) / denom);
    return Complex(real_part, imag_part);
}

Complex conj(const Complex& z) noexcept
{
    return z.conj();
}

double abs(const Complex& z) noexcept
{
    return z.abs();
}

Complex exp(const Complex& z) noexcept
{
    return z.exp();
}

}  // namespace complex_numbers
