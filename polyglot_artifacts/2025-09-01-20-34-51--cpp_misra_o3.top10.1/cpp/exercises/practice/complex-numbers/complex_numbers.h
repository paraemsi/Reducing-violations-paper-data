#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex final {
public:
    /* All trivial functions are defined inline to keep them usable in
     * constant-expression contexts while satisfying the One Definition Rule. */
    constexpr Complex(double realVal = 0.0, double imagVal = 0.0) noexcept
        : real_{ realVal }, imag_{ imagVal } {}

    [[nodiscard]] constexpr double real() const noexcept { return real_; }
    [[nodiscard]] constexpr double imag() const noexcept { return imag_; }

    /* Unary operations required by the test-suite */
    [[nodiscard]] constexpr Complex conj() const noexcept {
        return Complex{ real_, -(imag_) };
    }

    [[nodiscard]] double abs() const noexcept {
        return std::sqrt((real_ * real_) + (imag_ * imag_));
    }

    [[nodiscard]] Complex exp() const {
        const double exponent{ std::exp(real_) };
        return Complex{
            (exponent * std::cos(imag_)),
            (exponent * std::sin(imag_))
        };
    }

private:
    double real_{ 0.0 };
    double imag_{ 0.0 };
};

/* Symmetric arithmetic operators implemented as free functions */
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);

/* Additional operations */
[[nodiscard]] Complex conj(const Complex& value) noexcept;
[[nodiscard]] double  abs (const Complex& value) noexcept;
[[nodiscard]] Complex exp (const Complex& value);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
