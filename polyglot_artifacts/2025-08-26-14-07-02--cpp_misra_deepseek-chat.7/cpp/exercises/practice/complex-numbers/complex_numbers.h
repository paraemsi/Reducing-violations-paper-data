#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
private:
    double real_;
    double imag_;
public:
    Complex(double real, double imag);
    double real() const;
    double imag() const;
    
    // Operations
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    
    // Overloads for operations with doubles
    Complex operator+(double other) const;
    Complex operator-(double other) const;
    Complex operator*(double other) const;
    Complex operator/(double other) const;
    
    // Friend functions for operations where double comes first
    friend Complex operator+(double lhs, const Complex& rhs) {
        return Complex(lhs + rhs.real_, rhs.imag_);
    }
    friend Complex operator-(double lhs, const Complex& rhs) {
        return Complex(lhs - rhs.real_, -rhs.imag_);
    }
    friend Complex operator*(double lhs, const Complex& rhs) {
        return Complex(lhs * rhs.real_, lhs * rhs.imag_);
    }
    friend Complex operator/(double lhs, const Complex& rhs) {
        // To compute lhs / (a + bi), which is the same as lhs * conjugate / (a² + b²)
        double denominator = (rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_);
        if (denominator == 0.0) {
            return Complex(0.0/0.0, 0.0/0.0);
        }
        return Complex((lhs * rhs.real_) / denominator, (-lhs * rhs.imag_) / denominator);
    }
    
    // Other functions
    double abs() const;
    Complex conj() const;
    Complex exp() const;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
