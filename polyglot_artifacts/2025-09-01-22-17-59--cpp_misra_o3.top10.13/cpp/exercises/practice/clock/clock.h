#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock
{
public:
    /* Factory function to create a clock at the given hour and minute. */
    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

    /* Return a new Clock advanced by the supplied number of minutes. */
    [[nodiscard]] clock add_minutes(std::int32_t minutes) const;

    /* Return a new Clock moved back by the supplied number of minutes. */
    [[nodiscard]] clock subtract_minutes(std::int32_t minutes) const;

    /* Provide exercism-expected aliases. */
    [[nodiscard]] clock plus(std::int32_t minutes) const { return add_minutes(minutes); }
    [[nodiscard]] clock minus(std::int32_t minutes) const { return subtract_minutes(minutes); }

    /* Return the time in "HH:MM" 24-hour format. */
    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] operator std::string() const { return to_string(); }

    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    explicit clock(std::int32_t total_minutes);   /* total minutes since 00:00, normalised */

    std::int32_t m_total_minutes;                 /* range 0-1439 inclusive */
};

}  // namespace date_independent

#endif // CLOCK_H
