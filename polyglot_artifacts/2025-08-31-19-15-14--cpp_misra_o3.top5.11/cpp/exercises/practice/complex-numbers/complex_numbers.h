#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

/*
 * A lightweight complex number implementation that obeys the subset of
 * MISRA-C++ rules supplied in the exercise description.
 */
class Complex final
{
public:
    /* Constructors */
    constexpr Complex(double real_val = 0.0, double imag_val = 0.0) noexcept
        : real_part(real_val), imag_part(imag_val) {}

    /* Observers */
    [[nodiscard]] constexpr double real(void) const noexcept { return real_part; }
    [[nodiscard]] constexpr double imag(void) const noexcept { return imag_part; }

    /* Modifiers */
    void set_real(double real_val) noexcept { real_part = real_val; }
    void set_imag(double imag_val) noexcept { imag_part = imag_val; }

    /* Additional operations */
    [[nodiscard]] Complex conj() const noexcept;
    [[nodiscard]] double  abs() const noexcept;
    [[nodiscard]] Complex exp() const;

private:
    double real_part; /* NOLINT(cppcoreguidelines-non-private-member-variables-in-classes) */
    double imag_part; /* NOLINT(cppcoreguidelines-non-private-member-variables-in-classes) */
};

/* Binary arithmetic operators */
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);

/* Unary functions */
[[nodiscard]] Complex conjugate(const Complex& value) noexcept;
[[nodiscard]] double  abs(const Complex& value) noexcept;
[[nodiscard]] Complex exp(const Complex& value);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
