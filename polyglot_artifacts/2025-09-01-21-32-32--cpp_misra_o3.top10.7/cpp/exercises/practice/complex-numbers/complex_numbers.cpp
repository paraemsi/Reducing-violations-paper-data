#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

/* ----------- member operations ----------- */

double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::exp() const noexcept
{
    const double exp_real = std::exp(m_real);
    return Complex((exp_real * std::cos(m_imag)), (exp_real * std::sin(m_imag)));
}

/* ----------- arithmetic operators ----------- */
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
    return Complex(((lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag())),
                   ((lhs.imag() * rhs.real()) + (lhs.real() * rhs.imag())));
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    const double denominator = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    return Complex((((lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag())) / denominator),
                   (((lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag())) / denominator));
}

/* ----------- additional operations ----------- */
Complex conj(const Complex& value) noexcept
{
    return value.conj();
}

double abs(const Complex& value) noexcept
{
    return value.abs();
}

Complex exp(const Complex& value) noexcept
{
    return value.exp();
}

}  // namespace complex_numbers
