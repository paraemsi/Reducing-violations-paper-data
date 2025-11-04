#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex();
    Complex(double real, double imag);

    double real() const;
    double imag() const;

    // Complex-Complex operators
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Complex-scalar operators
    Complex operator+(double scalar) const;
    Complex operator-(double scalar) const;
    Complex operator*(double scalar) const;
    Complex operator/(double scalar) const;

    // scalar-Complex operators (friends)
    friend Complex operator+(double scalar, const Complex& z);
    friend Complex operator-(double scalar, const Complex& z);
    friend Complex operator*(double scalar, const Complex& z);
    friend Complex operator/(double scalar, const Complex& z);

    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double re_;
    double im_;
};


}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
