#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

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
    
    // Friend operators for operations with doubles
    friend Complex operator+(const Complex& lhs, double rhs);
    friend Complex operator+(double lhs, const Complex& rhs);
    friend Complex operator-(const Complex& lhs, double rhs);
    friend Complex operator-(double lhs, const Complex& rhs);
    friend Complex operator*(const Complex& lhs, double rhs);
    friend Complex operator*(double lhs, const Complex& rhs);
    friend Complex operator/(const Complex& lhs, double rhs);
    friend Complex operator/(double lhs, const Complex& rhs);
};

// Implement these in the .cpp file
Complex operator+(const Complex& lhs, double rhs);
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, double rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, double rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, double rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
