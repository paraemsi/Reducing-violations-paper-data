#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

namespace complex_numbers {

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex{(lhs.m_real + rhs.m_real), (lhs.m_imag + rhs.m_imag)};
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex{(lhs.m_real - rhs.m_real), (lhs.m_imag - rhs.m_imag)};
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex{((lhs.m_real * rhs.m_real) - (lhs.m_imag * rhs.m_imag)),
                   ((lhs.m_imag * rhs.m_real) + (lhs.m_real * rhs.m_imag))};
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    const double denominator{((rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag))};

    if (denominator == 0.0)
    {
        throw std::domain_error("Division by zero complex number");
    }

    return Complex{(((lhs.m_real * rhs.m_real) + (lhs.m_imag * rhs.m_imag)) /
                    denominator),
                   (((lhs.m_imag * rhs.m_real) - (lhs.m_real * rhs.m_imag)) /
                    denominator)};
}

bool operator==(const Complex& lhs,
                const Complex& rhs) noexcept
{
    constexpr double epsilon{1.0e-12};

    return ((std::fabs(lhs.m_real - rhs.m_real) <= epsilon) &&
            (std::fabs(lhs.m_imag - rhs.m_imag) <= epsilon));
}

bool operator!=(const Complex& lhs,
                const Complex& rhs) noexcept
{
    return !(lhs == rhs);
}

Complex conjugate(const Complex& value) noexcept
{
    return Complex{value.m_real, (-value.m_imag)};
}

double abs(const Complex& value) noexcept
{
    return std::sqrt(((value.m_real * value.m_real) +
                      (value.m_imag * value.m_imag)));
}

Complex exp(const Complex& value)
{
    const double expReal{std::exp(value.m_real)};
    const double cosImag{std::cos(value.m_imag)};
    const double sinImag{std::sin(value.m_imag)};

    return Complex{(expReal * cosImag), (expReal * sinImag)};
}

}  // namespace complex_numbers

namespace complex_numbers
{
/* member function definitions */
Complex Complex::conj() const noexcept
{
    return Complex{m_real, (-m_imag)};
}

double Complex::abs() const noexcept
{
    return std::sqrt(((m_real * m_real) + (m_imag * m_imag)));
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

/* arithmetic with scalar (double) */
Complex operator+(const Complex& lhs, double rhs) noexcept
{
    return Complex{(lhs.m_real + rhs), lhs.m_imag};
}

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex{(lhs + rhs.m_real), rhs.m_imag};
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    return Complex{(lhs.m_real - rhs), lhs.m_imag};
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex{(lhs - rhs.m_real), (-rhs.m_imag)};
}

Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return Complex{(lhs.m_real * rhs), (lhs.m_imag * rhs)};
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex{(lhs * rhs.m_real), (lhs * rhs.m_imag)};
}

Complex operator/(const Complex& lhs, double rhs)
{
    if (rhs == 0.0)
    {
        throw std::domain_error("Division by zero scalar");
    }

    return Complex{(lhs.m_real / rhs), (lhs.m_imag / rhs)};
}

Complex operator/(double lhs, const Complex& rhs)
{
    const double denominator{((rhs.m_real * rhs.m_real) +
                              (rhs.m_imag * rhs.m_imag))};

    if (denominator == 0.0)
    {
        throw std::domain_error("Division by zero complex number");
    }

    return Complex{((lhs * rhs.m_real) / denominator),
                   ((-lhs * rhs.m_imag) / denominator)};
}

} // namespace complex_numbers
