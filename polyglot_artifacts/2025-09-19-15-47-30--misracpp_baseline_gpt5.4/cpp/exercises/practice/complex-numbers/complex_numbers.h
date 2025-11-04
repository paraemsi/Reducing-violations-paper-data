#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    // Construct a complex number with given real and imaginary parts.
    Complex();
    explicit Complex(double real);
    Complex(double real, double imag);

    // Accessors
    double real() const;
    double imag() const;

    // Unary operations
    Complex conj() const;  // conjugate
    double abs() const;    // absolute value (magnitude)
    Complex exp() const;   // exponent e^(a + i*b)

    // Binary operations with another complex number
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Binary operations with a real number
    Complex operator+(double rhs) const;
    Complex operator-(double rhs) const;
    Complex operator*(double rhs) const;
    Complex operator/(double rhs) const;

private:
    double re_;
    double im_;
};

// Real-Complex non-member operations
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
