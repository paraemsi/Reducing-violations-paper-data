#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    using minutes_t = std::int32_t;

    static auto at(minutes_t hour, minutes_t minute = static_cast<minutes_t>(0)) -> Clock;

    auto plus(minutes_t minutes) const -> Clock;
    auto minus(minutes_t minutes) const -> Clock;

    auto operator==(const Clock& other) const -> bool;

    auto to_string() const -> std::string;
    explicit operator std::string() const;

private:
    explicit Clock(minutes_t total_minutes);

    minutes_t m_minutes;
};

namespace clock
{
    using minutes_t = Clock::minutes_t;

    inline auto at(minutes_t hour,
                   minutes_t minute = static_cast<minutes_t>(0)) -> Clock
    {
        return Clock::at(hour, minute);
    }
} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
