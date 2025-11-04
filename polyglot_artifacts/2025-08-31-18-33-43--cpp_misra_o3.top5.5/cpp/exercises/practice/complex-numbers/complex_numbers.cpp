#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

namespace complex_numbers {

//---------------------------------------------------------------------------
// Complex : constructors and accessors
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
// Complex : fundamental operations
//---------------------------------------------------------------------------


double Complex::abs() const noexcept
{
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

//---------------------------------------------------------------------------
// Added member aliases required by tests
//---------------------------------------------------------------------------

Complex Complex::conj() const noexcept
{
    return Complex(m_real, (-m_imag));
}

Complex Complex::exp() const
{
    // delegate to the free-standing implementation to avoid code duplication
    return complex_numbers::exp(*this);
}

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
    const double newReal = ((m_real * rhs.m_real) - (m_imag * rhs.m_imag));
    const double newImag = ((m_imag * rhs.m_real) + (m_real * rhs.m_imag));
    m_real = newReal;
    m_imag = newImag;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    const double denom = ((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag));
    if (denom == 0.0) {
        throw std::invalid_argument("Division by zero complex number");
    }

    const double newReal =
        (((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denom);
    const double newImag =
        (((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denom);

    m_real = newReal;
    m_imag = newImag;
    return *this;
}

 //---------------------------------------------------------------------------
// Non-member operator helpers
//---------------------------------------------------------------------------

bool operator==(const Complex& lhs, const Complex& rhs) noexcept
{
    constexpr double epsilon = 1.0e-12;
    return ((std::fabs(lhs.real() - rhs.real()) < epsilon) &&
            (std::fabs(lhs.imag() - rhs.imag()) < epsilon));
}

bool operator!=(const Complex& lhs, const Complex& rhs) noexcept
{
    return !(lhs == rhs);
}

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

//------------------------------------------------------------------------------
// binary operators with two Complex operands
//------------------------------------------------------------------------------

Complex operator/(Complex lhs, const Complex& rhs)
{
    lhs /= rhs;
    return lhs;
}

//------------------------------------------------------------------------------
// operators mixing Complex with double
//------------------------------------------------------------------------------

Complex operator+(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() + rhs), lhs.imag());
}

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() - rhs), lhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs - rhs.real()), (-rhs.imag()));
}

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
        throw std::invalid_argument("Division by zero scalar");
    }
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

Complex operator/(double lhs, const Complex& rhs)
{
    return Complex(lhs, 0.0) / rhs;
}

//---------------------------------------------------------------------------
// Exponential of a complex number
//---------------------------------------------------------------------------

Complex exp(const Complex& z)
{
    const double expReal = std::exp(z.real());
    const double realPart = expReal * std::cos(z.imag());
    const double imagPart = expReal * std::sin(z.imag());
//------------------------------------------------------------------------------
// free-standing helpers
//------------------------------------------------------------------------------

    return Complex(realPart, imagPart);
}

double abs(const Complex& z) noexcept
{
    return z.abs();
}

}  // namespace complex_numbers
