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

Complex& Complex::operator+=(const Complex& other) noexcept
{
    m_real = (m_real + other.m_real);
    m_imag = (m_imag + other.m_imag);
    return *this;
}

Complex& Complex::operator-=(const Complex& other) noexcept
{
    m_real = (m_real - other.m_real);
    m_imag = (m_imag - other.m_imag);
    return *this;
}

Complex& Complex::operator*=(const Complex& other) noexcept
{
    const double new_real = ((m_real * other.m_real) - (m_imag * other.m_imag));
    const double new_imag = ((m_imag * other.m_real) + (m_real * other.m_imag));
    m_real = new_real;
    m_imag = new_imag;
    return *this;
}

Complex& Complex::operator/=(const Complex& other)
{
    const double denom = ((other.m_real * other.m_real) + (other.m_imag * other.m_imag));
    if (denom == 0.0)
    {
        throw std::runtime_error("Division by zero complex number");
    }
    const double new_real = (((m_real * other.m_real) + (m_imag * other.m_imag)) / denom);
    const double new_imag = (((m_imag * other.m_real) - (m_real * other.m_imag)) / denom);
    m_real = new_real;
    m_imag = new_imag;
    return *this;
}

Complex Complex::operator+(const Complex& other) const noexcept
{
    Complex result(*this);
    result += other;
    return result;
}

Complex Complex::operator-(const Complex& other) const noexcept
{
    Complex result(*this);
    result -= other;
    return result;
}

Complex Complex::operator*(const Complex& other) const noexcept
{
    Complex result(*this);
    result *= other;
    return result;
}

Complex Complex::operator/(const Complex& other) const
{
    Complex result(*this);
    result /= other;
    return result;
}

Complex Complex::conjugate() const noexcept
{
    return Complex(m_real, (-m_imag));
}

double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::conj() const noexcept        /* NOLINT(readability-identifier-naming) */
{
    return conjugate();
}

Complex Complex::exp() const                  /* NOLINT(readability-identifier-naming) */
{
    return complex_numbers::exp(*this);
}

Complex exp(const Complex& z)
{
    const double exp_real = std::exp(z.real());
    const double cos_imag = std::cos(z.imag());
    const double sin_imag = std::sin(z.imag());
    const double real_part = (exp_real * cos_imag);
    const double imag_part = (exp_real * sin_imag);
    return Complex(real_part, imag_part);
}

Complex conjugate(const Complex& z) noexcept
{
    return z.conjugate();
}

Complex conj(const Complex& z) noexcept          /* NOLINT(readability-identifier-naming) */
{
    return z.conj();
}

double abs(const Complex& z) noexcept
{
    return z.abs();
}

/* Operators with scalar left-hand operand */
Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return (Complex(lhs, 0.0) + rhs);
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return (Complex(lhs, 0.0) - rhs);
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return (Complex(lhs, 0.0) * rhs);
}

Complex operator/(double lhs, const Complex& rhs)
{
    return (Complex(lhs, 0.0) / rhs);
}

}  // namespace complex_numbers
