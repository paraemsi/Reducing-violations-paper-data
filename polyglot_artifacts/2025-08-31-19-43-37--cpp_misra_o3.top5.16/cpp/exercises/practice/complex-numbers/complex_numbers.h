#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

class Complex
{
public:
    /* Constructor */
    constexpr Complex(double real_val = 0.0, double imag_val = 0.0) noexcept
        : real_{ real_val }, imag_{ imag_val } {}

    /* Accessors */
    constexpr double real(void) const noexcept { return real_; }
    constexpr double imag(void) const noexcept { return imag_; }

    /* Binary arithmetic operators */
    [[nodiscard]] Complex operator+(const Complex& rhs) const noexcept;
    [[nodiscard]] Complex operator-(const Complex& rhs) const noexcept;
    [[nodiscard]] Complex operator*(const Complex& rhs) const noexcept;
    [[nodiscard]] Complex operator/(const Complex& rhs) const;

    /* Unary operations */
    [[nodiscard]] Complex conjugate(void) const noexcept;
    [[nodiscard]] Complex conj(void) const noexcept;
    [[nodiscard]] double abs(void) const noexcept;
    [[nodiscard]] Complex exp(void) const;

private:
    double real_;
    double imag_;
};

[[nodiscard]] Complex operator+(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
