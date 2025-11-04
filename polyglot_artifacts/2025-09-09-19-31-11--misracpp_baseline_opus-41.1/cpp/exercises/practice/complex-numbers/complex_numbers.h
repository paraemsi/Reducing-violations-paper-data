#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    // Constructor
    Complex(double real_part = 0.0, double imag_part = 0.0);
    
    // Getters
    double real() const;
    double imag() const;
    
    // Absolute value
    double abs() const;
    
    // Conjugate
    Complex conj() const;
    
    // Exponential
    Complex exp() const;
    
    // Arithmetic operators
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    // Friend functions for operations with double on the left
    friend Complex operator+(double lhs, const Complex& rhs);
    friend Complex operator-(double lhs, const Complex& rhs);
    friend Complex operator*(double lhs, const Complex& rhs);
    friend Complex operator/(double lhs, const Complex& rhs);
    
private:
    double real_;
    double imag_;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
