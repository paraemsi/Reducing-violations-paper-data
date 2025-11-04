#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <stdexcept>

#if defined(__has_cpp_attribute)
#  if (__has_cpp_attribute(nodiscard) && (__cplusplus >= 201703L))
#    define CN_NODISCARD [[nodiscard]]
#  else
#    define CN_NODISCARD
#  endif
#else
#  define CN_NODISCARD
#endif

namespace complex_numbers {

class Complex
{
public:
    constexpr Complex(double real_val = 0.0, double imag_val = 0.0) noexcept
        : m_real(real_val), m_imag(imag_val)
    {
    }

    CN_NODISCARD constexpr double real() const noexcept
    {
        return m_real;
    }

    CN_NODISCARD constexpr double imag() const noexcept
    {
        return m_imag;
    }

    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator/=(const Complex& rhs);
    Complex& operator+=(double rhs) noexcept;
    Complex& operator-=(double rhs) noexcept;
    Complex& operator*=(double rhs) noexcept;
    Complex& operator/=(double rhs);

    /* Member utility wrappers */
    CN_NODISCARD double abs() const noexcept;
    CN_NODISCARD Complex conj() const noexcept;
    CN_NODISCARD Complex exp() const;

private:
    double m_real;
    double m_imag;
};

/* Non-member symmetrical operators */
CN_NODISCARD Complex operator+(Complex lhs, const Complex& rhs) noexcept;
CN_NODISCARD Complex operator-(Complex lhs, const Complex& rhs) noexcept;
CN_NODISCARD Complex operator*(Complex lhs, const Complex& rhs) noexcept;
CN_NODISCARD Complex operator/(Complex lhs, const Complex& rhs);

/* Operations with scalar double */
CN_NODISCARD Complex operator+(Complex lhs, double rhs) noexcept;
CN_NODISCARD Complex operator+(double lhs, Complex rhs) noexcept;
CN_NODISCARD Complex operator-(Complex lhs, double rhs) noexcept;
CN_NODISCARD Complex operator-(double lhs, Complex rhs) noexcept;
CN_NODISCARD Complex operator*(Complex lhs, double rhs) noexcept;
CN_NODISCARD Complex operator*(double lhs, Complex rhs) noexcept;
CN_NODISCARD Complex operator/(Complex lhs, double rhs);
CN_NODISCARD Complex operator/(double lhs, Complex rhs);

/* Equality operators */
CN_NODISCARD bool operator==(const Complex& lhs, const Complex& rhs) noexcept;
CN_NODISCARD bool operator!=(const Complex& lhs, const Complex& rhs) noexcept;

/* Utility functions */
CN_NODISCARD Complex conjugate(const Complex& z) noexcept;
CN_NODISCARD double abs(const Complex& z) noexcept;
CN_NODISCARD Complex exp(const Complex& z);

} // namespace complex_numbers

#endif /* COMPLEX_NUMBERS_H */
