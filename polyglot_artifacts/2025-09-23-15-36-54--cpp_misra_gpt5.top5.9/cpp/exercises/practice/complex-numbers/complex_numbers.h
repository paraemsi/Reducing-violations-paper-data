#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex final {
public:
    Complex() noexcept;
    Complex(double real_part, double imag_part) noexcept;

    double real() const noexcept;
    double imag() const noexcept;

    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

private:
    double real_;
    double imag_;
};

// Binary operators between complex numbers
Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator/(const Complex& lhs, const Complex& rhs) noexcept;

// Mixed operators with real numbers (double)
Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs) noexcept;

Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

// Free-function helpers
Complex conj(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;
Complex exp(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
