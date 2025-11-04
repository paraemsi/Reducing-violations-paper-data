#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

namespace complex_numbers {

constexpr Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real() + rhs.real()),
                   (lhs.imag() + rhs.imag()));
}

constexpr Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real() - rhs.real()),
                   (lhs.imag() - rhs.imag()));
}

constexpr Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    const double realPart = ((lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag()));
    const double imagPart = ((lhs.imag() * rhs.real()) + (lhs.real() * rhs.imag()));
    return Complex(realPart, imagPart);
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    const double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));

    if (denom == 0.0)
    {
        throw std::invalid_argument("Division by zero complex number");
    }

    const double realPart = (((lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag())) / denom);
    const double imagPart = (((lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag())) / denom);

    return Complex(realPart, imagPart);
}

double abs(const Complex& z) noexcept
{
    return std::sqrt((z.real() * z.real()) + (z.imag() * z.imag()));
}

Complex exp(const Complex& z)
{
    const double expReal = std::exp(z.real());
    const double realPart = (expReal * std::cos(z.imag()));
    const double imagPart = (expReal * std::sin(z.imag()));

    return Complex(realPart, imagPart);
}

/* Member function definitions that delegate to existing utilities */
double Complex::abs() const noexcept
{
    return complex_numbers::abs(*this);
}

Complex Complex::conj() const noexcept
{
    return Complex(m_real, -m_imag);
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

}  // namespace complex_numbers
