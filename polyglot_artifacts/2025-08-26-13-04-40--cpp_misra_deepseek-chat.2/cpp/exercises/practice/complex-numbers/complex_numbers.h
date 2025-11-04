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
    
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
};

// Addition
inline Complex operator+(const Complex& lhs, double rhs) {
    return lhs.operator+(Complex(rhs, 0.0));
}
inline Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0).operator+(rhs);
}

// Subtraction
inline Complex operator-(const Complex& lhs, double rhs) {
    return lhs.operator-(Complex(rhs, 0.0));
}
inline Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0).operator-(rhs);
}

// Multiplication
inline Complex operator*(const Complex& lhs, double rhs) {
    return lhs.operator*(Complex(rhs, 0.0));
}
inline Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0).operator*(rhs);
}

// Division
inline Complex operator/(const Complex& lhs, double rhs) {
    return lhs.operator/(Complex(rhs, 0.0));
}
inline Complex operator/(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0).operator/(rhs);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
