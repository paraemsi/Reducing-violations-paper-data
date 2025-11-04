#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    // Constructs a complex number with given real and imaginary parts.
    // Defaults to 0 + 0i when no arguments are provided.
    Complex(double real = 0.0, double imag = 0.0);

    // Accessors
    double real() const;
    double imag() const;

    // Basic arithmetic operators
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Operations with real numbers
    Complex operator+(double value) const;
    Complex operator-(double value) const;
    Complex operator*(double value) const;
    Complex operator/(double value) const;

    // Unary operators
    Complex operator+() const;
    Complex operator-() const;

    // Conjugate of the complex number
    Complex conj() const;

    // Absolute value (magnitude)
    double abs() const;

    // Exponential of a complex number
    Complex exp() const;

private:
    double real_;
    double imag_;
};

// Non-member arithmetic with a real number on the left-hand side
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

// Non-member absolute value to enable argument-dependent lookup
double abs(const Complex& c);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
