#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0) noexcept;

    double real() const noexcept;
    double imag() const noexcept;

    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const noexcept;

    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

private:
    double re_{0.0};
    double im_{0.0};
};

// Scalar overloads
Complex operator+(const Complex& z, double r) noexcept;
Complex operator+(double r, const Complex& z) noexcept;
Complex operator-(const Complex& z, double r) noexcept;
Complex operator-(double r, const Complex& z) noexcept;
Complex operator*(const Complex& z, double r) noexcept;
Complex operator*(double r, const Complex& z) noexcept;
Complex operator/(const Complex& z, double r) noexcept;
Complex operator/(double r, const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
