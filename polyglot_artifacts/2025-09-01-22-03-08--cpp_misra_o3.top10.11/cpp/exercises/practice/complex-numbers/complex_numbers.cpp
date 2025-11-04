#include "complex_numbers.h"

#include <stdexcept>

namespace complex_numbers {

/* ---- constructors ----------------------------------------------------- */
Complex::Complex(double real_val, double imag_val) noexcept
    : m_real(real_val),
      m_imag(imag_val)
{
}

/* ---- accessors -------------------------------------------------------- */
double Complex::real() const noexcept
{
    return m_real;
}

double Complex::imag() const noexcept
{
    return m_imag;
}

/* ---- compound assignment operators ----------------------------------- */
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
    const double denom = (rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag);

    if (denom == 0.0) {
        throw std::domain_error("Division by zero complex number");
    }

    const double new_real = ((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denom;
    const double new_imag = ((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denom;

    m_real = new_real;
    m_imag = new_imag;
    return *this;
}

/* ---- unary operators -------------------------------------------------- */
Complex Complex::operator-() const noexcept
{
    return Complex(-m_real, -m_imag);
}

/* ---- mathematical helpers -------------------------------------------- */
Complex Complex::conj() const noexcept
{
    return Complex(m_real, -m_imag);
}

double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::exp() const
{
    const double e_to_real = std::exp(m_real);
    const double cos_imag = std::cos(m_imag);
    const double sin_imag = std::sin(m_imag);

    return Complex((e_to_real * cos_imag), (e_to_real * sin_imag));
}

/* ---- free symmetrical operators -------------------------------------- */
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

/* ---- scalar operators ------------------------------------------------- */
Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(const Complex& lhs, double rhs)
{
    if (rhs == 0.0) {
        throw std::domain_error("Division by zero scalar");
    }

    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

}   // namespace complex_numbers
