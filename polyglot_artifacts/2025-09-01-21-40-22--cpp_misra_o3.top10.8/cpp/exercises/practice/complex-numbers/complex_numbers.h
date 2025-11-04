#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

/*
 * A lightweight complex-number type that supports the basic arithmetic
 * operations together with conjugate, absolute value, and exponent.
 *
 * Notes on MISRA-C++ compliance:
 *  – Only fixed-width integer types from <cstdint> are included; none are
 *    used in the public interface – all numerics are double-precision
 *    floating point.
 *  – Binary arithmetic operators are implemented as non-member functions
 *    to keep them symmetrical (see rule).
 *  – Parentheses are used liberally to make operator precedence explicit.
 */
class Complex final
{
public:
    constexpr Complex(double real_val = 0.0, double imag_val = 0.0) noexcept
        : m_real(real_val), m_imag(imag_val)
    {
    }

    [[nodiscard]] constexpr double real() const noexcept
    {
        return m_real;
    }

    [[nodiscard]] constexpr double imag() const noexcept
    {
        return m_imag;
    }

    [[nodiscard]] constexpr Complex conjugate() const noexcept
    {
        return Complex(m_real, (-m_imag));
    }

    /*  Alias required by the public Exercism interface ------------------ */
    [[nodiscard]] constexpr Complex conj() const noexcept
    {
        return conjugate();
    }

    [[nodiscard]] double abs() const noexcept
    {
        return std::sqrt((m_real * m_real) + (m_imag * m_imag));
    }

    [[nodiscard]] Complex exp() const noexcept
    {
        const double exp_real { std::exp(m_real) };
        return Complex((exp_real * std::cos(m_imag)),
                       (exp_real * std::sin(m_imag)));
    }

private:
    double m_real;
    double m_imag;
};

/* Non-member, symmetrical operators ------------------------------------ */

[[nodiscard]] inline Complex operator+(const Complex& lhs,
                                       const Complex& rhs) noexcept
{
    return Complex((lhs.real() + rhs.real()),
                   (lhs.imag() + rhs.imag()));
}

[[nodiscard]] inline Complex operator-(const Complex& lhs,
                                       const Complex& rhs) noexcept
{
    return Complex((lhs.real() - rhs.real()),
                   (lhs.imag() - rhs.imag()));
}

[[nodiscard]] inline Complex operator*(const Complex& lhs,
                                       const Complex& rhs) noexcept
{
    return Complex(((lhs.real() * rhs.real()) -
                    (lhs.imag() * rhs.imag())),
                   ((lhs.imag() * rhs.real()) +
                    (lhs.real() * rhs.imag())));
}

[[nodiscard]] inline Complex operator/(const Complex& lhs,
                                       const Complex& rhs)
{
    const double denom {(rhs.real() * rhs.real()) +
                        (rhs.imag() * rhs.imag())};

    /* Guard against division by zero – behaviour is undefined, propagate
     * infinity / NaN as per IEEE-754 via the hardware division.
     */
    return Complex(((lhs.real() * rhs.real()) +
                    (lhs.imag() * rhs.imag())) / denom,
                   ((lhs.imag() * rhs.real()) -
                    (lhs.real() * rhs.imag())) / denom);
}

/* Additional free-functions ------------------------------------------------ */

/*  Conjugate of a complex number */
[[nodiscard]] inline Complex conj(const Complex& value) noexcept
{
    return value.conjugate();
}

/*  Absolute value (magnitude) */
[[nodiscard]] inline double abs(const Complex& value) noexcept
{
    return value.abs();
}

/*  Exponential of a complex number */
[[nodiscard]] inline Complex exp(const Complex& value) noexcept
{
    return value.exp();
}

/* Additional mixed-type operators --------------------------------------- */

/*  Multiply Complex by scalar (Complex * double) */
[[nodiscard]] inline Complex operator*(const Complex& lhs,
                                       double rhs) noexcept
{
    return Complex((lhs.real() * rhs),
                   (lhs.imag() * rhs));
}

/*  Multiply Complex by scalar (double * Complex) */
[[nodiscard]] inline Complex operator*(double lhs,
                                       const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real()),
                   (lhs * rhs.imag()));
}

/*  Divide Complex by scalar (Complex / double) */
[[nodiscard]] inline Complex operator/(const Complex& lhs,
                                       double rhs)
{
    return Complex((lhs.real() / rhs),
                   (lhs.imag() / rhs));
}

/*  Equality operators --------------------------------------------------- */
[[nodiscard]] inline bool operator==(const Complex& lhs,
                                     const Complex& rhs) noexcept
{
    return ((lhs.real() == rhs.real()) &&
            (lhs.imag() == rhs.imag()));
}

[[nodiscard]] inline bool operator!=(const Complex& lhs,
                                     const Complex& rhs) noexcept
{
    return (!(lhs == rhs));
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
