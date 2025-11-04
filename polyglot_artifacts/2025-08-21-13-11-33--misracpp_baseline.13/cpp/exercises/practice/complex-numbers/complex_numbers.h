#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    Complex(double real, double imag) : re(real), im(imag) {}

    double real() const { return re; }
    double imag() const { return im; }

    Complex operator+(const Complex& other) const {
        return Complex(re + other.re, im + other.im);
    }
    Complex operator+(double value) const {
        return Complex(re + value, im);
    }
    // Friend functions must be declared public but defined outside the class

    Complex operator-(const Complex& other) const {
        return Complex(re - other.re, im - other.im);
    }
    Complex operator-(double value) const {
        return Complex(re - value, im);
    }
    // Friend functions must be declared public but defined outside the class

    Complex operator*(const Complex& other) const {
        return Complex(re * other.re - im * other.im,
                       im * other.re + re * other.im);
    }
    Complex operator*(double value) const {
        return Complex(re * value, im * value);
    }
    // Friend functions must be declared public but defined outside the class

    Complex operator/(const Complex& other) const {
        double denom = other.re * other.re + other.im * other.im;
        return Complex(
            (re * other.re + im * other.im) / denom,
            (im * other.re - re * other.im) / denom
        );
    }
    Complex operator/(double value) const {
        return Complex(re / value, im / value);
    }
    // Friend functions must be declared public but defined outside the class

    Complex conj() const {
        return Complex(re, -im);
    }

    double abs() const {
        return std::sqrt(re * re + im * im);
    }

    Complex exp() const {
        double exp_re = std::exp(re);
        return Complex(
            exp_re * std::cos(im),
            exp_re * std::sin(im)
        );
    }

private:
    double re;
    double im;
};

}  // namespace complex_numbers

// Non-member operator overloads for double op Complex
inline complex_numbers::Complex operator+(double lhs, const complex_numbers::Complex& rhs) {
    return complex_numbers::Complex(lhs + rhs.real(), rhs.imag());
}
inline complex_numbers::Complex operator-(double lhs, const complex_numbers::Complex& rhs) {
    return complex_numbers::Complex(lhs - rhs.real(), -rhs.imag());
}
inline complex_numbers::Complex operator*(double lhs, const complex_numbers::Complex& rhs) {
    return complex_numbers::Complex(lhs * rhs.real(), lhs * rhs.imag());
}
inline complex_numbers::Complex operator/(double lhs, const complex_numbers::Complex& rhs) {
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return complex_numbers::Complex(
        (lhs * rhs.real()) / denom,
        (-lhs * rhs.imag()) / denom
    );
}

#endif  // COMPLEX_NUMBERS_H
