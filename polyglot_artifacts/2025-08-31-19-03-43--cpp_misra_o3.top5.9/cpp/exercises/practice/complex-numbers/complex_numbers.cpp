#include "complex_numbers.h"

#include <cmath>    // std::sqrt, std::exp, std::cos, std::sin

namespace complex_numbers {


/* Accessors */
double Complex::real() const noexcept
{
    return m_real;
}

double Complex::imag() const noexcept
{
    return m_imag;
}

/* Compound assignments */
Complex& Complex::operator+=(const Complex& rhs) noexcept
{
    m_real = (m_real + rhs.m_real);
    m_imag = (m_imag + rhs.m_imag);
    return *this;
}

Complex& Complex::operator-=(const Complex& rhs) noexcept
{
    m_real = (m_real - rhs.m_real);
    m_imag = (m_imag - rhs.m_imag);
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
    /* (a + i b) / (c + i d) */
    const double denom = ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag));

    /* Behaviour is undefined for division by zero; caller’s responsibility */
    const double new_real =
        (((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denom);
    const double new_imag =
        (((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denom);

    m_real = new_real;
    m_imag = new_imag;
    return *this;
}

/* Helper operations */
Complex Complex::conjugate() const noexcept
{
    return Complex(m_real, -m_imag);
}

double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

/* Provide alias name used by some test-suites */
Complex Complex::conj() const noexcept
{
    return conjugate();
}

/* Member exponential forwards to free function */
Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

/* Binary operators */
Complex operator+(Complex lhs, const Complex& rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

Complex operator-(Complex lhs, const Complex& rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}

Complex operator*(Complex lhs, const Complex& rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

Complex operator/(Complex lhs, const Complex& rhs)
{
    lhs /= rhs;
    return lhs;
}

/* Exponential: e^(a + i b) = e^a (cos b + i sin b) */
Complex exp(const Complex& z)
{
    const double exp_real = std::exp(z.real());
    const double cos_imag = std::cos(z.imag());
    const double sin_imag = std::sin(z.imag());

    const double real_part = (exp_real * cos_imag);
    const double imag_part = (exp_real * sin_imag);

    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
