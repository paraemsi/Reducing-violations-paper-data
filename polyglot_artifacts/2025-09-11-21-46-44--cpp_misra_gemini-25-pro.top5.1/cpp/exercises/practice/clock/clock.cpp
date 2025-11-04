#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr std::int64_t minutes_per_hour{60};
constexpr std::int64_t hours_per_day{24};
constexpr std::int64_t minutes_per_day{(hours_per_day * minutes_per_hour)};
}  // namespace

clock::clock(std::int64_t total_minutes) {
  std::int64_t normalized_minutes = total_minutes % minutes_per_day;
  if (normalized_minutes < 0) {
    normalized_minutes += minutes_per_day;
  }
  minutes_ = normalized_minutes;
}

clock clock::at(std::int32_t hour, std::int32_t minute) {
  return clock(((static_cast<std::int64_t>(hour) * minutes_per_hour) +
                static_cast<std::int64_t>(minute)));
}

clock clock::plus(std::int32_t minutes) const {
  return clock((minutes_ + static_cast<std::int64_t>(minutes)));
}

clock clock::minus(std::int32_t minutes) const {
  return clock((minutes_ - static_cast<std::int64_t>(minutes)));
}

bool clock::operator==(const clock& other) const {
  return minutes_ == other.minutes_;
}

bool clock::operator!=(const clock& other) const {
  return minutes_ != other.minutes_;
}

std::string clock::to_string() const {
  const std::int64_t hour{minutes_ / minutes_per_hour};
  const std::int64_t minute{minutes_ % minutes_per_hour};

  std::ostringstream oss;
  oss << std::setfill('0') << std::setw(2) << hour << ":" << std::setw(2)
      << minute;

  return oss.str();
}

}  // namespace date_independent
