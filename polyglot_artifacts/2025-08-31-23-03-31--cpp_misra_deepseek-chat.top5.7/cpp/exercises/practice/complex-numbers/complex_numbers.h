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
    
    double real() const { return real_; }
    double imag() const { return imag_; }
    
    double abs() const;
    Complex conj() const;
    Complex exp() const;
    
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    Complex operator+(double other) const;
    Complex operator-(double other) const;
    Complex operator*(double other) const;
    Complex operator/(double other) const;
};

Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
