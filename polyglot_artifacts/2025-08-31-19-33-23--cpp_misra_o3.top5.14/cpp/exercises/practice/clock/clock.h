#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    static Clock at(std::int32_t hour, std::int32_t minute = 0) noexcept;

    Clock plus(std::int32_t minutes) const noexcept;
    Clock minus(std::int32_t minutes) const noexcept;

    std::string to_string() const;
    /* Allow implicit conversion to std::string for test convenience */
    explicit operator std::string() const { return to_string(); }

    bool operator==(const Clock& other) const noexcept;
    bool operator!=(const Clock& other) const noexcept;

private:
    explicit Clock(std::int32_t total_minutes) noexcept;
    std::int32_t m_total_minutes; /* Minutes elapsed since 00:00, range 0..1439 */
};

/* Alias required by tests: date_independent::clock */
using clock = Clock;

}  // namespace date_independent

#endif // CLOCK_H
