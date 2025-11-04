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

    // Operations with a real scalar
    Complex operator+(double rhs) const;
    Complex operator-(double rhs) const;
    Complex operator*(double rhs) const;
    Complex operator/(double rhs) const;

    // Comparison
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    // Allow scalar on the left-hand side
    friend Complex operator+(double lhs, const Complex& rhs);
    friend Complex operator-(double lhs, const Complex& rhs);
    friend Complex operator*(double lhs, const Complex& rhs);
    friend Complex operator/(double lhs, const Complex& rhs);

    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double real_;
    double imag_;
};


Complex conj(const Complex& z);
double abs(const Complex& z);
Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
