#include "complex_numbers.h"
#include <limits>

namespace complex_numbers {

/*-----  Complex member operators  -----*/
bool Complex::operator==(const Complex& other) const noexcept
{
    return ((real() == other.real()) && (imag() == other.imag()));
}

bool Complex::operator!=(const Complex& other) const noexcept
{
    return !(*this == other);
}

/*-----  Helper aliases  -----*/
using fp_t = double;        /*  floating-point alias, explicit for MISRA rules  */

/*-----  Arithmetic  -----*/
Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex{ (lhs.real() + rhs.real()), (lhs.imag() + rhs.imag()) };
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex{ (lhs.real() - rhs.real()), (lhs.imag() - rhs.imag()) };
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    const fp_t real_part = (lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag());
    const fp_t imag_part = (lhs.imag() * rhs.real()) + (lhs.real() * rhs.imag());
    return Complex{ real_part, imag_part };
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    const fp_t denom = (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag());

    /*  Guard against division by zero (undefined); propagate inf  */
    if (denom == 0.0) {
        return Complex{ std::numeric_limits<fp_t>::infinity(),
                        std::numeric_limits<fp_t>::infinity() };
    }

    const fp_t real_part = ((lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag())) / denom;
    const fp_t imag_part = ((lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag())) / denom;
    return Complex{ real_part, imag_part };
}

/*-----  Conjugate  -----*/
Complex conj(const Complex& value) noexcept
{
    return Complex{ value.real(), -value.imag() };
}

/*-----  Absolute value  -----*/
double abs(const Complex& value) noexcept
{
    return std::sqrt((value.real() * value.real()) + (value.imag() * value.imag()));
}

/*-----  Exponential  -----*/
Complex exp(const Complex& value)
{
    const fp_t factor = std::exp(value.real());
    const fp_t cos_b  = std::cos(value.imag());
    const fp_t sin_b  = std::sin(value.imag());
    return Complex{ (factor * cos_b), (factor * sin_b) };
}

/*-----  Member function wrappers  -----*/
double Complex::abs() const noexcept
{
    return complex_numbers::abs(*this);
}

Complex Complex::conj() const noexcept
{
    return complex_numbers::conj(*this);
}

Complex Complex::exp() const
{
    return complex_numbers::exp(*this);
}

/*-----  Complex-scalar arithmetic  -----*/
Complex operator+(const Complex& lhs, double rhs) noexcept
{
    return Complex{ (lhs.real() + rhs), lhs.imag() };
}

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex{ (lhs + rhs.real()), rhs.imag() };
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    return Complex{ (lhs.real() - rhs), lhs.imag() };
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex{ (lhs - rhs.real()), (-rhs.imag()) };
}

Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return Complex{ (lhs.real() * rhs), (lhs.imag() * rhs) };
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex{ (lhs * rhs.real()), (lhs * rhs.imag()) };
}

Complex operator/(const Complex& lhs, double rhs)
{
    if (rhs == 0.0) {
        return Complex{ std::numeric_limits<double>::infinity(),
                        std::numeric_limits<double>::infinity() };
    }
    return Complex{ (lhs.real() / rhs), (lhs.imag() / rhs) };
}

Complex operator/(double lhs, const Complex& rhs)
{
    /*  Treat lhs as complex(lhs, 0)  */
    return Complex(lhs, 0.0) / rhs;
}

}  // namespace complex_numbers
