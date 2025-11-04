#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
 public:
  explicit Complex(double real = 0.0, double imag = 0.0) : re_(real), im_(imag) {}
  double real() const;
  double imag() const;

  Complex conj() const;
  double abs() const;
  Complex exp() const;

  Complex operator+(const Complex& other) const;
  Complex operator-(const Complex& other) const;
  Complex operator*(const Complex& other) const;
  Complex operator/(const Complex& other) const;

  Complex operator+(double value) const;
  Complex operator-(double value) const;
  Complex operator*(double value) const;
  Complex operator/(double value) const;

  friend Complex operator+(double value, const Complex& z);
  friend Complex operator-(double value, const Complex& z);
  friend Complex operator*(double value, const Complex& z);
  friend Complex operator/(double value, const Complex& z);

 private:
  double re_;
  double im_;
};

Complex conj(const Complex& z);
double abs(const Complex& z);
Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
