#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <iosfwd>
#include <ostream>

namespace date_independent {

class Clock final
{
public:
    // Factory: create a clock at the supplied hour and minute
    static Clock at(std::int16_t hour,
                    std::int16_t minute = static_cast<std::int16_t>(0)) noexcept;

    // Return a new clock advanced by the given minutes
    [[nodiscard]] Clock plus(std::int16_t minute) const noexcept;

    // Return a new clock moved backward by the given minutes
    [[nodiscard]] Clock minus(std::int16_t minute) const noexcept;

    // "HH:MM" 24-hour format
    [[nodiscard]] std::string to_string() const;

    // implicit conversion so that std::string s{Clock{}} works
    [[nodiscard]] operator std::string() const;

    // Equality
    friend bool operator==(const Clock& lhs,
                           const Clock& rhs) noexcept;
    friend bool operator!=(const Clock& lhs,
                           const Clock& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& os,
                                    const Clock& clock);

private:
    explicit Clock(std::int16_t total_minutes) noexcept;

    static constexpr std::int16_t k_minutes_per_day =
        static_cast<std::int16_t>(24 * 60);

    static std::int16_t normalize(std::int32_t minute) noexcept;

    std::int16_t m_minutes_since_midnight;   // 0 – 1439
};

Clock operator+(const Clock& clock,
                std::int16_t minute) noexcept;

Clock operator-(const Clock& clock,
                std::int16_t minute) noexcept;

// provide date_independent::clock::at(...) façade expected by tests
namespace clock
{
inline Clock at(std::int16_t hour,
                std::int16_t minute = static_cast<std::int16_t>(0)) noexcept
{
    return Clock::at(hour, minute);
}
}  // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
