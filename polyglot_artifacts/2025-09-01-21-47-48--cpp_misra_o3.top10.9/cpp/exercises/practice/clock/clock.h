#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    /* Factory: create a clock at the given hour and minute            */
    static Clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0));

    /* Return a new clock `minutes` past this one                      */
    [[nodiscard]] Clock plus(std::int32_t minutes) const;

    /* Return a new clock `minutes` before this one                    */
    [[nodiscard]] Clock minus(std::int32_t minutes) const;

    /* Format as "HH:MM"                                               */
    [[nodiscard]] std::string to_string() const;

    /* Implicit conversion to std::string so tests can call
       std::string(date_independent::clock::at(...))                   */
    [[nodiscard]] operator std::string() const;

private:
    explicit Clock(std::int32_t totalMinutes);

    std::int32_t m_totalMinutes;          /* total minutes since 00:00 */

    static std::int32_t normalize(std::int32_t minutes);

    friend bool operator==(const Clock& lhs, const Clock& rhs);
    friend bool operator!=(const Clock& lhs, const Clock& rhs);
};

/* Symmetrical equality operators – non-member as required             */
bool operator==(const Clock& lhs, const Clock& rhs);
bool operator!=(const Clock& lhs, const Clock& rhs);

/* Convenience wrapper namespace expected by the tests                */
namespace clock
{
    /* Forward to Clock factory                                        */
    inline Clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0))
    {
        return Clock::at(hour, minute);
    }
}   /* namespace clock */

}  // namespace date_independent

#endif // CLOCK_H
