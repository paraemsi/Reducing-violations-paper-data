#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>

namespace complex_numbers {

class Complex final {
public:
    constexpr Complex(double real_part = 0.0, double imag_part = 0.0) noexcept;

    [[nodiscard]] constexpr double real() const noexcept;
    [[nodiscard]] constexpr double imag() const noexcept;

    [[nodiscard]] Complex operator+(const Complex& rhs) const noexcept;
    [[nodiscard]] Complex operator-(const Complex& rhs) const noexcept;
    [[nodiscard]] Complex operator*(const Complex& rhs) const noexcept;
    [[nodiscard]] Complex operator/(const Complex& rhs) const;

    [[nodiscard]] Complex conj() const noexcept;
    [[nodiscard]] double  abs()  const noexcept;
    [[nodiscard]] Complex exp()  const;

private:
    double m_real{};
    double m_imag{};
};

/* --------------------------------------------------------------------------
 * Inline definitions (required because constexpr implies inline)
 * -------------------------------------------------------------------------- */
inline constexpr Complex::Complex(double real_part, double imag_part) noexcept
    : m_real(real_part), m_imag(imag_part)
{
}

inline constexpr double Complex::real() const noexcept
{
    return m_real;
}

inline constexpr double Complex::imag() const noexcept
{
    return m_imag;
}

/* --------------------------------------------------------------------------
 * Free-function overloads to allow a real left-hand operand
 * -------------------------------------------------------------------------- */
inline Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex(lhs, 0.0) + rhs;
}

inline Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex(lhs, 0.0) - rhs;
}

inline Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex(lhs, 0.0) * rhs;
}

inline Complex operator/(double lhs, const Complex& rhs) noexcept
{
    return Complex(lhs, 0.0) / rhs;
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
