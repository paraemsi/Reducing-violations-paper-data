#include "complex_numbers.h"

#include <cmath>    // std::sqrt, std::exp, std::cos, std::sin
#include <cstdint>  // Fixed-width integer types per MISRA (not used but included for completeness)

namespace complex_numbers {

/* Constructor */
constexpr Complex::Complex(double real_value, double imag_value) noexcept
    : m_real(real_value),
      m_imag(imag_value)
{
    /* Initialiser list fully initialises members */
}

/* Accessors */
constexpr double Complex::real() const noexcept
{
    return m_real;
}

constexpr double Complex::imag() const noexcept
{
    return m_imag;
}

/* Addition */
constexpr Complex Complex::operator+(const Complex& other) const noexcept
{
    return Complex{ (m_real + other.m_real), (m_imag + other.m_imag) };
}

/* Subtraction */
constexpr Complex Complex::operator-(const Complex& other) const noexcept
{
    return Complex{ (m_real - other.m_real), (m_imag - other.m_imag) };
}

/* Multiplication */
constexpr Complex Complex::operator*(const Complex& other) const noexcept
{
    double const new_real{ ((m_real * other.m_real) - (m_imag * other.m_imag)) };
    double const new_imag{ ((m_imag * other.m_real) + (m_real * other.m_imag)) };
    return Complex{ new_real, new_imag };
}

/* Division */
Complex Complex::operator/(const Complex& other) const
{
    double const denominator{ ((other.m_real * other.m_real) + (other.m_imag * other.m_imag)) };

    /* Division by zero yields implementation-defined behaviour for floating types.
       The caller is responsible for avoiding a zero denominator. */
    double const new_real{ (((m_real * other.m_real) + (m_imag * other.m_imag)) / denominator) };
    double const new_imag{ (((m_imag * other.m_real) - (m_real * other.m_imag)) / denominator) };

    return Complex{ new_real, new_imag };
}

/* Conjugate */
constexpr Complex Complex::conj() const noexcept
{
    return Complex{ m_real, (-m_imag) };
}

/* Absolute value (magnitude) */
double Complex::abs() const
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

/* Exponential */
Complex Complex::exp() const
{
    double const exp_real{ std::exp(m_real) };
    double const new_real{ (exp_real * std::cos(m_imag)) };
    double const new_imag{ (exp_real * std::sin(m_imag)) };
    return Complex{ new_real, new_imag };
}

/* -------------------------------------------------------------------------- */
/* Free-standing arithmetic                                                   */
/* -------------------------------------------------------------------------- */
constexpr Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return (Complex{ lhs, 0.0 } + rhs);
}

constexpr Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return (Complex{ lhs, 0.0 } - rhs);
}

constexpr Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return (Complex{ lhs, 0.0 } * rhs);
}

Complex operator/(double lhs, const Complex& rhs)
{
    return (Complex{ lhs, 0.0 } / rhs);
}

}  // namespace complex_numbers
