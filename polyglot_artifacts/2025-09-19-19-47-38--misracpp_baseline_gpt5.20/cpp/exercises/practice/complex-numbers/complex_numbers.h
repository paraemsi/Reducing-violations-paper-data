#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex() noexcept;
    explicit Complex(double real) noexcept;
    Complex(double real, double imag) noexcept;
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
    double re_;
    double im_;
};

/* Mixed-type operators */
Complex operator+(const Complex& z, double d) noexcept;
Complex operator+(double d, const Complex& z) noexcept;
Complex operator-(const Complex& z, double d) noexcept;
Complex operator-(double d, const Complex& z) noexcept;
Complex operator*(const Complex& z, double d) noexcept;
Complex operator*(double d, const Complex& z) noexcept;
Complex operator/(const Complex& z, double d) noexcept;
Complex operator/(double d, const Complex& z) noexcept;

/* Free-function helpers */
Complex conj(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;
Complex exp(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
