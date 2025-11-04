#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>

namespace complex_numbers {

class Complex final
{
public:
    constexpr Complex(double real_part = 0.0, double imag_part = 0.0) noexcept
        : m_real(real_part), m_imag(imag_part) {}

    constexpr double real() const noexcept { return m_real; }
    constexpr double imag() const noexcept { return m_imag; }

    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator/=(const Complex& rhs);

    [[nodiscard]] Complex conjugate() const noexcept;
    [[nodiscard]] double  abs() const noexcept;

    /* convenience member wrappers expected by tests */
    [[nodiscard]] Complex conj() const noexcept;   /* returns complex conjugate */
    [[nodiscard]] Complex exp()  const;            /* returns e^(this) */

private:
    double m_real;
    double m_imag;
};

/* Symmetrical binary operators implemented as non-member functions */
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);

[[nodiscard]] Complex conj(const Complex& value) noexcept;
[[nodiscard]] Complex conjugate(const Complex& value) noexcept;
[[nodiscard]] double  abs(const Complex& value) noexcept;
[[nodiscard]] Complex exp(const Complex& value);

[[nodiscard]] bool operator==(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] bool operator!=(const Complex& lhs, const Complex& rhs) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
