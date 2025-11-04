#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0);

    double real() const;
    double imag() const;

    // Operations with other complex numbers
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Operations with real numbers
    Complex operator+(double value) const;
    Complex operator-(double value) const;
    Complex operator*(double value) const;
    Complex operator/(double value) const;

    // Conjugate, absolute value, and exponent
    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double re_;
    double im_;
};

 // Symmetric operations with real numbers on the left-hand side
Complex operator+(double value, const Complex& z);
Complex operator-(double value, const Complex& z);
Complex operator*(double value, const Complex& z);
Complex operator/(double value, const Complex& z);

// Non-member helpers
Complex conj(const Complex& z);
double abs(const Complex& z);
Complex exp(const Complex& z);

// Accessors as non-member helpers (for compatibility)
double real(const Complex& z);
double imag(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
