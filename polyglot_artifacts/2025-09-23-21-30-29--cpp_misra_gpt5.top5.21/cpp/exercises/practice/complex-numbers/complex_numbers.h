#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H


namespace complex_numbers {

class Complex final {
public:
    explicit constexpr Complex(double real_val = 0.0, double imag_val = 0.0) noexcept
        : re(real_val), im(imag_val) {}

    double real() const noexcept;
    double imag() const noexcept;

    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const noexcept;

    Complex operator+(double rhs) const noexcept;
    Complex operator-(double rhs) const noexcept;
    Complex operator*(double rhs) const noexcept;
    Complex operator/(double rhs) const noexcept;

    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

private:
    double re;
    double im;
};

 // real on the left-hand side overloads
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

// free-function helpers
double real(const Complex& z) noexcept;
double imag(const Complex& z) noexcept;
Complex conj(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;
Complex exp(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
