#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex() = default;
    Complex(double r, double i);

    double real() const;
    double imag() const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    Complex conj() const;
    double abs() const;
    Complex exp() const;

    // Operations with scalar (real) values
    Complex operator+(double rhs) const;
    Complex operator-(double rhs) const;
    Complex operator*(double rhs) const;
    Complex operator/(double rhs) const;

private:
    double real_ = 0.0;
    double imag_ = 0.0;
};

Complex operator*(double lhs, const Complex& rhs);
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
