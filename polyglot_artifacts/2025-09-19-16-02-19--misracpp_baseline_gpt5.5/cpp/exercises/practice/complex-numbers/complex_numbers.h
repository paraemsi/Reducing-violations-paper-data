#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
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
    double re_ = 0.0;
    double im_ = 0.0;
};

// Operations with real numbers (double)
Complex operator+(const Complex& z, double d);
Complex operator+(double d, const Complex& z);
Complex operator-(const Complex& z, double d);
Complex operator-(double d, const Complex& z);
Complex operator*(const Complex& z, double d);
Complex operator*(double d, const Complex& z);
Complex operator/(const Complex& z, double d);
Complex operator/(double d, const Complex& z);

// Free function interfaces matching common expectations
Complex conj(const Complex& z);
double abs(const Complex& z);
Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
