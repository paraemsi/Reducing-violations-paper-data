#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

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

    [[nodiscard]] constexpr Complex conj() const noexcept
    {
        return Complex(m_real, -m_imag);
    }
    [[nodiscard]] double              abs()  const noexcept;
    [[nodiscard]] Complex             exp()  const noexcept;

private:
    double m_real;
    double m_imag;
};

/* ----------- non-member symmetrical operators ----------- */
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);

[[nodiscard]] Complex conj(const Complex& value) noexcept;
[[nodiscard]] double  abs(const Complex& value) noexcept;
[[nodiscard]] Complex exp(const Complex& value) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
