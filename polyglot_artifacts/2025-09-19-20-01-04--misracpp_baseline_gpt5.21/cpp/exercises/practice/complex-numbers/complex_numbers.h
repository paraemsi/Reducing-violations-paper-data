#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex() = default;
    Complex(double real);
    Complex(double real, double imag);

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
    double real_{0.0};
    double imag_{0.0};
};


// Overloads to operate with real numbers on either side
Complex operator+(const Complex& lhs, double rhs);
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, double rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, double rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, double rhs);
Complex operator/(double lhs, const Complex& rhs);

// Free-function helpers
double real(const Complex& z);
double imag(const Complex& z);
Complex conj(const Complex& z);
double abs(const Complex& z);
Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
