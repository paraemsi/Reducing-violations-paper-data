#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    /*
     * Factory method that builds a Clock for the supplied hour / minute.
     * Both arguments are interpreted modulo one day (24 h).
     */
    static Clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0));

    [[nodiscard]] std::string to_string() const;

    /*
     * Return a new Clock obtained by adding / subtracting the
     * specified minute count to / from this instance.
     */
    [[nodiscard]] Clock plus (std::int32_t minutes) const;
    [[nodiscard]] Clock minus(std::int32_t minutes) const;

    /* Implicit conversion so `std::string(clock::at(...))` works in tests. */
    operator std::string() const;

    /* Public constants so helper functions can use them without befriending. */
    static constexpr std::int32_t minutes_per_hour = static_cast<std::int32_t>(60);
    static constexpr std::int32_t hours_per_day    = static_cast<std::int32_t>(24);
    static constexpr std::int32_t minutes_per_day  =
        (hours_per_day * minutes_per_hour);

private:
    explicit Clock(std::int32_t total_minutes);

    /* Stored as an offset in minutes from 00:00, range 0‥1439. */
    std::int32_t m_total_minutes;

    /* Grant comparison operators access to internal state. */
    friend bool operator==(const Clock& lhs, const Clock& rhs);
    friend bool operator!=(const Clock& lhs, const Clock& rhs);
};

/* Helper namespace expected by the tests */
namespace clock
{
    /* Re-export the main Clock type and a forwarding factory wrapper. */
    using ::date_independent::Clock;

    inline Clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0))
    {
        return Clock::at(hour, minute);
    }
}  // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
