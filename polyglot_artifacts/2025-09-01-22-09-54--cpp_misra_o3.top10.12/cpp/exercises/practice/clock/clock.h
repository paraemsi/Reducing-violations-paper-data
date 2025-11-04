#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock
{
public:
    /* Factory that builds a clock set to the supplied hour and minute */
    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

    /* Add minutes (may be negative) and return a new clock instance */
    [[nodiscard]] clock plus(std::int32_t minute_delta) const;

    /* Subtract minutes (may be negative) and return a new clock instance */
    [[nodiscard]] clock minus(std::int32_t minute_delta) const;

    /* Return the clock time formatted as HH:MM */
    [[nodiscard]] std::string to_string() const;

    /* Implicit conversion used by the tests */
    [[nodiscard]] operator std::string() const { return to_string(); }

    /* Equality – implemented as non-member friend to respect symmetry */
    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    explicit clock(std::int32_t total_minutes);

    std::int32_t minutes_since_midnight_;
    static constexpr std::int32_t minutes_per_day{ static_cast<std::int32_t>(24 * 60) };

    /* Normalise any minute count into the range [0, minutes_per_day) */
    static std::int32_t normalise(std::int32_t total_minutes);
};

}  // namespace date_independent

#endif // CLOCK_H
