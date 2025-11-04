#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex() : r_(0.0), i_(0.0) {}
    explicit Complex(double real);
    Complex(double real, double imag);
    double real() const;
    double imag() const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Unary operators
    Complex operator+() const;
    Complex operator-() const;

    // Operations with real scalars (rhs)
    Complex operator+(double value) const;
    Complex operator-(double value) const;
    Complex operator*(double value) const;
    Complex operator/(double value) const;

    Complex conjugate() const;
    Complex conj() const;
    double abs() const;
    Complex exp() const;

    // Accessors kept for symmetry with free functions
    // These are trivial and do not throw.

private:
    double r_;
    double i_;
};

// Free-function interfaces for convenience/compatibility
Complex conjugate(const Complex& z);
double abs(const Complex& z);
Complex exp(const Complex& z);

// Accessors as free functions
double real(const Complex& z);
double imag(const Complex& z);

// Operations with real scalars (lhs)
Complex operator+(double value, const Complex& z);
Complex operator-(double value, const Complex& z);
Complex operator*(double value, const Complex& z);
Complex operator/(double value, const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
