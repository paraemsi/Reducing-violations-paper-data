#include "complex_numbers.h"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace complex_numbers {

/* ----  Constructors and basic accessors --------------------------------- */




/* ----  Unary helpers ---------------------------------------------------- */

Complex Complex::conjugate() const noexcept
{
    return Complex(m_real, (-m_imag));
}

double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::exp() const noexcept
{
    double const exp_real{std::exp(m_real)};
    double const cos_imag{std::cos(m_imag)};
    double const sin_imag{std::sin(m_imag)};
    return Complex((exp_real * cos_imag), (exp_real * sin_imag));
}

/* ----  Symmetrical binary operators ------------------------------------ */

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.m_real + rhs.m_real), (lhs.m_imag + rhs.m_imag));
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.m_real - rhs.m_real), (lhs.m_imag - rhs.m_imag));
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    double const real_part{(lhs.m_real * rhs.m_real) - (lhs.m_imag * rhs.m_imag)};
    double const imag_part{(lhs.m_imag * rhs.m_real) + (lhs.m_real * rhs.m_imag)};
    return Complex(real_part, imag_part);
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    double const denom{(rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag)};
    if (denom == 0.0) {
        throw std::domain_error("Division by zero magnitude complex number");
    }

    double const real_part{
        ((lhs.m_real * rhs.m_real) + (lhs.m_imag * rhs.m_imag)) / denom
    };
    double const imag_part{
        ((lhs.m_imag * rhs.m_real) - (lhs.m_real * rhs.m_imag)) / denom
    };
    return Complex(real_part, imag_part);
}

/* ----  Free-function wrappers ------------------------------------------ */

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

Complex conjugate(const Complex& value) noexcept
{
    return value.conjugate();
}

double abs(const Complex& value) noexcept
{
    return value.abs();
}

Complex exp(const Complex& value) noexcept
{
    return value.exp();
}

}  // namespace complex_numbers
