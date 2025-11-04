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
    { }

    [[nodiscard]] double real() const noexcept;
    [[nodiscard]] double imag() const noexcept;

    /* Alias helpers matching test expectations */
    [[nodiscard]] Complex conj() const noexcept;     /* NOLINT(readability-identifier-naming) */
    [[nodiscard]] Complex exp() const;               /* NOLINT(readability-identifier-naming) */

    Complex& operator+=(const Complex& other) noexcept;
    Complex& operator-=(const Complex& other) noexcept;
    Complex& operator*=(const Complex& other) noexcept;
    Complex& operator/=(const Complex& other);

    [[nodiscard]] Complex operator+(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator-(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator*(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator/(const Complex& other) const;

    [[nodiscard]] Complex conjugate() const noexcept;
    [[nodiscard]] double abs() const noexcept;

private:
    double m_real {};
    double m_imag {};
};

[[nodiscard]] Complex exp(const Complex& z);
[[nodiscard]] Complex conjugate(const Complex& z) noexcept;
[[nodiscard]] Complex conj(const Complex& z) noexcept;   /* NOLINT(readability-identifier-naming) */
[[nodiscard]] double abs(const Complex& z) noexcept;

/* Operators with scalar left-hand operand */
[[nodiscard]] Complex operator+(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
