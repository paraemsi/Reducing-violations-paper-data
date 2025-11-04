#include "complex_numbers.h"
#include <limits>

namespace complex_numbers {

/* Addition */
Complex Complex::operator+(const Complex& rhs) const noexcept
{
    return Complex((real_ + rhs.real_), (imag_ + rhs.imag_));
}

/* Subtraction */
Complex Complex::operator-(const Complex& rhs) const noexcept
{
    return Complex((real_ - rhs.real_), (imag_ - rhs.imag_));
}

/* Multiplication */
Complex Complex::operator*(const Complex& rhs) const noexcept
{
    const double real_part = ((real_ * rhs.real_) - (imag_ * rhs.imag_));
    const double imag_part = ((imag_ * rhs.real_) + (real_ * rhs.imag_));
    return Complex(real_part, imag_part);
}

/* Division */
Complex Complex::operator/(const Complex& rhs) const
{
    const double denominator =
        ((rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_));

    /* Guard against division by zero */
    if (denominator == 0.0)
    {
        return Complex(std::numeric_limits<double>::quiet_NaN(),
                       std::numeric_limits<double>::quiet_NaN());
    }

    const double real_part =
        (((real_ * rhs.real_) + (imag_ * rhs.imag_)) / denominator);
    const double imag_part =
        (((imag_ * rhs.real_) - (real_ * rhs.imag_)) / denominator);

    return Complex(real_part, imag_part);
}

/* Conjugate */
Complex Complex::conjugate(void) const noexcept
{
    return Complex(real_, (-imag_));
}

/* Alias: conj */
Complex Complex::conj(void) const noexcept
{
    return this->conjugate();
}

/* Absolute value (magnitude) */
double Complex::abs(void) const noexcept
{
    return std::sqrt((real_ * real_) + (imag_ * imag_));
}

/* Exponential function */
Complex Complex::exp(void) const
{
    const double exponent = std::exp(real_);
    const double real_part = (exponent * std::cos(imag_));
    const double imag_part = (exponent * std::sin(imag_));
    return Complex(real_part, imag_part);
}

/* Non-member operators with double lhs */
Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs - rhs.real()), (-rhs.imag()));
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs)
{
    const double denominator =
        ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));

    if (denominator == 0.0)
    {
        return Complex(std::numeric_limits<double>::quiet_NaN(),
                       std::numeric_limits<double>::quiet_NaN());
    }

    const double real_part = ((lhs * rhs.real()) / denominator);
    const double imag_part = ((-lhs * rhs.imag()) / denominator);

    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
