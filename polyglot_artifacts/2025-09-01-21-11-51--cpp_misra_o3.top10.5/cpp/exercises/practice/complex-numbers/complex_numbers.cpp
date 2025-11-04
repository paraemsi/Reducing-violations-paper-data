#include "complex_numbers.h"

namespace complex_numbers {

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real() + rhs.real()), (lhs.imag() + rhs.imag()));
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real() - rhs.real()), (lhs.imag() - rhs.imag()));
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex(
        ((lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag())),
        ((lhs.imag() * rhs.real()) + (lhs.real() * rhs.imag())));
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    const double denominator = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));

    /* Division by zero yields INF/NaN as per IEEE-754; no additional check required. */
    return Complex(
        (((lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag())) / denominator),
        (((lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag())) / denominator));
}

double abs(const Complex& z) noexcept
{
    return std::sqrt(((z.real() * z.real()) + (z.imag() * z.imag())));
}

Complex exp(const Complex& z)
{
    const double expReal = std::exp(z.real());
    return Complex(
        (expReal * std::cos(z.imag())),
        (expReal * std::sin(z.imag())));
}

Complex conjugate(const Complex& z) noexcept
{
    return z.conjugate();
}

Complex conj(const Complex& z) noexcept
{
    return z.conjugate();
}

/* ----------------------------------------------------------------------- */
/* Member wrappers                                                         */
/* ----------------------------------------------------------------------- */
double Complex::abs() const noexcept
{
    return complex_numbers::abs(*this);
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

}  // namespace complex_numbers
