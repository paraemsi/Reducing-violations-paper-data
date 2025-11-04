#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

struct Complex final
{
    constexpr Complex() noexcept : m_real{0.0}, m_imag{0.0} {}

    constexpr explicit Complex(double realPart,
                               double imagPart = 0.0) noexcept
        : m_real{realPart}, m_imag{imagPart}
    {
    }

    double m_real; /* NOLINT(misc-non-private-member-variables-in-classes) */
    double m_imag; /* NOLINT(misc-non-private-member-variables-in-classes) */

    /* accessors */
    [[nodiscard]] constexpr double real() const noexcept
    {
        return m_real;
    }

    [[nodiscard]] constexpr double imag() const noexcept
    {
        return m_imag;
    }

    /* additional member operations */
    [[nodiscard]] Complex conj() const noexcept;
    [[nodiscard]] double  abs()  const noexcept;
    [[nodiscard]] Complex exp()  const;

    /* unary operators */
    [[nodiscard]] constexpr Complex operator+() const noexcept
    {
        return *this;
    }

    [[nodiscard]] constexpr Complex operator-() const noexcept
    {
        return Complex{(-m_real), (-m_imag)};
    }
};

/* symmetrical binary operators implemented as free functions */
[[nodiscard]] Complex operator+(const Complex& lhs,
                                const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs,
                                const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs,
                                const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs,
                                const Complex& rhs);
[[nodiscard]] bool    operator==(const Complex& lhs,
                                 const Complex& rhs) noexcept;
[[nodiscard]] bool    operator!=(const Complex& lhs,
                                 const Complex& rhs) noexcept;

/* arithmetic with scalar (double) */
[[nodiscard]] Complex operator+(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator+(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator-(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator*(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, double rhs);
[[nodiscard]] Complex operator/(double lhs, const Complex& rhs);

/* additional operations */
[[nodiscard]] Complex   conjugate(const Complex& value) noexcept;
[[nodiscard]] double    abs(const Complex& value) noexcept;
[[nodiscard]] Complex   exp(const Complex& value);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
