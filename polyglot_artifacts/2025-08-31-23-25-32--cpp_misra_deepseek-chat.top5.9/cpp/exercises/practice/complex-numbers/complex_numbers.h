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
    
    // Friend functions for mixed-type operations
    friend Complex operator+(const Complex& lhs, double rhs) {
        return Complex(((lhs.real() + rhs)), lhs.imag());
    }
    friend Complex operator+(double lhs, const Complex& rhs) {
        return Complex(((lhs + rhs.real())), rhs.imag());
    }
    friend Complex operator-(const Complex& lhs, double rhs) {
        return Complex(((lhs.real() - rhs)), lhs.imag());
    }
    friend Complex operator-(double lhs, const Complex& rhs) {
        return Complex(((lhs - rhs.real())), ((-rhs.imag())));
    }
    friend Complex operator*(const Complex& lhs, double rhs) {
        return Complex(((lhs.real() * rhs)), ((lhs.imag() * rhs)));
    }
    friend Complex operator*(double lhs, const Complex& rhs) {
        return Complex(((lhs * rhs.real())), ((lhs * rhs.imag())));
    }
    friend Complex operator/(const Complex& lhs, double rhs) {
        return Complex(((lhs.real() / rhs)), ((lhs.imag() / rhs)));
    }
    friend Complex operator/(double lhs, const Complex& rhs) {
        // To compute lhs / (a + bi), we can use the formula for division
        // Treat lhs as lhs + 0i
        // So it's (lhs + 0i) / (a + bi) = (lhs*a)/(a^2 + b^2) + (-lhs*b)/(a^2 + b^2)i
        double denominator = (((rhs.real() * rhs.real())) + ((rhs.imag() * rhs.imag())));
        double real_part = (((lhs * rhs.real())) / denominator);
        double imag_part = ((((-lhs) * rhs.imag())) / denominator);
        return Complex(real_part, imag_part);
    }
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
