#include "complex_numbers.h"

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
    const double new_real = (m_real * rhs.m_real) - (m_imag * rhs.m_imag);
    const double new_imag = (m_imag * rhs.m_real) + (m_real * rhs.m_imag);

    m_real = new_real;
    m_imag = new_imag;

    return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    const double denominator = (rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag);

    if (denominator == 0.0)
    {
        throw std::invalid_argument("Division by zero complex number");
    }

    const double orig_real = m_real;
    const double orig_imag = m_imag;

    m_real = ((orig_real * rhs.m_real) + (orig_imag * rhs.m_imag)) / denominator;
    m_imag = ((orig_imag * rhs.m_real) - (orig_real * rhs.m_imag)) / denominator;

    return *this;
}

/* Non-member symmetrical operators */
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

/* Operations with scalar double */
Complex& Complex::operator+=(double rhs) noexcept
{
    m_real += rhs;
    return *this;
}

Complex& Complex::operator-=(double rhs) noexcept
{
    m_real -= rhs;
    return *this;
}

Complex& Complex::operator*=(double rhs) noexcept
{
    m_real *= rhs;
    m_imag *= rhs;
    return *this;
}

Complex& Complex::operator/=(double rhs)
{
    if (rhs == 0.0)
    {
        throw std::invalid_argument("Division by zero scalar");
    }

    m_real /= rhs;
    m_imag /= rhs;
    return *this;
}

/* Non-member operations with scalar double */
Complex operator+(Complex lhs, double rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

Complex operator+(double lhs, Complex rhs) noexcept
{
    rhs += lhs;
    return rhs;
}

Complex operator-(Complex lhs, double rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}

Complex operator-(double lhs, Complex rhs) noexcept
{
    return Complex(lhs, 0.0) - rhs;
}

Complex operator*(Complex lhs, double rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

Complex operator*(double lhs, Complex rhs) noexcept
{
    rhs *= lhs;
    return rhs;
}

Complex operator/(Complex lhs, double rhs)
{
    lhs /= rhs;
    return lhs;
}

Complex operator/(double lhs, Complex rhs)
{
    return Complex(lhs, 0.0) / rhs;
}

/* Equality operators */
bool operator==(const Complex& lhs, const Complex& rhs) noexcept
{
    return ((lhs.real() == rhs.real()) && (lhs.imag() == rhs.imag()));
}

bool operator!=(const Complex& lhs, const Complex& rhs) noexcept
{
    return !(lhs == rhs);
}

/* Member utility wrappers */
double Complex::abs() const noexcept
{
    return complex_numbers::abs(*this);
}

Complex Complex::conj() const noexcept
{
    return complex_numbers::conjugate(*this);
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

/* Utility functions */
Complex conjugate(const Complex& z) noexcept
{
    return Complex(z.real(), -z.imag());
}

double abs(const Complex& z) noexcept
{
    return std::sqrt((z.real() * z.real()) + (z.imag() * z.imag()));
}

Complex exp(const Complex& z)
{
    const double magnitude = std::exp(z.real());
    const double cos_part  = std::cos(z.imag());
    const double sin_part  = std::sin(z.imag());

    return Complex((magnitude * cos_part), (magnitude * sin_part));
}

} // namespace complex_numbers
