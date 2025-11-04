#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <ostream>

namespace date_independent {

class Clock {
public:
    [[nodiscard]] static Clock at(std::int32_t hours,
                                  std::int32_t minutes = static_cast<std::int32_t>(0));

    [[nodiscard]] Clock plus(std::int32_t minutes) const;
    [[nodiscard]] Clock minus(std::int32_t minutes) const;

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] explicit operator std::string() const;

    friend bool operator==(const Clock& lhs, const Clock& rhs);
    friend bool operator!=(const Clock& lhs, const Clock& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Clock& clock);

private:
    explicit Clock(std::int32_t totalMinutes);

    std::int32_t totalMinutes_;
    static constexpr std::int32_t minutesPerDay_{ static_cast<std::int32_t>(1440) };
};

namespace clock {

using Clock = ::date_independent::Clock;

inline Clock at(std::int32_t hours,
                std::int32_t minutes = static_cast<std::int32_t>(0))
{
    return Clock::at(hours, minutes);
}

}  // namespace clock
}  // namespace date_independent

#endif // CLOCK_H
