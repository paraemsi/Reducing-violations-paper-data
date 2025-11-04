#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H
#include <cmath>

namespace complex_numbers {

class Complex final
{
public:
    constexpr Complex(double real_val = 0.0, double imag_val = 0.0) noexcept
        : m_real(real_val),
          m_imag(imag_val)
    {
    }

    constexpr double real() const noexcept
    {
        return m_real;
    }

    constexpr double imag() const noexcept
    {
        return m_imag;
    }

    constexpr Complex conjugate() const noexcept
    {
        return Complex(m_real, -m_imag);
    }

    /* Alias required by tests */
    constexpr Complex conj() const noexcept
    {
        return conjugate();
    }

    /* Unary conjugate operator */
    constexpr Complex operator~() const noexcept
    {
        return conjugate();
    }

    double abs() const noexcept
    {
        return std::sqrt((m_real * m_real) + (m_imag * m_imag));
    }

    Complex exp() const noexcept
    {
        const double exp_real { std::exp(m_real) };
        const double cos_imag { std::cos(m_imag) };
        const double sin_imag { std::sin(m_imag) };

        return Complex((exp_real * cos_imag), (exp_real * sin_imag));
    }

    friend constexpr Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
    {
        return Complex((lhs.m_real + rhs.m_real), (lhs.m_imag + rhs.m_imag));
    }

    friend constexpr Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
    {
        return Complex((lhs.m_real - rhs.m_real), (lhs.m_imag - rhs.m_imag));
    }

    friend constexpr Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
    {
        return Complex(((lhs.m_real * rhs.m_real) - (lhs.m_imag * rhs.m_imag)),
                       ((lhs.m_imag * rhs.m_real) + (lhs.m_real * rhs.m_imag)));
    }

    friend Complex operator/(const Complex& lhs, const Complex& rhs) noexcept
    {
        const double denom { (rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag) };
        /* Division by zero produces undefined behaviour; caller responsibility */
        return Complex(((lhs.m_real * rhs.m_real) + (lhs.m_imag * rhs.m_imag)) / denom,
                       ((lhs.m_imag * rhs.m_real) - (lhs.m_real * rhs.m_imag)) / denom);
    }

    /* Scalar ‒ complex operations */
    friend constexpr Complex operator*(const Complex& lhs, double rhs) noexcept
    {
        return Complex((lhs.m_real * rhs), (lhs.m_imag * rhs));
    }

    friend constexpr Complex operator*(double lhs, const Complex& rhs) noexcept
    {
        return Complex((lhs * rhs.m_real), (lhs * rhs.m_imag));
    }

    friend constexpr Complex operator/(const Complex& lhs, double rhs) noexcept
    {
        return Complex((lhs.m_real / rhs), (lhs.m_imag / rhs));
    }

    constexpr bool operator==(const Complex& rhs) const noexcept
    {
        return ((m_real == rhs.m_real) && (m_imag == rhs.m_imag));
    }

    constexpr bool operator!=(const Complex& rhs) const noexcept
    {
        return !((*this) == rhs);
    }

private:
    double m_real;
    double m_imag;
};

/* ---------------------------------------------------------------------------
 * Free-function helpers required by the public test-suite
 * ------------------------------------------------------------------------ */
inline double abs(const Complex& z) noexcept
{
    return z.abs();
}

inline constexpr Complex conj(const Complex& z) noexcept
{
    return z.conjugate();
}

inline Complex exp(const Complex& z) noexcept
{
    return z.exp();
}

/* Scalar left-hand division :  double / Complex --------------------------- */
inline Complex operator/(double lhs, const Complex& rhs) noexcept
{
    const double denom { (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()) };
    /* Division by zero yields undefined behaviour – caller responsibility */
    return Complex((lhs * rhs.real()) / denom,
                   (-lhs * rhs.imag()) / denom);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
