#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex();
    Complex(double real, double imag = 0.0);

    double real() const;
    double imag() const;

    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double re_;
    double im_;
};

// Arithmetic operators
Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator+(const Complex& lhs, double rhs);
Complex operator+(double lhs, const Complex& rhs);

Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, double rhs);
Complex operator-(double lhs, const Complex& rhs);

Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, double rhs);
Complex operator*(double lhs, const Complex& rhs);

Complex operator/(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, double rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
