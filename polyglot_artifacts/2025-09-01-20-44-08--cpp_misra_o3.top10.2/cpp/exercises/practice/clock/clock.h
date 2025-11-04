#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock
{
public:
    /* Factory method to create a clock at the specified hour / minute */
    static clock at(std::int32_t hour, std::int32_t minute = 0) noexcept;

    /* Return a new clock that is this clock plus the supplied minutes
       (minutes may be negative). */
    clock plus(std::int32_t minutes) const noexcept;

    /* Obtain a string representation in "HH:MM" 24-hour format */
    std::string to_string() const;

    /* Implicit conversion to std::string for test expectations */
    operator std::string() const { return to_string(); }

    /* Equality – implemented as symmetrical non-member operators */
    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    explicit clock(std::int32_t total_minutes) noexcept;

    std::int32_t m_total_minutes;   /* minutes since 00:00, always 0-1439 */
};

}  // namespace date_independent

#endif // CLOCK_H
