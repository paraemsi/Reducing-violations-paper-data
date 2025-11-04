#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

namespace clock {

class Clock final {
public:
    Clock(std::int32_t hour, std::int32_t minute) noexcept;

    Clock plus_minutes(std::int32_t minutes) const noexcept;

    Clock plus(std::int32_t minutes) const noexcept;

    std::string to_string() const;

    explicit operator std::string() const;

    std::int32_t total_minutes() const noexcept;

private:
    std::int32_t minutes_since_midnight;
};

bool operator==(const Clock& lhs, const Clock& rhs) noexcept;
bool operator!=(const Clock& lhs, const Clock& rhs) noexcept;

Clock at(std::int32_t hour, std::int32_t minute = std::int32_t{0}) noexcept;

}  // namespace clock

using Clock = clock::Clock;

inline Clock at(std::int32_t hour, std::int32_t minute = std::int32_t{0}) noexcept
{
    return clock::at(hour, minute);
}

}  // namespace date_independent

#endif // CLOCK_H
