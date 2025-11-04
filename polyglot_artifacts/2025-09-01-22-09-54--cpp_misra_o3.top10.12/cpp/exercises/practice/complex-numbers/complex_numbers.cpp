#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {



double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.m_real + rhs.m_real), (lhs.m_imag + rhs.m_imag));
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.m_real - rhs.m_real), (lhs.m_imag - rhs.m_imag));
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    double realPart = ((lhs.m_real * rhs.m_real) - (lhs.m_imag * rhs.m_imag));
    double imagPart = ((lhs.m_imag * rhs.m_real) + (lhs.m_real * rhs.m_imag));
    return Complex(realPart, imagPart);
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    double denominator = ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag));
    double realPart = (((lhs.m_real * rhs.m_real) + (lhs.m_imag * rhs.m_imag)) / denominator);
    double imagPart = (((lhs.m_imag * rhs.m_real) - (lhs.m_real * rhs.m_imag)) / denominator);
    return Complex(realPart, imagPart);
}

Complex exp(const Complex& z)
{
    double magnitude = std::exp(z.real());
    double cosImag   = std::cos(z.imag());
    double sinImag   = std::sin(z.imag());
    return Complex((magnitude * cosImag), (magnitude * sinImag));
}

/* Member wrapper for exponent */
Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

/* Operators with scalar rhs (double) */

Complex operator+(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.m_real + rhs), lhs.m_imag);
}

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs + rhs.m_real), rhs.m_imag);
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.m_real - rhs), lhs.m_imag);
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs - rhs.m_real), (0.0 - rhs.m_imag));
}

Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.m_real * rhs), (lhs.m_imag * rhs));
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.m_real), (lhs * rhs.m_imag));
}

Complex operator/(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.m_real / rhs), (lhs.m_imag / rhs));
}

Complex operator/(double lhs, const Complex& rhs)
{
    return Complex(lhs, 0.0) / rhs;
}

}  // namespace complex_numbers
