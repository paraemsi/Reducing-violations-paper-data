#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H
#include <cmath>

// On some platforms <cmath>/<math.h> defines `abs` as a macro, which breaks
// our member function named `abs()`.  Undefine it so the class declaration
// compiles regardless of platform headers.
#if defined(abs)
#undef abs
#endif

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

    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double real_;
    double imag_;
};

// Non-member arithmetic operators with a double left-hand operand
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
