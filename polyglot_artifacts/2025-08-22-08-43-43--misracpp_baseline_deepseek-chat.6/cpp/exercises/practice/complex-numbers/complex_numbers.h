#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
private:
    double real_;
    double imag_;
public:
    Complex(double real, double imag) : real_(real), imag_(imag) {}
    Complex(double real) : real_(real), imag_(0.0) {}
    double real() const { return real_; }
    double imag() const { return imag_; }
    double abs() const;
    Complex conj() const;
    Complex exp() const;
    
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    // Friend declarations for operations with doubles on the left
    friend Complex operator+(double lhs, const Complex& rhs);
    friend Complex operator-(double lhs, const Complex& rhs);
    friend Complex operator*(double lhs, const Complex& rhs);
    friend Complex operator/(double lhs, const Complex& rhs);
};

// Implement the operators inline
inline Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

inline Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

inline Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

inline Complex operator/(double lhs, const Complex& rhs) {
    double denominator = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return Complex((lhs * rhs.real()) / denominator, 
                  (-lhs * rhs.imag()) / denominator);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
