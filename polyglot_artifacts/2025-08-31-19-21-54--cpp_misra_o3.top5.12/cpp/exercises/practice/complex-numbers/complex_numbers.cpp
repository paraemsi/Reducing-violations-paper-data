#include "complex_numbers.h"

#include <cmath>
#include <limits>

namespace complex_numbers {




Complex Complex::operator+(const Complex& rhs) const noexcept
{
    return Complex{(m_real + rhs.m_real), (m_imag + rhs.m_imag)};
}

Complex Complex::operator-(const Complex& rhs) const noexcept
{
    return Complex{(m_real - rhs.m_real), (m_imag - rhs.m_imag)};
}

Complex Complex::operator*(const Complex& rhs) const noexcept
{
    const double real_part{((m_real * rhs.m_real) - (m_imag * rhs.m_imag))};
    const double imag_part{((m_imag * rhs.m_real) + (m_real * rhs.m_imag))};
    return Complex{real_part, imag_part};
}

Complex Complex::operator/(const Complex& rhs) const
{
    const double denominator{((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag))};

    /* Guard against division by zero – behaviour is undefined, but we avoid a
       floating-point exception by propagating infinities/NaNs that std::numeric_limits
       would generate implicitly. */
    if (denominator == 0.0) {
        return Complex{std::numeric_limits<double>::infinity(),
                       std::numeric_limits<double>::infinity()};
    }

    const double real_part{(((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denominator)};
    const double imag_part{(((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denominator)};
    return Complex{real_part, imag_part};
}

Complex Complex::conj() const noexcept
{
    return Complex{m_real, -m_imag};
}

double Complex::abs() const noexcept
{
    return std::sqrt(((m_real * m_real) + (m_imag * m_imag)));
}

Complex Complex::exp() const
{
    const double exp_real{std::exp(m_real)};
    const double real_part{(exp_real * std::cos(m_imag))};
    const double imag_part{(exp_real * std::sin(m_imag))};
    return Complex{real_part, imag_part};
}

}  // namespace complex_numbers
