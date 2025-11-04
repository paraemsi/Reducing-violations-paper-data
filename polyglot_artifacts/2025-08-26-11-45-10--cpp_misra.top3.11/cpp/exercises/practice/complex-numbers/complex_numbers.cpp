#include "complex_numbers.h"

namespace complex_numbers {

Complex::Complex(float_alias real_value, float_alias imag_value)
    : m_real(real_value), m_imag(imag_value)
{
}

float_alias Complex::real(void) const
{
    return m_real;
}

float_alias Complex::imag(void) const
{
    return m_imag;
}

Complex Complex::operator+(const Complex& rhs) const
{
    return Complex((m_real + rhs.m_real), (m_imag + rhs.m_imag));
}

Complex Complex::operator-(const Complex& rhs) const
{
    return Complex((m_real - rhs.m_real), (m_imag - rhs.m_imag));
}

Complex Complex::operator*(const Complex& rhs) const
{
    // (a + i*b) * (c + i*d) = (a*c - b*d) + (b*c + a*d) * i
    float_alias real_part = ((m_real * rhs.m_real) - (m_imag * rhs.m_imag));
    float_alias imag_part = ((m_imag * rhs.m_real) + (m_real * rhs.m_imag));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& rhs) const
{
    // (a + i*b) / (c + i*d) = ((a*c + b*d)/(c^2 + d^2)) + ((b*c - a*d)/(c^2 + d^2)) * i
    float_alias denom = ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag));
    float_alias real_part = (((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denom);
    float_alias imag_part = (((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denom);
    return Complex(real_part, imag_part);
}

Complex Complex::conj(void) const
{
    return Complex(m_real, -m_imag);
}

float_alias Complex::abs(void) const
{
    // sqrt(a^2 + b^2)
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::exp(void) const
{
    // e^(a + i*b) = e^a * (cos(b) + i*sin(b))
    float_alias exp_real = std::exp(m_real);
    float_alias real_part = (exp_real * std::cos(m_imag));
    float_alias imag_part = (exp_real * std::sin(m_imag));
    return Complex(real_part, imag_part);
}

// Scalar overloads for arithmetic with double on either side

Complex operator+(const Complex& lhs, float_alias rhs)
{
    return Complex(lhs.m_real + rhs, lhs.m_imag);
}

Complex operator+(float_alias lhs, const Complex& rhs)
{
    return Complex(lhs + rhs.m_real, rhs.m_imag);
}

Complex operator-(const Complex& lhs, float_alias rhs)
{
    return Complex(lhs.m_real - rhs, lhs.m_imag);
}

Complex operator-(float_alias lhs, const Complex& rhs)
{
    return Complex(lhs - rhs.m_real, -rhs.m_imag);
}

Complex operator*(const Complex& lhs, float_alias rhs)
{
    return Complex(lhs.m_real * rhs, lhs.m_imag * rhs);
}

Complex operator*(float_alias lhs, const Complex& rhs)
{
    return Complex(lhs * rhs.m_real, lhs * rhs.m_imag);
}

Complex operator/(const Complex& lhs, float_alias rhs)
{
    return Complex(lhs.m_real / rhs, lhs.m_imag / rhs);
}

Complex operator/(float_alias lhs, const Complex& rhs)
{
    // lhs / (a + i*b) = (lhs * a)/(a^2 + b^2) - (lhs * b)/(a^2 + b^2) * i
    float_alias denom = (rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag);
    float_alias real_part = (lhs * rhs.m_real) / denom;
    float_alias imag_part = (-lhs * rhs.m_imag) / denom;
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
