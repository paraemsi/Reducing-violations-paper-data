#include "complex_numbers.h"

#include <cmath>        // std::exp, std::cos, std::sin
#include <stdexcept>    // std::domain_error

namespace complex_numbers {

Complex add(Complex const& lhs, Complex const& rhs) noexcept
{
    return Complex{(lhs.real_ + rhs.real_), (lhs.imag_ + rhs.imag_)};
}

Complex subtract(Complex const& lhs, Complex const& rhs) noexcept
{
    return Complex{(lhs.real_ - rhs.real_), (lhs.imag_ - rhs.imag_)};
}

Complex multiply(Complex const& lhs, Complex const& rhs) noexcept
{
    return Complex{
        ((lhs.real_ * rhs.real_) - (lhs.imag_ * rhs.imag_)),
        ((lhs.imag_ * rhs.real_) + (lhs.real_ * rhs.imag_))};
}

Complex divide(Complex const& lhs, Complex const& rhs)
{
    const double denom{(rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_)};
    if (denom == 0.0)
    {
        throw std::domain_error("Division by zero complex number");
    }

    return Complex{
        (((lhs.real_ * rhs.real_) + (lhs.imag_ * rhs.imag_)) / denom),
        (((lhs.imag_ * rhs.real_) - (lhs.real_ * rhs.imag_)) / denom)};
}

Complex conjugate(Complex const& value) noexcept
{
    return Complex{value.real_, -value.imag_};
}

double abs(Complex const& value) noexcept
{
    return std::sqrt((value.real_ * value.real_) + (value.imag_ * value.imag_));
}

Complex exp(Complex const& value) noexcept
{
    /* Euler’s formula: e^(a + i b) = e^a (cos b + i sin b) */
    const double exp_real{std::exp(value.real_)};
    const double cos_imag{std::cos(value.imag_)};
    const double sin_imag{std::sin(value.imag_)};

    return Complex{(exp_real * cos_imag), (exp_real * sin_imag)};
}

}  // namespace complex_numbers
