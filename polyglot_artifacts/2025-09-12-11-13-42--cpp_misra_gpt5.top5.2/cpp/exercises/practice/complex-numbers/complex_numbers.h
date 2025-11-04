#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H


namespace complex_numbers {

class Complex final {
public:
    Complex() noexcept;
    Complex(double real, double imag) noexcept;
    explicit Complex(double real) noexcept;

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
    double real_{0.0};
    double imag_{0.0};
};

/* Non-member operators to support real-Complex mixed operations */
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
