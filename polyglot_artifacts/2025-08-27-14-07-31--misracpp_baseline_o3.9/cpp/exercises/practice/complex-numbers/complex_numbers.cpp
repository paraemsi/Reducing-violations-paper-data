#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

namespace complex_numbers {

// ---------------------------
//  Complex implementation
// ---------------------------


double Complex::real() const
{
    return m_real;
}

double Complex::imag() const
{
    return m_imag;
}

Complex Complex::operator+(const Complex& rhs) const
{
    return {m_real + rhs.m_real, m_imag + rhs.m_imag};
}

Complex Complex::operator-(const Complex& rhs) const
{
    return {m_real - rhs.m_real, m_imag - rhs.m_imag};
}

Complex Complex::operator*(const Complex& rhs) const
{
    return {m_real * rhs.m_real - m_imag * rhs.m_imag,
            m_imag * rhs.m_real + m_real * rhs.m_imag};
}

Complex Complex::operator/(const Complex& rhs) const
{
    double denom = rhs.m_real * rhs.m_real + rhs.m_imag * rhs.m_imag;
    if (denom == 0.0)
    {
        throw std::domain_error("Division by zero complex number");
    }
    return {(m_real * rhs.m_real + m_imag * rhs.m_imag) / denom,
            (m_imag * rhs.m_real - m_real * rhs.m_imag) / denom};
}

Complex Complex::conjugate() const
{
    return {m_real, -m_imag};
}

double Complex::abs() const
{
    return std::sqrt(m_real * m_real + m_imag * m_imag);
}

Complex Complex::exp() const
{
    double factor = std::exp(m_real);
    return {factor * std::cos(m_imag), factor * std::sin(m_imag)};
}
 
// ---------------------------
//  non-member helper wrappers
// ---------------------------
 
Complex conjugate(const Complex& z)
{
    return z.conjugate();
}
 
double abs(const Complex& z)
{
    return z.abs();
}
 
Complex exp(const Complex& z)
{
    return z.exp();
}

// arithmetic with a real value on the left-hand side
Complex operator+(double lhs, const Complex& rhs)
{
    return {lhs + rhs.real(), rhs.imag()};
}

Complex operator-(double lhs, const Complex& rhs)
{
    return {lhs - rhs.real(), -rhs.imag()};
}

Complex operator*(double lhs, const Complex& rhs)
{
    return {lhs * rhs.real(), lhs * rhs.imag()};
}

Complex operator/(double lhs, const Complex& rhs)
{
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    if (denom == 0.0)
    {
        throw std::domain_error("Division by zero complex number");
    }
    return {(lhs * rhs.real()) / denom,
            (-lhs * rhs.imag()) / denom};
}

}  // namespace complex_numbers
