#include "complex_numbers.h"
#include <stdexcept>
#include <cmath>

namespace complex_numbers {

/* ---- Constructors ----------------------------------------------------- */

Complex::Complex() noexcept
    : m_real(0.0), m_imag(0.0)
{
    /* empty */
}

Complex::Complex(double realPart, double imagPart) noexcept
    : m_real(realPart), m_imag(imagPart)
{
    /* empty */
}

/* ---- Accessors -------------------------------------------------------- */

double Complex::real() const noexcept
{
    return m_real;
}

double Complex::imag() const noexcept
{
    return m_imag;
}

/* ---- Elementary operations ------------------------------------------- */

Complex Complex::conjugate() const noexcept
{
    return Complex(m_real, -m_imag);
}

Complex Complex::conj() const noexcept
{
    return conjugate();
}

double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

double Complex::abs2() const noexcept
{
    return (m_real * m_real) + (m_imag * m_imag);
}

Complex Complex::exp() const noexcept
{
    const double exp_real = std::exp(m_real);
    const double cos_imag = std::cos(m_imag);
    const double sin_imag = std::sin(m_imag);
    return Complex((exp_real * cos_imag), (exp_real * sin_imag));
}

/* ---- Compound assignment operators ----------------------------------- */

Complex& Complex::operator+=(const Complex& rhs) noexcept
{
    m_real += rhs.m_real;
    m_imag += rhs.m_imag;
    return *this;
}

/* ---- Compound assignment with scalar (double) ------------------------ */

Complex& Complex::operator+=(const double rhs) noexcept
{
    m_real += rhs;
    return *this;
}

Complex& Complex::operator-=(const double rhs) noexcept
{
    m_real -= rhs;
    return *this;
}

Complex& Complex::operator*=(const double rhs) noexcept
{
    m_real *= rhs;
    m_imag *= rhs;
    return *this;
}

Complex& Complex::operator/=(const double rhs)
{
    if (rhs == 0.0)
    {
        throw std::invalid_argument("Division by zero scalar");
    }
    m_real /= rhs;
    m_imag /= rhs;
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

    if (denom == 0.0)
    {
        throw std::invalid_argument("Division by zero complex number");
    }

    const double new_real = ((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denom;
    const double new_imag = ((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denom;
    m_real = new_real;
    m_imag = new_imag;
    return *this;
}

/* ---- Free symmetrical operators -------------------------------------- */

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

/* Mixed complex / scalar (double) arithmetic --------------------------- */

Complex operator+(Complex lhs, const double rhs) noexcept
{
    lhs += Complex(rhs, 0.0);
    return lhs;
}

Complex operator+(const double lhs, const Complex& rhs) noexcept
{
    return (Complex(lhs, 0.0) + rhs);
}

Complex operator-(Complex lhs, const double rhs) noexcept
{
    lhs -= Complex(rhs, 0.0);
    return lhs;
}

Complex operator-(const double lhs, const Complex& rhs) noexcept
{
    return (Complex(lhs, 0.0) - rhs);
}

Complex operator*(Complex lhs, const double rhs) noexcept
{
    lhs *= Complex(rhs, 0.0);
    return lhs;
}

Complex operator*(const double lhs, const Complex& rhs) noexcept
{
    return (Complex(lhs, 0.0) * rhs);
}

Complex operator/(Complex lhs, const double rhs)
{
    if (rhs == 0.0)
    {
        throw std::invalid_argument("Division by zero scalar");
    }
    lhs /= Complex(rhs, 0.0);
    return lhs;
}

Complex operator/(const double lhs, const Complex& rhs)
{
    return (Complex(lhs, 0.0) / rhs);
}

/* Equality operators ---------------------------------------------------- */

bool operator==(const Complex& lhs, const Complex& rhs) noexcept
{
    return ((lhs.real() == rhs.real()) && (lhs.imag() == rhs.imag()));
}

bool operator!=(const Complex& lhs, const Complex& rhs) noexcept
{
    return !(lhs == rhs);
}

}  // namespace complex_numbers
