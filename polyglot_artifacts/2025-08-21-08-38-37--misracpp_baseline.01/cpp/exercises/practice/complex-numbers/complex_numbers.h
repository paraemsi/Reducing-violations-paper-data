#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0);

    double real() const;
    double imag() const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // These friend declarations must be outside the class in the namespace scope.
    // Remove them from here.

    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double re;
    double im;
};

    // Friend declarations for double op Complex
}  // namespace complex_numbers

// Friend function declarations in namespace scope
namespace complex_numbers {
    Complex operator+(double lhs, const Complex& rhs);
    Complex operator-(double lhs, const Complex& rhs);
    Complex operator*(double lhs, const Complex& rhs);
    Complex operator/(double lhs, const Complex& rhs);
}

#endif  // COMPLEX_NUMBERS_H
