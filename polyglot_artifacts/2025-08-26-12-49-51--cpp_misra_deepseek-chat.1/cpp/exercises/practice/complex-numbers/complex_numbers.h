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
    
    // Operators
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
};

// Non-member operators for mixed-type operations
inline Complex operator+(const Complex& lhs, double rhs) {
    return Complex((lhs.real() + rhs), lhs.imag());
}

inline Complex operator+(double lhs, const Complex& rhs) {
    return Complex((lhs + rhs.real()), rhs.imag());
}

inline Complex operator-(const Complex& lhs, double rhs) {
    return Complex((lhs.real() - rhs), lhs.imag());
}

inline Complex operator-(double lhs, const Complex& rhs) {
    return Complex((lhs - rhs.real()), (-rhs.imag()));
}

inline Complex operator*(const Complex& lhs, double rhs) {
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

inline Complex operator*(double lhs, const Complex& rhs) {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

inline Complex operator/(const Complex& lhs, double rhs) {
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

inline Complex operator/(double lhs, const Complex& rhs) {
    // To compute lhs / (a + bi), which is the same as lhs * (1/(a + bi))
    // 1/(a + bi) = a/(a^2 + b^2) - b/(a^2 + b^2)i
    double denominator = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    double real_part = (rhs.real() / denominator);
    double imag_part = ((-rhs.imag()) / denominator);
    return Complex((lhs * real_part), (lhs * imag_part));
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
