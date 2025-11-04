#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>   // fixed-width integer types per MISRA

namespace complex_numbers {

class Complex {
public:
    explicit constexpr Complex(double real_val = 0.0,
                               double imag_val = 0.0) noexcept
        : m_real(real_val),
          m_imag(imag_val) {}

    [[nodiscard]] constexpr double real() const noexcept { return m_real; }
    [[nodiscard]] constexpr double imag() const noexcept { return m_imag; }

    [[nodiscard]] Complex conj() const noexcept;
    [[nodiscard]] double   abs()  const noexcept;
    [[nodiscard]] Complex  exp()  const noexcept;

private:
    double m_real;
    double m_imag;
};

// Symmetric operators implemented as non-member functions
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);
[[nodiscard]] Complex operator+(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator+(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator-(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator*(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, double rhs);
[[nodiscard]] Complex operator/(double lhs, const Complex& rhs);

// Utility free functions
[[nodiscard]] Complex conj(const Complex& z) noexcept;
[[nodiscard]] double  abs(const Complex& z) noexcept;
[[nodiscard]] Complex exp(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
