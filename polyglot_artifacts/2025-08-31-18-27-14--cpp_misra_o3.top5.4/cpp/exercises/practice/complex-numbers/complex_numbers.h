#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    /* Constructors */
    Complex(double real_part = 0.0, double imag_part = 0.0) noexcept;

    /* Accessors */
    [[nodiscard]] double real() const noexcept;
    [[nodiscard]] double imag() const noexcept;

    /* Basic arithmetic operators */
    [[nodiscard]] Complex operator+(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator-(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator*(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator/(const Complex& other) const;

    /* Scalar operations with real numbers */
    [[nodiscard]] Complex operator+(double value) const noexcept;
    [[nodiscard]] Complex operator-(double value) const noexcept;
    [[nodiscard]] Complex operator*(double value) const noexcept;
    [[nodiscard]] Complex operator/(double value) const;

    /* Other operations */
    [[nodiscard]] Complex conj() const noexcept;
    [[nodiscard]] double  abs() const noexcept;
    [[nodiscard]] Complex exp() const;

private:
    double real_value_;
    double imag_value_;
};  // class Complex

/*======================================================================
 *  Exercism-style free-function façade
 *====================================================================*/
[[nodiscard]] inline Complex  make_complex(double real, double imag = 0.0) noexcept
{
    return Complex{real, imag};
}

[[nodiscard]] inline Complex  operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex{ (lhs + rhs.real()), rhs.imag() };
}

[[nodiscard]] inline Complex  operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex{ (lhs - rhs.real()), (-rhs.imag()) };
}

[[nodiscard]] inline Complex  operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex{ (lhs * rhs.real()), (lhs * rhs.imag()) };
}

[[nodiscard]] inline Complex  operator/(double lhs, const Complex& rhs)
{
    return Complex{ lhs, 0.0 }.operator/(rhs);
}

[[nodiscard]] inline Complex  conj(const Complex& cplx) noexcept
{
    return cplx.conj();
}

[[nodiscard]] inline double   abs(const Complex& cplx) noexcept
{
    return cplx.abs();
}

[[nodiscard]] inline Complex  exp(const Complex& cplx)
{
    return cplx.exp();
}


}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
