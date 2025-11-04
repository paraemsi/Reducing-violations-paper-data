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
    
    // Friend operators for mixed-type operations
    friend Complex operator+(const Complex& lhs, double rhs);
    friend Complex operator+(double lhs, const Complex& rhs);
    friend Complex operator-(const Complex& lhs, double rhs);
    friend Complex operator-(double lhs, const Complex& rhs);
    friend Complex operator*(const Complex& lhs, double rhs);
    friend Complex operator*(double lhs, const Complex& rhs);
    friend Complex operator/(const Complex& lhs, double rhs);
    friend Complex operator/(double lhs, const Complex& rhs);
};

// Implement these inline
inline Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ + rhs, lhs.imag_);
}

inline Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real_, rhs.imag_);
}

inline Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ - rhs, lhs.imag_);
}

inline Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real_, -rhs.imag_);
}

inline Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ * rhs, lhs.imag_ * rhs);
}

inline Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real_, lhs * rhs.imag_);
}

inline Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ / rhs, lhs.imag_ / rhs);
}

inline Complex operator/(double lhs, const Complex& rhs) {
    // To compute lhs / (a + bi), we can treat lhs as (lhs + 0i)
    // and use the division formula
    double denominator = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
    double real_part = (lhs * rhs.real_) / denominator;
    double imag_part = (-lhs * rhs.imag_) / denominator;
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
