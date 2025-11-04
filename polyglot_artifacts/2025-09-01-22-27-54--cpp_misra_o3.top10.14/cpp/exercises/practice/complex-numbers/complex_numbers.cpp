#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

namespace complex_numbers {

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
    const double new_real = ((m_real * rhs.m_real) - (m_imag * rhs.m_imag));
    const double new_imag = ((m_imag * rhs.m_real) + (m_real * rhs.m_imag));
    m_real = new_real;
    m_imag = new_imag;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    const double denom = ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag));
    if (denom == 0.0)
    {
        throw std::runtime_error("Division by zero in Complex::operator/=");
    }
    const double new_real = (((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denom);
    const double new_imag = (((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denom);
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
    return conjugate();
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
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

bool operator==(const Complex& lhs, const Complex& rhs) noexcept
{
    return ((lhs.real() == rhs.real()) && (lhs.imag() == rhs.imag()));
}

bool operator!=(const Complex& lhs, const Complex& rhs) noexcept
{
    return !(lhs == rhs);
}

/* Helper free functions */

Complex conj(const Complex& value) noexcept
{
    return value.conjugate();
}

Complex conjugate(const Complex& value) noexcept
{
    return value.conjugate();
}

double abs(const Complex& value) noexcept
{
    return value.abs();
}

Complex exp(const Complex& value)
{
    const double exp_real  = std::exp(value.real());
    const double cos_imag  = std::cos(value.imag());
    const double sin_imag  = std::sin(value.imag());

    const double real_part = (exp_real * cos_imag);
    const double imag_part = (exp_real * sin_imag);

    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
