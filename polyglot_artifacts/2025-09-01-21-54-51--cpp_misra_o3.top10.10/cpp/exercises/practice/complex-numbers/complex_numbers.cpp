#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

namespace complex_numbers {

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real_ + rhs.real_), (lhs.imag_ + rhs.imag_));
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real_ - rhs.real_), (lhs.imag_ - rhs.imag_));
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    const double real_part = ((lhs.real_ * rhs.real_) - (lhs.imag_ * rhs.imag_));
    const double imag_part = ((lhs.imag_ * rhs.real_) + (lhs.real_ * rhs.imag_));
    return Complex(real_part, imag_part);
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    const double denom = ((rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_));
    if (denom == 0.0)
    {
        throw std::domain_error("Division by zero in complex division");
    }
    const double real_part = (((lhs.real_ * rhs.real_) + (lhs.imag_ * rhs.imag_)) / denom);
    const double imag_part = (((lhs.imag_ * rhs.real_) - (lhs.real_ * rhs.imag_)) / denom);
    return Complex(real_part, imag_part);
}

Complex exp(const Complex& z) noexcept
{
    const double magnitude = std::exp(z.real());
    const double real_part = (magnitude * std::cos(z.imag()));
    const double imag_part = (magnitude * std::sin(z.imag()));
    return Complex(real_part, imag_part);
}

Complex conjugate(const Complex& z) noexcept
{
    return z.conjugate();
}

double abs(const Complex& z) noexcept
{
    return z.abs();
}

Complex operator+(const Complex& lhs, double rhs) noexcept
{
    const Complex rhs_complex(rhs, 0.0);
    return lhs + rhs_complex;
}

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    const Complex lhs_complex(lhs, 0.0);
    return lhs_complex + rhs;
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    const Complex rhs_complex(rhs, 0.0);
    return lhs - rhs_complex;
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    const Complex lhs_complex(lhs, 0.0);
    return lhs_complex - rhs;
}

Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real_ * rhs), (lhs.imag_ * rhs));
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real_), (lhs * rhs.imag_));
}

Complex operator/(const Complex& lhs, double rhs)
{
    if (rhs == 0.0)
    {
        throw std::domain_error("Division by zero in complex / scalar");
    }
    return Complex((lhs.real_ / rhs), (lhs.imag_ / rhs));
}

Complex operator/(double lhs, const Complex& rhs)
{
    const Complex lhs_complex(lhs, 0.0);
    return lhs_complex / rhs;
}

bool operator==(const Complex& lhs, const Complex& rhs) noexcept
{
    return ((lhs.real_ == rhs.real_) && (lhs.imag_ == rhs.imag_));
}

bool operator!=(const Complex& lhs, const Complex& rhs) noexcept
{
    return !(lhs == rhs);
}

}  // namespace complex_numbers
