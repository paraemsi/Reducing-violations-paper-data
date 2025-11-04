#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <ostream>

namespace complex_numbers {

class Complex {
public:
    // Constructors
    Complex(double real = 0.0, double imag = 0.0);

    // Accessors
    double real() const;
    double imag() const;

    // Complex-Complex arithmetic
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Complex-scalar arithmetic (rhs scalar)
    Complex operator+(double value) const;
    Complex operator-(double value) const;
    Complex operator*(double value) const;
    Complex operator/(double value) const;

    // Unary operations
    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double re_;
    double im_;
};

// Scalar-Complex arithmetic (lhs scalar)
Complex operator+(double value, const Complex& c);
Complex operator-(double value, const Complex& c);
Complex operator*(double value, const Complex& c);
Complex operator/(double value, const Complex& c);

// Optional helper for debugging/printing
std::ostream& operator<<(std::ostream& os, const Complex& c);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
