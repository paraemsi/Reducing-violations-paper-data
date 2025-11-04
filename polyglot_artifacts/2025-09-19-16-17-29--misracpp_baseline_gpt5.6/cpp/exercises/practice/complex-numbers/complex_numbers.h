#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

// Avoid macro conflicts that may be introduced by C headers
#ifdef conj
#undef conj
#endif
#ifdef abs
#undef abs
#endif
#ifdef exp
#undef exp
#endif

namespace complex_numbers {

class Complex {
public:
    Complex() noexcept;
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

// Scalar operations with a real number (double)
Complex operator+(const Complex& z, double d) noexcept;
Complex operator+(double d, const Complex& z) noexcept;

Complex operator-(const Complex& z, double d) noexcept;
Complex operator-(double d, const Complex& z) noexcept;

Complex operator*(const Complex& z, double d) noexcept;
Complex operator*(double d, const Complex& z) noexcept;

Complex operator/(const Complex& z, double d) noexcept;
Complex operator/(double d, const Complex& z) noexcept;

// Free function helpers
Complex conj(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;
Complex exp(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
