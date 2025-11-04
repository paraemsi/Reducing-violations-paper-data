#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex();
    Complex(double real);
    Complex(double real, double imag);
    double real() const;
    double imag() const;
    Complex conj() const;
    double abs() const;
    Complex exp() const;

    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(const Complex& rhs) const;
    Complex operator/(const Complex& rhs) const;

    Complex operator+(double rhs) const;
    Complex operator-(double rhs) const;
    Complex operator*(double rhs) const;
    Complex operator/(double rhs) const;

private:
    double re_;
    double im_;
};

// Operators with double on the left-hand side
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

// Utility functions
Complex conj(const Complex& value);
double abs(const Complex& value);
Complex exp(const Complex& value);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
