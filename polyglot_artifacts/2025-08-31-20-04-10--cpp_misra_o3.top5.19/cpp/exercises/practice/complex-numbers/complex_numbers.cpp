#include "complex_numbers.h"

namespace complex_numbers {

Complex Complex::operator+(const Complex& rhs) const noexcept
{
    return Complex((m_real + rhs.m_real), (m_imag + rhs.m_imag));
}

Complex Complex::operator-(const Complex& rhs) const noexcept
{
    return Complex((m_real - rhs.m_real), (m_imag - rhs.m_imag));
}

Complex Complex::operator*(const Complex& rhs) const noexcept
{
    /* (a + i b) * (c + i d) = (a c - b d) + (b c + a d) i */
    const double realPart = ((m_real * rhs.m_real) - (m_imag * rhs.m_imag));
    const double imagPart = ((m_imag * rhs.m_real) + (m_real * rhs.m_imag));
    return Complex(realPart, imagPart);
}

Complex Complex::operator/(const Complex& rhs) const
{
    /* (a + i b) / (c + i d) = (a c + b d)/(c² + d²) + (b c - a d)/(c² + d²) i */
    const double denom = ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag));
    if (denom == 0.0)
    {
        throw std::domain_error("Division by zero complex number");
    }
    const double realPart = (((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denom);
    const double imagPart = (((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denom);
    return Complex(realPart, imagPart);
}

bool Complex::operator==(const Complex& rhs) const noexcept
{
    return ((m_real == rhs.m_real) && (m_imag == rhs.m_imag));
}

bool Complex::operator!=(const Complex& rhs) const noexcept
{
    return !(*this == rhs);
}

constexpr Complex Complex::conjugate() const noexcept
{
    return Complex(m_real, (-m_imag));
}

double Complex::abs() const noexcept
{
    return std::sqrt(((m_real * m_real) + (m_imag * m_imag)));
}

constexpr Complex Complex::conj() const noexcept
{
    return conjugate();
}

constexpr Complex Complex::operator*(double scalar) const noexcept
{
    return Complex((m_real * scalar), (m_imag * scalar));
}

constexpr Complex Complex::operator+(double scalar) const noexcept
{
    return Complex((m_real + scalar), m_imag);
}

constexpr Complex Complex::operator-(double scalar) const noexcept
{
    return Complex((m_real - scalar), m_imag);
}

Complex Complex::operator/(double scalar) const
{
    if (scalar == 0.0)
    {
        throw std::domain_error("Division by zero scalar");
    }
    return Complex((m_real / scalar), (m_imag / scalar));
}

Complex operator+(double scalar, const Complex& rhs) noexcept
{
    return Complex((scalar + rhs.real()), rhs.imag());
}

Complex operator-(double scalar, const Complex& rhs) noexcept
{
    return Complex((scalar - rhs.real()), (-rhs.imag()));
}

Complex operator/(double scalar, const Complex& rhs)
{
    const double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    if (denom == 0.0)
    {
        throw std::domain_error("Division by zero complex number");
    }
    const double realPart = ((scalar * rhs.real()) / denom);
    const double imagPart = ((-scalar * rhs.imag()) / denom);
    return Complex(realPart, imagPart);
}

Complex operator*(double scalar, const Complex& rhs) noexcept
{
    return rhs * scalar;
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

Complex conjugate(const Complex& z) noexcept
{
    return z.conjugate();
}

double abs(const Complex& z) noexcept
{
    return z.abs();
}

Complex exp(const Complex& z)
{
    /* e^(a + i b) = e^a * (cos b + i sin b) */
    const double scalar = std::exp(z.real());
    const double realPart = (scalar * std::cos(z.imag()));
    const double imagPart = (scalar * std::sin(z.imag()));
    return Complex(realPart, imagPart);
}

}  // namespace complex_numbers
