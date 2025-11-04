#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
private:
    double real_;
    double imag_;
public:
    Complex(double real = 0.0, double imag = 0.0);
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
};

// Non-member operator overloads to handle double op Complex
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
    // To divide a double by a complex number, we can treat the double as a complex number with imaginary part 0
    // and use the complex division formula
    double denominator = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    double real_part = (lhs * rhs.real()) / denominator;
    double imag_part = (-lhs * rhs.imag()) / denominator;
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
