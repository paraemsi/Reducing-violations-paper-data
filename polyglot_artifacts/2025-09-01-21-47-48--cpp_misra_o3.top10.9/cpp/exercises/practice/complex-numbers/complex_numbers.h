#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>

namespace complex_numbers {

class Complex
{
public:
    constexpr Complex(double realVal = 0.0, double imagVal = 0.0) noexcept
        : m_real(realVal),
          m_imag(imagVal)
    {
    }

    [[nodiscard]] double real() const noexcept;
    [[nodiscard]] double imag() const noexcept;

    [[nodiscard]] Complex conj() const noexcept;
    [[nodiscard]] double abs() const noexcept;
    [[nodiscard]] Complex exp() const;

    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator/=(const Complex& rhs);

private:
    double m_real;
    double m_imag;
};

/* Symmetrical operators implemented as non-member functions */
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
