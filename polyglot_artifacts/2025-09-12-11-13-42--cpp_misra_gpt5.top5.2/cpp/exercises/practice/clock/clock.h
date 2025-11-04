#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {
namespace clock {

class Clock {
public:
    Clock(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;
    static Clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

    Clock plus(std::int32_t minutes) const noexcept;
    Clock minus(std::int32_t minutes) const noexcept;

    std::string to_string() const;
    operator std::string() const;

    friend bool operator==(const Clock& lhs, const Clock& rhs) noexcept;
    friend bool operator!=(const Clock& lhs, const Clock& rhs) noexcept;

private:
    std::int32_t m_minutes;
};

Clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

}  // namespace clock
}  // namespace date_independent

#endif // CLOCK_H
