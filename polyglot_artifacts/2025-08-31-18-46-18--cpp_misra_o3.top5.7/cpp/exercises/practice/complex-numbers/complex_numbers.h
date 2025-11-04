#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : real_{real}, imag_{imag} {}

    double real() const noexcept { return real_; }
    double imag() const noexcept { return imag_; }

    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const;

    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const;

private:
    double real_;
    double imag_;
};

// Non-member arithmetic operators that accept a real scalar on the
// left-hand side and a Complex value on the right-hand side.
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
