#include "complex_numbers.h"
#include <cmath>
#include <stdexcept>

namespace complex_numbers {


double Complex::real() const noexcept
{
    return m_real;
}

double Complex::imag() const noexcept
{
    return m_imag;
}

Complex Complex::conj() const noexcept
{
    return Complex(m_real, (-m_imag));
}

double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::exp() const
{
    const double expReal = std::exp(m_real);
    const double cosImag = std::cos(m_imag);
    const double sinImag = std::sin(m_imag);
    return Complex((expReal * cosImag), (expReal * sinImag));
}

Complex& Complex::operator+=(const Complex& rhs) noexcept
{
    m_real += rhs.m_real;
    m_imag += rhs.m_imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& rhs) noexcept
{
    m_real -= rhs.m_real;
    m_imag -= rhs.m_imag;
    return *this;
}

Complex& Complex::operator*=(const Complex& rhs) noexcept
{
    const double newReal = (m_real * rhs.m_real) - (m_imag * rhs.m_imag);
    const double newImag = (m_imag * rhs.m_real) + (m_real * rhs.m_imag);
    m_real = newReal;
    m_imag = newImag;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    const double denominator = (rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag);
    if (denominator == 0.0)
    {
        throw std::invalid_argument("Division by zero complex number");
    }
    const double newReal = ((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denominator;
    const double newImag = ((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denominator;
    m_real = newReal;
    m_imag = newImag;
    return *this;
}

/* Non-member symmetrical operators */

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    Complex result(lhs);
    result += rhs;
    return result;
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    Complex result(lhs);
    result -= rhs;
    return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    Complex result(lhs);
    result *= rhs;
    return result;
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    Complex result(lhs);
    result /= rhs;
    return result;
}

}  // namespace complex_numbers
