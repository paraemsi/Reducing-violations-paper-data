#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

using real_t = double;

class Complex {
public:
    explicit constexpr Complex(real_t real, real_t imag) noexcept : real_(real), imag_(imag) {}

    constexpr real_t real() const noexcept { return real_; }
    constexpr real_t imag() const noexcept { return imag_; }

    constexpr Complex operator+(const Complex& other) const noexcept {
        return Complex(real_ + other.real_, imag_ + other.imag_);
    }
    constexpr Complex operator-(const Complex& other) const noexcept {
        return Complex(real_ - other.real_, imag_ - other.imag_);
    }
    constexpr Complex operator*(const Complex& other) const noexcept {
        const real_t r = ((real_ * other.real_) - (imag_ * other.imag_));
        const real_t i = ((imag_ * other.real_) + (real_ * other.imag_));
        return Complex(r, i);
    }
    constexpr Complex operator/(const Complex& other) const noexcept {
        const real_t denominator = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
        const real_t r = ((real_ * other.real_) + (imag_ * other.imag_)) / denominator;
        const real_t i = ((imag_ * other.real_) - (real_ * other.imag_)) / denominator;
        return Complex(r, i);
    }

    real_t abs() const noexcept;
    constexpr Complex conj() const noexcept { return Complex(real_, -imag_); }
    Complex exp() const noexcept;

private:
    real_t real_;
    real_t imag_;
};

constexpr Complex operator+(const Complex& lhs, real_t rhs) noexcept {
    return Complex((lhs.real() + rhs), lhs.imag());
}
constexpr Complex operator+(real_t lhs, const Complex& rhs) noexcept {
    return Complex((lhs + rhs.real()), rhs.imag());
}
constexpr Complex operator-(const Complex& lhs, real_t rhs) noexcept {
    return Complex((lhs.real() - rhs), lhs.imag());
}
constexpr Complex operator-(real_t lhs, const Complex& rhs) noexcept {
    return Complex((lhs - rhs.real()), -rhs.imag());
}
constexpr Complex operator*(const Complex& lhs, real_t rhs) noexcept {
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}
constexpr Complex operator*(real_t lhs, const Complex& rhs) noexcept {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}
constexpr Complex operator/(const Complex& lhs, real_t rhs) noexcept {
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}
constexpr Complex operator/(real_t lhs, const Complex& rhs) noexcept {
    const real_t denominator = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    const real_t r = ((lhs * rhs.real()) / denominator);
    const real_t i = (-(lhs * rhs.imag()) / denominator);
    return Complex(r, i);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
