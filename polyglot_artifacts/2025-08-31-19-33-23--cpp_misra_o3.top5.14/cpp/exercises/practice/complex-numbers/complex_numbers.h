#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

class Complex
{
public:
    /* Constructor */
    constexpr Complex(double real_part, double imag_part) noexcept : m_real(real_part), m_imag(imag_part) {}

    /* Accessors */
    [[nodiscard]] constexpr double real() const noexcept
    {
        return m_real;
    }

    [[nodiscard]] constexpr double imag() const noexcept
    {
        return m_imag;
    }

    /* Arithmetic operators */
    [[nodiscard]] Complex operator+(const Complex& other) const noexcept
    {
        return Complex((m_real + other.m_real), (m_imag + other.m_imag));
    }

    [[nodiscard]] Complex operator-(const Complex& other) const noexcept
    {
        return Complex((m_real - other.m_real), (m_imag - other.m_imag));
    }

    [[nodiscard]] Complex operator*(const Complex& other) const noexcept
    {
        const double real_part = ((m_real * other.m_real) - (m_imag * other.m_imag));
        const double imag_part = ((m_imag * other.m_real) + (m_real * other.m_imag));
        return Complex(real_part, imag_part);
    }

    [[nodiscard]] Complex operator/(const Complex& other) const
    {
        const double denominator = ((other.m_real * other.m_real) + (other.m_imag * other.m_imag));
        const double real_part = (((m_real * other.m_real) + (m_imag * other.m_imag)) / denominator);
        const double imag_part = (((m_imag * other.m_real) - (m_real * other.m_imag)) / denominator);
        return Complex(real_part, imag_part);
    }

    /* Scalar arithmetic with real value on right-hand side */
    [[nodiscard]] Complex operator+(double value) const noexcept
    {
        return Complex((m_real + value), m_imag);
    }

    [[nodiscard]] Complex operator-(double value) const noexcept
    {
        return Complex((m_real - value), m_imag);
    }

    [[nodiscard]] Complex operator*(double value) const noexcept
    {
        return Complex((m_real * value), (m_imag * value));
    }

    [[nodiscard]] Complex operator/(double value) const
    {
        return Complex((m_real / value), (m_imag / value));
    }

    /* Compound assignment operators */
    Complex& operator+=(const Complex& other) noexcept
    {
        m_real += other.m_real;
        m_imag += other.m_imag;
        return *this;
    }

    Complex& operator-=(const Complex& other) noexcept
    {
        m_real -= other.m_real;
        m_imag -= other.m_imag;
        return *this;
    }

    Complex& operator*=(const Complex& other) noexcept
    {
        const double real_part = ((m_real * other.m_real) - (m_imag * other.m_imag));
        const double imag_part = ((m_imag * other.m_real) + (m_real * other.m_imag));
        m_real = real_part;
        m_imag = imag_part;
        return *this;
    }

    Complex& operator/=(const Complex& other)
    {
        const double denominator = ((other.m_real * other.m_real) + (other.m_imag * other.m_imag));
        const double real_part = (((m_real * other.m_real) + (m_imag * other.m_imag)) / denominator);
        const double imag_part = (((m_imag * other.m_real) - (m_real * other.m_imag)) / denominator);
        m_real = real_part;
        m_imag = imag_part;
        return *this;
    }

    /* Equality */
    [[nodiscard]] bool operator==(const Complex& other) const noexcept
    {
        return ((m_real == other.m_real) && (m_imag == other.m_imag));
    }

    /* Conjugate */
    [[nodiscard]] constexpr Complex conj() const noexcept
    {
        return Complex(m_real, (-m_imag));
    }

    /* Magnitude */
    [[nodiscard]] double abs() const noexcept
    {
        return std::sqrt((m_real * m_real) + (m_imag * m_imag));
    }

    /* Exponential */
    [[nodiscard]] Complex exp() const
    {
        const double exp_real = std::exp(m_real);
        return Complex((exp_real * std::cos(m_imag)), (exp_real * std::sin(m_imag)));
    }

private:
    double m_real;
    double m_imag;
};

/* ------------------------------------------------------------------------- */
/*  Free-function wrappers required by the exercise specification.            */
/*  They simply forward to the corresponding member function, allowing the   */
/*  operations to be used either in OO style ( z.conj() ) or functional      */
/*  style ( complex_numbers::conj(z) ).                                      */
/* ------------------------------------------------------------------------- */

[[nodiscard]] inline Complex conj(const Complex& value) noexcept
{
    return value.conj();
}

[[nodiscard]] inline double abs(const Complex& value) noexcept
{
    return value.abs();
}

[[nodiscard]] inline Complex exp(const Complex& value)
{
    return value.exp();
}

/* Overloads to support real value on the left-hand side of the operator */
[[nodiscard]] inline Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs + rhs.real()), rhs.imag());
}

[[nodiscard]] inline Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs - rhs.real()), (-rhs.imag()));
}

[[nodiscard]] inline Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

[[nodiscard]] inline Complex operator/(double lhs, const Complex& rhs)
{
    const double denominator = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    const double real_part = ((lhs * rhs.real()) / denominator);
    const double imag_part = ((-lhs * rhs.imag()) / denominator);
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
