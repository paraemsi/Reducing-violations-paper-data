#ifndef CLOCK_H
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

using hour_t   = std::int32_t;
using minute_t = std::int32_t;

class Clock {
public:
    Clock(hour_t hour, minute_t minute = static_cast<minute_t>(0)) noexcept;

    [[nodiscard]] Clock  plus (minute_t minutes) const noexcept;
    [[nodiscard]] Clock  minus(minute_t minutes) const noexcept;

    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] bool operator==(const Clock& other) const noexcept;
    [[nodiscard]] bool operator!=(const Clock& other) const noexcept;

private:
    minute_t minutes_since_midnight_;                          // 0‥1439
    static constexpr minute_t minutes_per_day_ = static_cast<minute_t>(1440);

    static minute_t normalize(minute_t total_minutes) noexcept;
};

namespace clock {

inline Clock at(hour_t hour,
               minute_t minute = static_cast<minute_t>(0)) noexcept {
    return Clock(hour, minute);
}

} // namespace clock

std::string string(const Clock& clk);

} // namespace date_independent

#endif // CLOCK_H
