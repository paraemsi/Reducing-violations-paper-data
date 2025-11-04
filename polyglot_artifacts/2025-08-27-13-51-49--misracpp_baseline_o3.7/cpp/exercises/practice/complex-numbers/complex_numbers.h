#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    // Construct a complex number with given real and imaginary parts.
    // Defaults to the additive identity 0 + 0i when no arguments are supplied.
    Complex(double real = 0.0, double imag = 0.0);

    // Accessors
    double real() const;
    double imag() const;

    // Basic arithmetic
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Compound assignment operators
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    // Conjugate, magnitude and exponent
    Complex conj() const;
    double  abs() const;
    Complex exp() const;

private:
    double real_;
    double imag_;
};

// Non-member arithmetic operations with double scalars
Complex operator+(const Complex& lhs, double rhs);
Complex operator+(double lhs, const Complex& rhs);

Complex operator-(const Complex& lhs, double rhs);
Complex operator-(double lhs, const Complex& rhs);

Complex operator*(const Complex& lhs, double rhs);
Complex operator*(double lhs, const Complex& rhs);

Complex operator/(const Complex& lhs, double rhs);
Complex operator/(double lhs, const Complex& rhs);

// Comparison operators
bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
