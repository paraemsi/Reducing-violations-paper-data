#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

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

/* Addition */
Complex Complex::operator+(const Complex& other) const noexcept
{
    return Complex((m_real + other.m_real), (m_imag + other.m_imag));
}

/* Subtraction */
Complex Complex::operator-(const Complex& other) const noexcept
{
    return Complex((m_real - other.m_real), (m_imag - other.m_imag));
}

/* Multiplication */
Complex Complex::operator*(const Complex& other) const noexcept
{
    double real_part = ((m_real * other.m_real) - (m_imag * other.m_imag));
    double imag_part = ((m_imag * other.m_real) + (m_real * other.m_imag));
    return Complex(real_part, imag_part);
}


/* Equality */
bool Complex::operator==(const Complex& other) const noexcept
{
    return ((m_real == other.m_real) && (m_imag == other.m_imag));
}

bool Complex::operator!=(const Complex& other) const noexcept
{
    return !((*this) == other);
}

/* Scalar multiplication (Complex * scalar) */
Complex Complex::operator*(double scalar) const noexcept
{
    return Complex((m_real * scalar), (m_imag * scalar));
}

/* Scalar multiplication (scalar * Complex) */
Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

/* Scalar on left-hand side arithmetic operations */

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return (Complex(lhs, 0.0) + rhs);
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return (Complex(lhs, 0.0) - rhs);
}

Complex operator/(double lhs, const Complex& rhs)
{
    return (Complex(lhs, 0.0) / rhs);
}

/* Division */
Complex Complex::operator/(const Complex& other) const
{
    double denom = ((other.m_real * other.m_real) + (other.m_imag * other.m_imag));

    if (denom == 0.0)
    {
        throw std::runtime_error("Division by zero for Complex numbers");
    }

    double real_part = (((m_real * other.m_real) + (m_imag * other.m_imag)) / denom);
    double imag_part = (((m_imag * other.m_real) - (m_real * other.m_imag)) / denom);
    return Complex(real_part, imag_part);
}

/* Conjugate */
Complex Complex::conj() const noexcept
{
    return Complex(m_real, -m_imag);
}

/* Absolute value (magnitude) */
double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

/* Exponential */
Complex Complex::exp() const
{
    double factor = std::exp(m_real);
    double real_part = factor * std::cos(m_imag);
    double imag_part = factor * std::sin(m_imag);
    return Complex(real_part, imag_part);
}

/* ------------------------------------------------------------------ */
/*  Free-function wrappers used by the test suite                      */
/* ------------------------------------------------------------------ */

Complex add(const Complex& lhs, const Complex& rhs) noexcept
{
    return (lhs + rhs);
}

Complex sub(const Complex& lhs, const Complex& rhs) noexcept
{
    return (lhs - rhs);
}

Complex mul(const Complex& lhs, const Complex& rhs) noexcept
{
    return (lhs * rhs);
}

Complex div(const Complex& lhs, const Complex& rhs)
{
    return (lhs / rhs);
}

Complex conj(const Complex& value) noexcept
{
    return value.conj();
}

double abs(const Complex& value) noexcept
{
    return value.abs();
}

Complex exp(const Complex& value)
{
    return value.exp();
}

}  // namespace complex_numbers
