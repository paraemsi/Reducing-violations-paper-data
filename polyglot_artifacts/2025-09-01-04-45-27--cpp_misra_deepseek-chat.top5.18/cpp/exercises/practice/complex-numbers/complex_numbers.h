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
    
    // Arithmetic operations
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    // Friend functions for operations with doubles
    friend Complex operator+(const Complex& lhs, double rhs);
    friend Complex operator+(double lhs, const Complex& rhs);
    friend Complex operator-(const Complex& lhs, double rhs);
    friend Complex operator-(double lhs, const Complex& rhs);
    friend Complex operator*(const Complex& lhs, double rhs);
    friend Complex operator*(double lhs, const Complex& rhs);
    friend Complex operator/(const Complex& lhs, double rhs);
    friend Complex operator/(double lhs, const Complex& rhs);
    
    // Other operations
    Complex conj() const;
    double abs() const;
    Complex exp() const;
};

// Define the non-member operators in the namespace (inline to avoid multiple definition errors)
inline Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real() + rhs, lhs.imag());
}

inline Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

inline Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real() - rhs, lhs.imag());
}

inline Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

inline Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real() * rhs, lhs.imag() * rhs);
}

inline Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

inline Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real() / rhs, lhs.imag() / rhs);
}

inline Complex operator/(double lhs, const Complex& rhs) {
    // To compute lhs / (a + bi), we can treat lhs as (lhs + 0i)
    // and use the division formula
    double denominator = (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag());
    double real_part = (lhs * rhs.real()) / denominator;
    double imag_part = (-lhs * rhs.imag()) / denominator;
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
