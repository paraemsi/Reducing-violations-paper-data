#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
 public:
  Complex();
  explicit Complex(double real);
  Complex(double real, double imag);

  double real() const;
  double imag() const;

  double abs() const;
  Complex conj() const;
  Complex exp() const;

  Complex operator+(const Complex& other) const;
  Complex operator-(const Complex& other) const;
  Complex operator*(const Complex& other) const;
  Complex operator/(const Complex& other) const;

  Complex operator+(double value) const;
  Complex operator-(double value) const;
  Complex operator*(double value) const;
  Complex operator/(double value) const;

  friend Complex operator+(double value, const Complex& self);
  friend Complex operator-(double value, const Complex& self);
  friend Complex operator*(double value, const Complex& self);
  friend Complex operator/(double value, const Complex& self);

 private:
  double real_ = 0.0;
  double imag_ = 0.0;
};

Complex operator+(double value, const Complex& self);
Complex operator-(double value, const Complex& self);
Complex operator*(double value, const Complex& self);
Complex operator/(double value, const Complex& self);

Complex conj(const Complex& z);
double abs(const Complex& z);
Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
