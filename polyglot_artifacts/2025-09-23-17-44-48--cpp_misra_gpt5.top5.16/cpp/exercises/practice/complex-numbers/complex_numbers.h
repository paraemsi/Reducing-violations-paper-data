#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H


namespace complex_numbers {

class Complex final {
public:
    Complex() noexcept;
    Complex(double real, double imag) noexcept;

    double real() const noexcept;
    double imag() const noexcept;

    Complex conjugate() const noexcept;
    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

    Complex operator+(const Complex& rhs) const noexcept;
    Complex operator-(const Complex& rhs) const noexcept;
    Complex operator*(const Complex& rhs) const noexcept;
    Complex operator/(const Complex& rhs) const noexcept;

    Complex operator+(double rhs) const noexcept;
    Complex operator-(double rhs) const noexcept;
    Complex operator*(double rhs) const noexcept;
    Complex operator/(double rhs) const noexcept;

    bool operator==(const Complex& rhs) const noexcept;
    bool operator!=(const Complex& rhs) const noexcept;

private:
    double real_;
    double imag_;
};

// Free-function helpers
Complex add(const Complex& lhs, const Complex& rhs) noexcept;
Complex subtract(const Complex& lhs, const Complex& rhs) noexcept;
Complex multiply(const Complex& lhs, const Complex& rhs) noexcept;
Complex divide(const Complex& lhs, const Complex& rhs) noexcept;
double abs(const Complex& z) noexcept;
Complex conjugate(const Complex& z) noexcept;
Complex exp(const Complex& z) noexcept;
double real(const Complex& z) noexcept;
double imag(const Complex& z) noexcept;

Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
