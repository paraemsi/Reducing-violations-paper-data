#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

namespace complex_numbers {

Complex::Complex(double real_val, double imag_val) noexcept
    : m_real(real_val),
      m_imag(imag_val)
{
    /* Constructor body intentionally empty */
}

double Complex::real() const noexcept
{
    return m_real;
}

double Complex::imag() const noexcept
{
    return m_imag;
}

Complex& Complex::operator+=(const Complex& other) noexcept
{
    m_real = m_real + other.m_real;
    m_imag = m_imag + other.m_imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) noexcept
{
    m_real = m_real - other.m_real;
    m_imag = m_imag - other.m_imag;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) noexcept
{
    const double new_real = (m_real * other.m_real) - (m_imag * other.m_imag);
    const double new_imag = (m_imag * other.m_real) + (m_real * other.m_imag);
    m_real = new_real;
    m_imag = new_imag;
    return *this;
}

Complex& Complex::operator/=(const Complex& other)
{
    const double denominator = (other.m_real * other.m_real) + (other.m_imag * other.m_imag);
    /* Division by zero check */
    if (denominator == 0.0)
    {
        throw std::runtime_error("Division by zero in Complex::operator/=");
    }

    const double new_real = ((m_real * other.m_real) + (m_imag * other.m_imag)) / denominator;
    const double new_imag = ((m_imag * other.m_real) - (m_real * other.m_imag)) / denominator;
    m_real = new_real;
    m_imag = new_imag;
    return *this;
}

Complex Complex::conjugate() const noexcept
{
    return Complex(m_real, -m_imag);
}

double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::conj() const noexcept
{
    /* Delegate to conjugate() to avoid code duplication */
    return conjugate();
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

/* Free operator definitions */
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

/* Helper functions */
Complex conj(const Complex& z) noexcept
{
    return z.conjugate();
}

double abs(const Complex& z) noexcept
{
    return z.abs();
}

Complex exp(const Complex& z)
{
    const double exp_real = std::exp(z.real());
    const double cos_imag = std::cos(z.imag());
    const double sin_imag = std::sin(z.imag());
    return Complex((exp_real * cos_imag), (exp_real * sin_imag));
}

}  // namespace complex_numbers
