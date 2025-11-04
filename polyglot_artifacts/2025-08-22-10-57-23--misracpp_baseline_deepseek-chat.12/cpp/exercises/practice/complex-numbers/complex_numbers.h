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
    
    // Friend operators for mixed-type operations
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
        // To divide a double by a complex number, we can use the formula:
        // (a + 0i) / (c + di) = (a*c)/(c^2 + d^2) + (-a*d)/(c^2 + d^2)i
        double denominator = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
        double real_part = (lhs * rhs.real_) / denominator;
        double imag_part = (-lhs * rhs.imag_) / denominator;
        return Complex(real_part, imag_part);
    }
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
