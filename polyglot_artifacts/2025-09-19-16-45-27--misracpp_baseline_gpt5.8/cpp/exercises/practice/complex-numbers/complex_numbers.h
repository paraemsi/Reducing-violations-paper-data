#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
 public:
  Complex();
  Complex(double real, double imag = 0.0);

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
  double real_;
  double imag_;
};

Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

// Free-function overloads for algorithms to enable ADL calls like real(z), imag(z), abs(z), conj(z), exp(z)
double real(const Complex& z);
double imag(const Complex& z);
Complex conj(const Complex& z);
double abs(const Complex& z);
Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
