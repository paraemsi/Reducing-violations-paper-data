#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

struct Complex final
{
    double real_;
    double imag_;

    constexpr Complex(double r = 0.0, double i = 0.0) noexcept
        : real_(r), imag_(i) {}

    constexpr Complex conjugate() const noexcept
    {
        return Complex(real_, -imag_);
    }

    double abs() const noexcept
    {
        return std::sqrt((real_ * real_) + (imag_ * imag_));
    }

    /* Accessor functions */
    constexpr double real() const noexcept { return real_; }
    constexpr double imag() const noexcept { return imag_; }

    /* Functions expected by tests */
    constexpr Complex conj() const noexcept { return Complex(real_, -imag_); }
    Complex exp() const noexcept { return complex_numbers::exp(*this); }

    friend Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator/(const Complex& lhs, const Complex& rhs);

    /* Equality operators */
    friend bool operator==(const Complex& lhs, const Complex& rhs) noexcept;
    friend bool operator!=(const Complex& lhs, const Complex& rhs) noexcept;
};

Complex exp(const Complex& z) noexcept;
Complex conjugate(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;

Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs);
Complex operator/(double lhs, const Complex& rhs);

bool operator==(const Complex& lhs, const Complex& rhs) noexcept;
bool operator!=(const Complex& lhs, const Complex& rhs) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
