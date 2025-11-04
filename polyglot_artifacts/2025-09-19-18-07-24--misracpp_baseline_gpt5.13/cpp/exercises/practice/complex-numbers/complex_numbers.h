#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
 public:
  Complex(double real = 0.0, double imag = 0.0);

  double real() const;
  double imag() const;

  Complex operator+(const Complex& other) const;
  Complex operator-(const Complex& other) const;
  Complex operator*(const Complex& other) const;
  Complex operator/(const Complex& other) const;

  Complex conj() const;
  double abs() const;
  Complex exp() const;

 private:
  double re_;
  double im_;
};

// Free function wrappers
Complex conj(const Complex& z);
double abs(const Complex& z);
Complex exp(const Complex& z);

// Operators with double on the left-hand side
Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
