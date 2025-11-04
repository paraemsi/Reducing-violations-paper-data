#include "complex_numbers.h"
#include <stdexcept>

namespace complex_numbers {

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
    const double old_real = m_real;
    const double old_imag = m_imag;

    m_real = ( (old_real * rhs.m_real) - (old_imag * rhs.m_imag) );
    m_imag = ( (old_imag * rhs.m_real) + (old_real * rhs.m_imag) );
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
    const double denom = (rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag);

    if(denom == 0.0) {
        throw std::domain_error("Division by zero complex number");
    }

    const double old_real = m_real;
    const double old_imag = m_imag;

    m_real = ( ( (old_real * rhs.m_real) + (old_imag * rhs.m_imag) ) / denom );
    m_imag = ( ( (old_imag * rhs.m_real) - (old_real * rhs.m_imag) ) / denom );
    return *this;
}

Complex exp(const Complex& z)
{
    const double growth = std::exp(z.real());
    const double real_part = growth * std::cos(z.imag());
    const double imag_part = growth * std::sin(z.imag());
    return Complex(real_part, imag_part);
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

}  // namespace complex_numbers
