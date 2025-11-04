#include "complex_numbers.h"

#include <cmath>        // std::sqrt, std::cos, std::sin, std::exp

namespace complex_numbers {

/* ==== Constructors ====================================================== */
Complex::Complex(double real_part, double imag_part) noexcept
    : real_value_{real_part},
      imag_value_{imag_part}
{
}

/* ==== Accessors ========================================================= */
double Complex::real() const noexcept
{
    return real_value_;
}

double Complex::imag() const noexcept
{
    return imag_value_;
}

/* ==== Arithmetic operators ============================================= */
Complex Complex::operator+(const Complex& other) const noexcept
{
    return Complex{ (real_value_ + other.real_value_), (imag_value_ + other.imag_value_) };
}

Complex Complex::operator-(const Complex& other) const noexcept
{
    return Complex{ (real_value_ - other.real_value_), (imag_value_ - other.imag_value_) };
}

Complex Complex::operator*(const Complex& other) const noexcept
{
    const double real_result = ( (real_value_ * other.real_value_) - (imag_value_ * other.imag_value_) );
    const double imag_result = ( (imag_value_ * other.real_value_) + (real_value_ * other.imag_value_) );
    return Complex{ real_result, imag_result };
}

/* ==== Scalar arithmetic with real numbers ============================== */
Complex Complex::operator+(double value) const noexcept
{
    return Complex{ (real_value_ + value), imag_value_ };
}

Complex Complex::operator-(double value) const noexcept
{
    return Complex{ (real_value_ - value), imag_value_ };
}

Complex Complex::operator*(double value) const noexcept
{
    return Complex{ (real_value_ * value), (imag_value_ * value) };
}

Complex Complex::operator/(double value) const
{
    /* Division-by-zero follows IEEE-754 rules for doubles. */
    return Complex{ (real_value_ / value), (imag_value_ / value) };
}

Complex Complex::operator/(const Complex& other) const
{
    const double denominator =
        ( (other.real_value_ * other.real_value_) + (other.imag_value_ * other.imag_value_) );

    /* Division-by-zero protection is delegated to the platform’s floating-point rules
       (will yield ±inf / NaN as per IEEE-754) to keep this function noexcept. */

    const double real_result =
        ( ( (real_value_ * other.real_value_) + (imag_value_ * other.imag_value_) ) / denominator );
    const double imag_result =
        ( ( (imag_value_ * other.real_value_) - (real_value_ * other.imag_value_) ) / denominator );

    return Complex{ real_result, imag_result };
}

/* ==== Other operations ================================================== */
Complex Complex::conj() const noexcept
{
    return Complex{ real_value_, (-imag_value_) };
}

double Complex::abs() const noexcept
{
    return std::sqrt( (real_value_ * real_value_) + (imag_value_ * imag_value_) );
}

Complex Complex::exp() const
{
    const double exp_real = std::exp(real_value_);
    const double real_result = exp_real * std::cos(imag_value_);
    const double imag_result = exp_real * std::sin(imag_value_);
    return Complex{ real_result, imag_result };
}

}  // namespace complex_numbers
