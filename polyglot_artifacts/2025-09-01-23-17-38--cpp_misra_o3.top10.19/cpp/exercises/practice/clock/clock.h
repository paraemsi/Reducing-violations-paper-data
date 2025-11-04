#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock final
{
public:
    static Clock at(std::int32_t hour, std::int32_t minute = 0) noexcept;

    Clock add_minutes(std::int32_t minutes) const noexcept;
    Clock plus(std::int32_t minutes) const noexcept;
    Clock minus(std::int32_t minutes) const noexcept;

    Clock& operator+=(std::int32_t minutes) noexcept;
    Clock& operator-=(std::int32_t minutes) noexcept;

    std::string to_string() const;
    operator std::string() const { return to_string(); }

private:
    explicit Clock(std::int32_t total_minutes) noexcept;

    std::int32_t m_total_minutes;  // range: 0‒1439

    friend bool operator==(const Clock& lhs, const Clock& rhs) noexcept;
    friend bool operator!=(const Clock& lhs, const Clock& rhs) noexcept;
};

Clock operator+(Clock lhs, std::int32_t minutes) noexcept;
Clock operator-(Clock lhs, std::int32_t minutes) noexcept;

// adaptor namespace expected by the tests
namespace clock
{
    inline Clock at(std::int32_t hour, std::int32_t minute = 0) noexcept
    {
        return Clock::at(hour, minute);
    }
}  // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
