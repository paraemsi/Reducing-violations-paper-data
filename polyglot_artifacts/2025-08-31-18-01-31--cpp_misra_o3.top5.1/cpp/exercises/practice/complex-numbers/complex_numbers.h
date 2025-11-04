#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

struct Complex final
{
private:
    double real_;
    double imag_;

public:
    constexpr Complex(double real_val = 0.0, double imag_val = 0.0) noexcept
        : real_(real_val), imag_(imag_val) {}

    constexpr double real() const noexcept { return real_; }
    constexpr double imag() const noexcept { return imag_; }

    Complex conj() const noexcept { return conjugate(); }
    Complex exp() const { return complex_numbers::exp(*this); }

    Complex conjugate() const noexcept;
    double abs() const noexcept;

    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const;
};

// Non-member utility functions
Complex conj(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;
Complex exp(const Complex& z);

Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs);

Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
