#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex() noexcept;
    explicit Complex(double real, double imag) noexcept;

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

    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

private:
    double real_;
    double imag_;
};

Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

Complex conj(const Complex& value) noexcept;
double abs(const Complex& value) noexcept;
Complex exp(const Complex& value) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
