#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0.0, double i = 0.0) noexcept;

    // Addition
    Complex operator+(const Complex& other) const noexcept;

    // Subtraction
    Complex operator-(const Complex& other) const noexcept;

    // Multiplication
    Complex operator*(const Complex& other) const noexcept;

    // Division
    Complex operator/(const Complex& other) const noexcept;

    // Conjugate
    Complex conjugate() const noexcept;

    // Also provide conj() for test compatibility
    Complex conj() const noexcept;

    // Absolute value (modulus)
    double abs() const noexcept;

    // Exponential
    Complex exp() const noexcept;
};

}  // namespace complex_numbers

namespace complex_numbers {
    Complex operator+(double lhs, const Complex& rhs) noexcept;
    Complex operator-(double lhs, const Complex& rhs) noexcept;
    Complex operator*(double lhs, const Complex& rhs) noexcept;
    Complex operator/(double lhs, const Complex& rhs) noexcept;
}

#endif  // COMPLEX_NUMBERS_H
