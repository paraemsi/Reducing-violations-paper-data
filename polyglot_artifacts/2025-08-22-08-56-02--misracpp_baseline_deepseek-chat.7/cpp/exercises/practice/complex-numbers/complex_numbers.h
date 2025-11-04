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
    
    // Friend operators for operations with doubles
    friend Complex operator+(const Complex& c, double d) {
        return Complex(c.real_ + d, c.imag_);
    }
    friend Complex operator+(double d, const Complex& c) {
        return Complex(c.real_ + d, c.imag_);
    }
    friend Complex operator-(const Complex& c, double d) {
        return Complex(c.real_ - d, c.imag_);
    }
    friend Complex operator-(double d, const Complex& c) {
        return Complex(d - c.real_, -c.imag_);
    }
    friend Complex operator*(const Complex& c, double d) {
        return Complex(c.real_ * d, c.imag_ * d);
    }
    friend Complex operator*(double d, const Complex& c) {
        return Complex(c.real_ * d, c.imag_ * d);
    }
    friend Complex operator/(const Complex& c, double d) {
        return Complex(c.real_ / d, c.imag_ / d);
    }
    friend Complex operator/(double d, const Complex& c) {
        // Compute d / (a + bi) = (d * a)/(a^2 + b^2) - (d * b)/(a^2 + b^2) * i
        double denominator = c.real_ * c.real_ + c.imag_ * c.imag_;
        return Complex(d * c.real_ / denominator, -d * c.imag_ / denominator);
    }
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
