#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
private:
    double real_part;
    double imag_part;
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
    
    // Friend declarations for operations with doubles
    friend Complex operator+(const Complex& c, double d);
    friend Complex operator+(double d, const Complex& c);
    friend Complex operator-(const Complex& c, double d);
    friend Complex operator-(double d, const Complex& c);
    friend Complex operator*(const Complex& c, double d);
    friend Complex operator*(double d, const Complex& c);
    friend Complex operator/(const Complex& c, double d);
    friend Complex operator/(double d, const Complex& c);
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
