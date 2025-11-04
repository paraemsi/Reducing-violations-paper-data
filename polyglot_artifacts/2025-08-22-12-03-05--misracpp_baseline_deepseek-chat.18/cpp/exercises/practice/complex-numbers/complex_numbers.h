#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
private:
    double real_;
    double imag_;
public:
    Complex(double real, double imag);
    double real() const;
    double imag() const;
    double abs() const;
    Complex conj() const;
    Complex exp() const;
    
    // Overload operators
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    // Friend functions for mixed-type operations
    friend Complex operator+(const Complex& lhs, double rhs);
    friend Complex operator+(double lhs, const Complex& rhs);
    friend Complex operator-(const Complex& lhs, double rhs);
    friend Complex operator-(double lhs, const Complex& rhs);
    friend Complex operator*(const Complex& lhs, double rhs);
    friend Complex operator*(double lhs, const Complex& rhs);
    friend Complex operator/(const Complex& lhs, double rhs);
    friend Complex operator/(double lhs, const Complex& rhs);
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
