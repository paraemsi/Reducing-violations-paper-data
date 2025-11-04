#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
 public:
  static clock at(int hours, int minutes);
  clock operator+(int minutes) const;
  clock operator-(int minutes) const;
  bool operator==(const clock& other) const = default;
  explicit operator std::string() const;

 private:
  explicit clock(int minutes);
  int minutes_;
};

}  // namespace date_independent

#endif // CLOCK_H
