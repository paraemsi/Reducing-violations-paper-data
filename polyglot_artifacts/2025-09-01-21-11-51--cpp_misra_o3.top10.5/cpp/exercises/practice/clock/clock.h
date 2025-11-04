#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

/*
 * Clock class – represents a time-of-day independent of any date.
 * Implementation follows MISRA C++ rules enforced in the code base.
 */
class Clock
{
public:
    /* Factory that normalises input to the range 00:00-23:59 */
    static Clock at(std::int16_t hours,
                    std::int16_t minutes = static_cast<std::int16_t>(0));

    /* Return a new Clock that is |minutes| minutes from this one */
    Clock addMinutes(std::int32_t minutes) const;

    /* ISO-8601 style string "HH:MM" */
    std::string toString() const;

    /* API required by unit-tests */
    Clock plus(std::int32_t minutes) const;
    Clock minus(std::int32_t minutes) const;

    /* Implicit conversion – enables `std::string(clock)` */
    operator std::string() const;

    /* Symmetrical comparison operators (declared friend for private access) */
    friend bool operator==(const Clock& lhs, const Clock& rhs);
    friend bool operator!=(const Clock& lhs, const Clock& rhs);

private:
    explicit Clock(std::int32_t minutesSinceMidnight);

    std::int32_t m_minutes; /* minutes since midnight in range 0-1439 */
};

/* Operators must be declared at namespace scope to stay symmetrical */
bool operator==(const Clock& lhs, const Clock& rhs);
bool operator!=(const Clock& lhs, const Clock& rhs);

/* Convenience wrapper namespace to match expected test API               */
/* Placed in header so each translation unit sees the inline definitions. */
namespace clock
{
    inline Clock at(std::int16_t hours,
                    std::int16_t minutes = static_cast<std::int16_t>(0))
    {
        return Clock::at(hours, minutes);
    }
} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
