#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    // Constructors
    Complex(double real = 0.0, double imag = 0.0);

    // Accessors
    double real() const;
    double imag() const;

    // Arithmetic between complex numbers
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Additional operations as member functions
    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double re_;
    double im_;
};

// Arithmetic with scalars (double)
Complex operator+(const Complex& lhs, double rhs);
Complex operator-(const Complex& lhs, double rhs);
Complex operator*(const Complex& lhs, double rhs);
Complex operator/(const Complex& lhs, double rhs);

Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

// Additional operations
Complex conj(const Complex& c);
double abs(const Complex& c);
Complex exp(const Complex& c);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
