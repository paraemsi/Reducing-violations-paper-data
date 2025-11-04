#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H


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

// Operations with scalars
Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator+(double lhs, const Complex& rhs) noexcept;

Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;

Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;

Complex operator/(const Complex& lhs, double rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

// Free-function utilities
Complex conj(const Complex& c) noexcept;
double abs(const Complex& c) noexcept;
Complex exp(const Complex& c) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
