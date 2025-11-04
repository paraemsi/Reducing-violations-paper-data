#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    // Constructors
    Complex();
    Complex(double real_value, double imaginary_value);
    
    // Getters
    double real() const;
    double imag() const;
    
    // Arithmetic operations with Complex
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    // Arithmetic operations with double
    Complex operator+(double value) const;
    Complex operator-(double value) const;
    Complex operator*(double value) const;
    Complex operator/(double value) const;
    
    // Other operations
    Complex conj() const;
    double abs() const;
    Complex exp() const;
    
private:
    double real_part;
    double imaginary_part;
};

// Non-member operators for double on left side
Complex operator+(double value, const Complex& c);
Complex operator-(double value, const Complex& c);
Complex operator*(double value, const Complex& c);
Complex operator/(double value, const Complex& c);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
