#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0);

    // Accessors
    double real() const;
    double imag() const;

    // Basic arithmetic
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Unary negation
    Complex operator-() const;

    // Compound assignment (return *this by reference to allow chaining)
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator*=(double num);
    Complex& operator/=(const Complex& other);

    // Scalar multiplication
    Complex operator*(double num) const;
    Complex operator+(double num) const;
    Complex operator-(double num) const;
    Complex operator/(double num) const;
    
    // Comparison
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    // Conjugate, absolute value and exponent
    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double real_;
    double imag_;
};

 // Non-member scalar multiplication
Complex operator*(double num, const Complex& other);
Complex operator+(double num, const Complex& other);
Complex operator-(double num, const Complex& other);
Complex operator/(double num, const Complex& other);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
