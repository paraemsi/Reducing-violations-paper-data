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
    friend Complex operator+(const Complex& lhs, double rhs) {
        return Complex(lhs.real_ + rhs, lhs.imag_);
    }
    friend Complex operator+(double lhs, const Complex& rhs) {
        return Complex(lhs + rhs.real_, rhs.imag_);
    }
    friend Complex operator-(const Complex& lhs, double rhs) {
        return Complex(lhs.real_ - rhs, lhs.imag_);
    }
    friend Complex operator-(double lhs, const Complex& rhs) {
        return Complex(lhs - rhs.real_, -rhs.imag_);
    }
    friend Complex operator*(const Complex& lhs, double rhs) {
        return Complex(lhs.real_ * rhs, lhs.imag_ * rhs);
    }
    friend Complex operator*(double lhs, const Complex& rhs) {
        return Complex(lhs * rhs.real_, lhs * rhs.imag_);
    }
    friend Complex operator/(const Complex& lhs, double rhs) {
        return Complex(lhs.real_ / rhs, lhs.imag_ / rhs);
    }
    friend Complex operator/(double lhs, const Complex& rhs) {
        // To divide a real number by a complex number, we can treat the real number as a complex number
        // and use the existing division implementation
        return Complex(lhs, 0.0) / rhs;
    }
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
