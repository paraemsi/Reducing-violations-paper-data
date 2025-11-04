#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace complex_numbers {

class Complex
{
public:
    constexpr Complex() noexcept : m_real(0.0), m_imag(0.0) {}
    constexpr Complex(double realVal, double imagVal) noexcept : m_real(realVal), m_imag(imagVal) {}

    [[nodiscard]] constexpr double real() const noexcept { return m_real; }
    [[nodiscard]] constexpr double imag() const noexcept { return m_imag; }

    [[nodiscard]] Complex operator+(const Complex& rhs) const noexcept;
    [[nodiscard]] Complex operator-(const Complex& rhs) const noexcept;
    [[nodiscard]] Complex operator*(const Complex& rhs) const noexcept;
    [[nodiscard]] Complex operator/(const Complex& rhs) const;
    [[nodiscard]] bool operator==(const Complex& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const Complex& rhs) const noexcept;

    [[nodiscard]] constexpr Complex conjugate() const noexcept;
    [[nodiscard]] double         abs()       const noexcept;

    /* Additional operations required by specification/tests */
    [[nodiscard]] Complex conj() const noexcept;          /* alias for conjugate()            */
    [[nodiscard]] Complex exp() const;                    /* e^(a + i b) as member            */

    [[nodiscard]] constexpr Complex operator*(double scalar) const noexcept;
    [[nodiscard]] constexpr Complex operator+(double scalar) const noexcept;
    [[nodiscard]] constexpr Complex operator-(double scalar) const noexcept;
    [[nodiscard]] Complex operator/(double scalar) const;

    friend Complex operator*(double scalar, const Complex& rhs) noexcept;
    friend Complex operator+(double scalar, const Complex& rhs) noexcept;
    friend Complex operator-(double scalar, const Complex& rhs) noexcept;
    friend Complex operator/(double scalar, const Complex& rhs);

private:
    double m_real;
    double m_imag;
};

[[nodiscard]] Complex exp(const Complex& z);
[[nodiscard]] Complex conjugate(const Complex& z) noexcept;
[[nodiscard]] double abs(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
