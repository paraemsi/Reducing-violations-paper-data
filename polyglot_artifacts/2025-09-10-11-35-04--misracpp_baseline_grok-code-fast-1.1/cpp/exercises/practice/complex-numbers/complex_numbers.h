#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex(double r = 0.0, double i = 0.0);
    
    // Binary operators
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    // Unary operations
    Complex conj() const;
    double abs() const;
    Complex exp() const;
    
    // Accessors (optional, for testing or external use)
    double real() const { return real_; }
    double imag() const { return imag_; }

private:
    double real_;
    double imag_;
};

// Non-member operators for double + Complex, etc.
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
