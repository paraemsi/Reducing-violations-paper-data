#include "complex_numbers.h"

namespace complex_numbers {

Complex::Complex(float_alias real, float_alias imag)
    : m_real(real), m_imag(imag)
{
}

float_alias Complex::real() const
{
    return m_real;
}

float_alias Complex::imag() const
{
    return m_imag;
}

Complex Complex::operator+(const Complex& other) const
{
    return Complex((m_real + other.m_real), (m_imag + other.m_imag));
}

Complex Complex::operator-(const Complex& other) const
{
    return Complex((m_real - other.m_real), (m_imag - other.m_imag));
}

Complex Complex::operator*(const Complex& other) const
{
    float_alias real_part = ((m_real * other.m_real) - (m_imag * other.m_imag));
    float_alias imag_part = ((m_imag * other.m_real) + (m_real * other.m_imag));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const
{
    float_alias denom = ((other.m_real * other.m_real) + (other.m_imag * other.m_imag));
    float_alias real_part = ((m_real * other.m_real) + (m_imag * other.m_imag)) / denom;
    float_alias imag_part = ((m_imag * other.m_real) - (m_real * other.m_imag)) / denom;
    return Complex(real_part, imag_part);
}

// Scalar overloads (member)
Complex Complex::operator+(float_alias rhs) const
{
    return Complex((m_real + rhs), m_imag);
}

Complex Complex::operator-(float_alias rhs) const
{
    return Complex((m_real - rhs), m_imag);
}

Complex Complex::operator*(float_alias rhs) const
{
    return Complex((m_real * rhs), (m_imag * rhs));
}

Complex Complex::operator/(float_alias rhs) const
{
    return Complex((m_real / rhs), (m_imag / rhs));
}

// Scalar overloads (non-member, friend)
Complex operator+(float_alias lhs, const Complex& rhs)
{
    return Complex((lhs + rhs.m_real), rhs.m_imag);
}

Complex operator-(float_alias lhs, const Complex& rhs)
{
    return Complex((lhs - rhs.m_real), (0.0 - rhs.m_imag));
}

Complex operator*(float_alias lhs, const Complex& rhs)
{
    return Complex((lhs * rhs.m_real), (lhs * rhs.m_imag));
}

Complex operator/(float_alias lhs, const Complex& rhs)
{
    // lhs / rhs = (lhs + 0i) / (rhs.m_real + rhs.m_imag i)
    float_alias denom = ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag));
    float_alias real_part = (lhs * rhs.m_real) / denom;
    float_alias imag_part = (0.0 - (lhs * rhs.m_imag)) / denom;
    return Complex(real_part, imag_part);
}

Complex Complex::conj() const
{
    return Complex(m_real, -m_imag);
}

float_alias Complex::abs() const
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::exp() const
{
    float_alias exp_real = std::exp(m_real);
    float_alias real_part = exp_real * std::cos(m_imag);
    float_alias imag_part = exp_real * std::sin(m_imag);
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
