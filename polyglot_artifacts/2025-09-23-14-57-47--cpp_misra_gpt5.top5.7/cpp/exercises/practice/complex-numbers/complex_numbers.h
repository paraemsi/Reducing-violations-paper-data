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

    Complex operator+(double value) const noexcept;
    Complex operator-(double value) const noexcept;
    Complex operator*(double value) const noexcept;
    Complex operator/(double value) const noexcept;

    Complex conjugate() const noexcept;
    Complex conj() const noexcept;

private:
    double re_;
    double im_;
};

Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

double abs(const Complex& z) noexcept;
Complex exp(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
