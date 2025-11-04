#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H


namespace complex_numbers {

class Complex {
public:
    // Construct with real and optional imaginary part (defaults to 0.0)
    // Implicit single-argument construction enables mixing with real values.
    Complex();

    Complex(double real, double imag = 0.0);

    double real() const;
    double imag() const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double m_real;
    double m_imag;
};

 // Support operations with a real number on the left-hand side
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
