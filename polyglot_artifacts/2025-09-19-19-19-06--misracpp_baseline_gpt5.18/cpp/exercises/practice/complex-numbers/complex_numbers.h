#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    // Constructs a complex number a + b*i
    Complex();
    Complex(double real, double imag = 0.0);

    // Accessors
    double real() const;
    double imag() const;

    // Arithmetic operations
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Unary operators
    Complex operator+() const;
    Complex operator-() const;

    // Comparisons
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    // Operations with real numbers
    Complex operator+(double other) const;
    Complex operator-(double other) const;
    Complex operator*(double other) const;
    Complex operator/(double other) const;

    // Other operations
    Complex conjugate() const;
    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double re_;
    double im_;
};

 // Overloads with double on the left-hand side
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

// Free function wrappers
double real(const Complex& z);
double imag(const Complex& z);
double abs(const Complex& z);
Complex conj(const Complex& z);
Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
