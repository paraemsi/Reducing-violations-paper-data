#include "complex_numbers.h"

namespace complex_numbers {

Complex::Complex(float_type real_value, float_type imag_value)
    : m_real(real_value), m_imag(imag_value)
{
}

float_type Complex::real() const
{
    return m_real;
}

float_type Complex::imag() const
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
    float_type real_part = ((m_real * rhs.m_real) - (m_imag * rhs.m_imag));
    float_type imag_part = ((m_imag * rhs.m_real) + (m_real * rhs.m_imag));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& rhs) const
{
    // (a + i*b) / (c + i*d) = ((a*c + b*d)/(c^2 + d^2)) + ((b*c - a*d)/(c^2 + d^2)) * i
    float_type denom = ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag));
    float_type real_part = (((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denom);
    float_type imag_part = (((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denom);
    return Complex(real_part, imag_part);
}

Complex Complex::conj() const
{
    return Complex(m_real, -m_imag);
}

float_type Complex::abs() const
{
    // sqrt(a^2 + b^2)
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::exp() const
{
    // e^(a + i*b) = e^a * (cos(b) + i*sin(b))
    float_type exp_real = std::exp(m_real);
    float_type real_part = (exp_real * std::cos(m_imag));
    float_type imag_part = (exp_real * std::sin(m_imag));
    return Complex(real_part, imag_part);
}

Complex Complex::operator+(float_type rhs) const
{
    // (a + bi) + r = (a + r) + bi
    return Complex((m_real + rhs), m_imag);
}

Complex Complex::operator-(float_type rhs) const
{
    // (a + bi) - r = (a - r) + bi
    return Complex((m_real - rhs), m_imag);
}

Complex Complex::operator*(float_type rhs) const
{
    // (a + bi) * r = (a*r) + (b*r)i
    return Complex((m_real * rhs), (m_imag * rhs));
}

Complex Complex::operator/(float_type rhs) const
{
    // (a + bi) / r = (a/r) + (b/r)i
    return Complex((m_real / rhs), (m_imag / rhs));
}

Complex operator+(float_type lhs, const Complex& rhs)
{
    // r + (a + bi) = (r + a) + bi
    return Complex((lhs + rhs.m_real), rhs.m_imag);
}

Complex operator-(float_type lhs, const Complex& rhs)
{
    // r - (a + bi) = (r - a) - bi
    return Complex((lhs - rhs.m_real), (-rhs.m_imag));
}

Complex operator*(float_type lhs, const Complex& rhs)
{
    // r * (a + bi) = (r*a) + (r*b)i
    return Complex((lhs * rhs.m_real), (lhs * rhs.m_imag));
}

Complex operator/(float_type lhs, const Complex& rhs)
{
    // r / (a + bi) = (r * (a - bi)) / (a^2 + b^2)
    float_type denom = ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag));
    float_type real_part = ((lhs * rhs.m_real) / denom);
    float_type imag_part = ((-lhs * rhs.m_imag) / denom);
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
