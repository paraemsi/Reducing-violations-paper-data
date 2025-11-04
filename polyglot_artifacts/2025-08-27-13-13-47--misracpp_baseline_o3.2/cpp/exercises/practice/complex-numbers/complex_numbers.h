#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
 public:
  constexpr Complex(double real = 0.0, double imag = 0.0) : real_{real}, imag_{imag} {}

  // Accessors
  constexpr double real() const { return real_; }
  constexpr double imag() const { return imag_; }

  // Arithmetic operators
  constexpr Complex operator+(const Complex& other) const {
    return {real_ + other.real_, imag_ + other.imag_};
  }

  constexpr Complex operator-(const Complex& other) const {
    return {real_ - other.real_, imag_ - other.imag_};
  }

  constexpr Complex operator*(const Complex& other) const {
    return {real_ * other.real_ - imag_ * other.imag_,
            imag_ * other.real_ + real_ * other.imag_};
  }

  // Equality comparison
  constexpr bool operator==(const Complex& other) const {
    return real_ == other.real_ && imag_ == other.imag_;
  }

  Complex operator/(const Complex& other) const;

  // Additional operations
  constexpr Complex conj() const { return {real_, -imag_}; }
  double abs() const;
  Complex exp() const;

 private:
  double real_;
  double imag_;
};

Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

// Free functions mirroring std::complex interface
Complex conj(const Complex& z);
double   abs(const Complex& z);
Complex  exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
