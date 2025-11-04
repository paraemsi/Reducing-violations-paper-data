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
    float_type real_part = ((m_real * rhs.m_real) - (m_imag * rhs.m_imag));
    float_type imag_part = ((m_imag * rhs.m_real) + (m_real * rhs.m_imag));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& rhs) const
{
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
    return std::sqrt(((m_real * m_real) + (m_imag * m_imag)));
}

Complex Complex::exp() const
{
    float_type exp_real = std::exp(m_real);
    float_type real_part = (exp_real * std::cos(m_imag));
    float_type imag_part = (exp_real * std::sin(m_imag));
    return Complex(real_part, imag_part);
}

// Arithmetic with real numbers (member functions)
Complex Complex::operator+(float_type rhs) const
{
    return Complex((m_real + rhs), m_imag);
}

Complex Complex::operator-(float_type rhs) const
{
    return Complex((m_real - rhs), m_imag);
}

Complex Complex::operator*(float_type rhs) const
{
    return Complex((m_real * rhs), (m_imag * rhs));
}

Complex Complex::operator/(float_type rhs) const
{
    return Complex((m_real / rhs), (m_imag / rhs));
}

// Non-member operators for real op Complex
Complex operator+(float_type lhs, const Complex& rhs)
{
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(float_type lhs, const Complex& rhs)
{
    return Complex((lhs - rhs.real()), (0.0 - rhs.imag()));
}

Complex operator*(float_type lhs, const Complex& rhs)
{
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(float_type lhs, const Complex& rhs)
{
    // (a) / (c + id) = (a * c)/(c^2 + d^2) + ( -a * d)/(c^2 + d^2) * i
    float_type denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    float_type real_part = ((lhs * rhs.real()) / denom);
    float_type imag_part = ((-lhs * rhs.imag()) / denom);
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
