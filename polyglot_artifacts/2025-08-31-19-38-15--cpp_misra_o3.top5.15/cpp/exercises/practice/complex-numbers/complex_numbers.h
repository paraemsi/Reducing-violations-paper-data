#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

class Complex
{
public:
    /* Constructor */
    constexpr Complex(double realVal = 0.0, double imagVal = 0.0) noexcept
        : m_real(realVal),
          m_imag(imagVal)
    {
    }

    /* Observers */
    [[nodiscard]] double real() const noexcept
    {
        return m_real;
    }

    [[nodiscard]] double imag() const noexcept
    {
        return m_imag;
    }

    /* Basic compound assignment operators */
    Complex& operator+=(const Complex& rhs) noexcept
    {
        m_real += rhs.m_real;
        m_imag += rhs.m_imag;
        return *this;
    }

    Complex& operator-=(const Complex& rhs) noexcept
    {
        m_real -= rhs.m_real;
        m_imag -= rhs.m_imag;
        return *this;
    }

    Complex& operator*=(const Complex& rhs) noexcept
    {
        const double newReal = ((m_real * rhs.m_real) - (m_imag * rhs.m_imag));
        const double newImag = ((m_imag * rhs.m_real) + (m_real * rhs.m_imag));
        m_real = newReal;
        m_imag = newImag;
        return *this;
    }

    Complex& operator/=(const Complex& rhs);

    /* Const member arithmetic operators */
    [[nodiscard]] Complex operator+(const Complex& rhs) const noexcept
    {
        Complex result(*this);
        result += rhs;
        return result;
    }

    [[nodiscard]] Complex operator-(const Complex& rhs) const noexcept
    {
        Complex result(*this);
        result -= rhs;
        return result;
    }

    [[nodiscard]] Complex operator*(const Complex& rhs) const noexcept
    {
        Complex result(*this);
        result *= rhs;
        return result;
    }

    [[nodiscard]] Complex operator/(const Complex& rhs) const
    {
        Complex result(*this);
        result /= rhs;
        return result;
    }

    /* Other operations */
    [[nodiscard]] Complex conj() const noexcept
    {
        return Complex(m_real, -m_imag);
    }

    /* Exponential (member) */
    [[nodiscard]] Complex exp() const
    {
        const double expReal = std::exp(m_real);
        const double realPart = expReal * std::cos(m_imag);
        const double imagPart = expReal * std::sin(m_imag);
        return Complex(realPart, imagPart);
    }

    [[nodiscard]] double abs() const noexcept
    {
        return std::sqrt((m_real * m_real) + (m_imag * m_imag));
    }

private:
    double m_real;
    double m_imag;
};

/* Scalar non-member operators (double lhs) */
[[nodiscard]] Complex operator+(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(double lhs, const Complex& rhs);

/* Scalar non-member operators (double rhs) */
[[nodiscard]] Complex operator+(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, double rhs);

/* Conjugate and absolute value */
[[nodiscard]] Complex conj(const Complex& z) noexcept;
[[nodiscard]] double abs(const Complex& z) noexcept;

/* Exponential function */
[[nodiscard]] Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
