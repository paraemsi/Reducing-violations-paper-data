#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
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
    
    // Add operators for scalar operations
    Complex operator+(double scalar) const;
    Complex operator-(double scalar) const;
    Complex operator*(double scalar) const;
    Complex operator/(double scalar) const;
    
private:
    double real_;
    double imag_;
};

// Add global operators for scalar on the left side
Complex operator+(double scalar, const Complex& c);
Complex operator-(double scalar, const Complex& c);
Complex operator*(double scalar, const Complex& c);
Complex operator/(double scalar, const Complex& c);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
