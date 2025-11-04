#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex
{
public:
    /* NOLINTNEXTLINE(hicpp-explicit-conversions) */
    constexpr Complex(double real_val = 0.0, double imag_val = 0.0) noexcept;

    constexpr double real() const noexcept;
    constexpr double imag() const noexcept;

    Complex conj() const noexcept;
    Complex conjugate() const noexcept { return conj(); }
    double abs() const noexcept;
    Complex exp() const noexcept;

    friend Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator/(const Complex& lhs, const Complex& rhs);

    friend Complex operator+(const Complex& lhs, double rhs) noexcept;
    friend Complex operator+(double lhs, const Complex& rhs) noexcept;

    friend Complex operator-(const Complex& lhs, double rhs) noexcept;
    friend Complex operator-(double lhs, const Complex& rhs) noexcept;

    friend Complex operator*(const Complex& lhs, double rhs) noexcept;
    friend Complex operator*(double lhs, const Complex& rhs) noexcept;

    friend Complex operator/(const Complex& lhs, double rhs);
    friend Complex operator/(double lhs, const Complex& rhs);

private:
    double real_;
    double imag_;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
