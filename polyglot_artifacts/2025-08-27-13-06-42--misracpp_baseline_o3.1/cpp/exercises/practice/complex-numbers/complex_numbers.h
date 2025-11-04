#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0);

    double real() const;
    double imag() const;

    Complex operator+(const Complex &other) const;
    Complex operator-(const Complex &other) const;
    Complex operator*(const Complex &other) const;
    Complex operator/(const Complex &other) const;

    Complex conj() const;
    double abs() const;
    Complex exp() const;

    // operations with scalar (real) values
    Complex operator+(double other) const;
    Complex operator-(double other) const;
    Complex operator*(double other) const;
    Complex operator/(double other) const;

    // allow scalar on the left-hand side
    friend Complex operator+(double lhs, const Complex &rhs);
    friend Complex operator-(double lhs, const Complex &rhs);
    friend Complex operator*(double lhs, const Complex &rhs);
    friend Complex operator/(double lhs, const Complex &rhs);

private:
    double r_;
    double i_;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
