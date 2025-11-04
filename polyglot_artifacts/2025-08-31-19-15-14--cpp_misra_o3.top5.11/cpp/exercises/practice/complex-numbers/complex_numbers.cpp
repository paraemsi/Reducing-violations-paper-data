#include "complex_numbers.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace complex_numbers {

/* Addition */
Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex(
        (lhs.real() + rhs.real()),
        (lhs.imag() + rhs.imag()));
}

/* Subtraction */
Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex(
        (lhs.real() - rhs.real()),
        (lhs.imag() - rhs.imag()));
}

/* Multiplication */
Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    const double real_val =
        ((lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag()));
    const double imag_val =
        ((lhs.imag() * rhs.real()) + (lhs.real() * rhs.imag()));
    return Complex(real_val, imag_val);
}

/* Division */
Complex operator/(const Complex& lhs, const Complex& rhs)
{
    const double denominator =
        ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));

    if (denominator == 0.0)
    {
        throw std::invalid_argument("Division by zero in complex division");
    }

    const double real_val =
        (((lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag())) / denominator);
    const double imag_val =
        (((lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag())) / denominator);
    return Complex(real_val, imag_val);
}

/* Conjugate */
Complex conjugate(const Complex& value) noexcept
{
    return Complex(value.real(), (-(value.imag())));
}

/* Absolute value (magnitude) */
double abs(const Complex& value) noexcept
{
    return std::sqrt(
        ((value.real() * value.real()) + (value.imag() * value.imag())));
}

/* Exponential e^(a + i b) */
Complex exp(const Complex& value)
{
    const double exp_real = std::exp(value.real());
    const double cos_b    = std::cos(value.imag());
    const double sin_b    = std::sin(value.imag());

    return Complex(
        (exp_real * cos_b),
        (exp_real * sin_b));
}

/* Member function wrappers */
Complex Complex::conj() const noexcept
{
    return conjugate(*this);
}

double Complex::abs() const noexcept
{
    return complex_numbers::abs(*this);
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

}  // namespace complex_numbers
