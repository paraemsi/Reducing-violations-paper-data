#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0);

    double real() const;
    double imag() const;

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);
    Complex& operator*=(double scalar);
    Complex operator*(double scalar) const;
    Complex operator/(double scalar) const;
    Complex operator+(double scalar) const;
    Complex operator-(double scalar) const;

    // Member versions of helper operations expected by the tests
    Complex conj() const;
    double  abs()  const;
    Complex exp()  const;

private:
    double re_;
    double im_;
};

// Arithmetic operators
Complex operator+(Complex lhs, const Complex& rhs);
Complex operator-(Complex lhs, const Complex& rhs);
Complex operator*(Complex lhs, const Complex& rhs);
Complex operator/(Complex lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);
bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

// Other operations
Complex conj(const Complex& value);
double abs(const Complex& value);
Complex exp(const Complex& value);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
