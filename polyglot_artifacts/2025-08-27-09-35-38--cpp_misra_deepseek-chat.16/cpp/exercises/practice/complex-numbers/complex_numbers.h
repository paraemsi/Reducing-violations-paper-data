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
    
    // Operations
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    // Friend operators for operations with doubles
    friend Complex operator+(const Complex& lhs, double rhs);
    friend Complex operator+(double lhs, const Complex& rhs);
    friend Complex operator-(const Complex& lhs, double rhs);
    friend Complex operator-(double lhs, const Complex& rhs);
    friend Complex operator*(const Complex& lhs, double rhs);
    friend Complex operator*(double lhs, const Complex& rhs);
    friend Complex operator/(const Complex& lhs, double rhs);
    friend Complex operator/(double lhs, const Complex& rhs);
    
    // Other functions
    double abs() const;
    Complex conj() const;
    Complex exp() const;
};

// Implement the operators inline in the header
// Since these are friend functions, they can access private members directly
inline Complex operator+(const Complex& lhs, double rhs) {
    return Complex((lhs.real_ + rhs), lhs.imag_);
}

inline Complex operator+(double lhs, const Complex& rhs) {
    return Complex((lhs + rhs.real_), rhs.imag_);
}

inline Complex operator-(const Complex& lhs, double rhs) {
    return Complex((lhs.real_ - rhs), lhs.imag_);
}

inline Complex operator-(double lhs, const Complex& rhs) {
    return Complex((lhs - rhs.real_), (-rhs.imag_));
}

inline Complex operator*(const Complex& lhs, double rhs) {
    return Complex((lhs.real_ * rhs), (lhs.imag_ * rhs));
}

inline Complex operator*(double lhs, const Complex& rhs) {
    return Complex((lhs * rhs.real_), (lhs * rhs.imag_));
}

inline Complex operator/(const Complex& lhs, double rhs) {
    return Complex((lhs.real_ / rhs), (lhs.imag_ / rhs));
}

inline Complex operator/(double lhs, const Complex& rhs) {
    // To divide a double by a complex number, we can treat the double as a complex number with imaginary part 0
    // and use the existing division formula
    double denominator = (rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_);
    double real_part = (lhs * rhs.real_) / denominator;
    double imag_part = (-lhs * rhs.imag_) / denominator;
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
