#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) noexcept
    : m_real{real}, m_imag{imag}
{
}

double Complex::real() const noexcept
{
    return (m_real);
}

double Complex::imag() const noexcept
{
    return (m_imag);
}

Complex Complex::conj() const noexcept
{
    return Complex(m_real, (-m_imag));
}

double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::exp() const noexcept
{
    const double exp_real = std::exp(m_real);
    const double real_part = (exp_real * std::cos(m_imag));
    const double imag_part = (exp_real * std::sin(m_imag));
    return Complex(real_part, imag_part);
}

Complex Complex::operator+(const Complex& other) const noexcept
{
    return Complex((m_real + other.m_real), (m_imag + other.m_imag));
}

Complex Complex::operator-(const Complex& other) const noexcept
{
    return Complex((m_real - other.m_real), (m_imag - other.m_imag));
}

Complex Complex::operator*(const Complex& other) const noexcept
{
    const double real_part = ((m_real * other.m_real) - (m_imag * other.m_imag));
    const double imag_part = ((m_imag * other.m_real) + (m_real * other.m_imag));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const noexcept
{
    const double denom = ((other.m_real * other.m_real) + (other.m_imag * other.m_imag));
    const double real_part = (((m_real * other.m_real) + (m_imag * other.m_imag)) / denom);
    const double imag_part = (((m_imag * other.m_real) - (m_real * other.m_imag)) / denom);
    return Complex(real_part, imag_part);
}

Complex Complex::operator+(double rhs) const noexcept
{
    return Complex((m_real + rhs), m_imag);
}

Complex Complex::operator-(double rhs) const noexcept
{
    return Complex((m_real - rhs), m_imag);
}

Complex Complex::operator*(double rhs) const noexcept
{
    return Complex((m_real * rhs), (m_imag * rhs));
}

Complex Complex::operator/(double rhs) const noexcept
{
    const double real_part = (m_real / rhs);
    const double imag_part = (m_imag / rhs);
    return Complex(real_part, imag_part);
}

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
    const double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    const double real_part = ((lhs * rhs.real()) / denom);
    const double imag_part = ((-(lhs * rhs.imag())) / denom);
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
