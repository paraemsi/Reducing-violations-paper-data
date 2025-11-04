#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock {
 public:
  static clock at(std::int32_t hour, std::int32_t minute);

  clock plus(std::int32_t minutes) const;
  clock minus(std::int32_t minutes) const;

  bool operator==(const clock& other) const;
  bool operator!=(const clock& other) const;

  std::string to_string() const;

 private:
  explicit clock(std::int64_t total_minutes);

  std::int64_t minutes_{0};
};

}  // namespace date_independent

#endif  // CLOCK_H
