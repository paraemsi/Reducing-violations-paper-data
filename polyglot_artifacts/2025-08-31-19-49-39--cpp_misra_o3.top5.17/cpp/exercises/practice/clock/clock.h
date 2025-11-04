#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    static Clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

    Clock plus(std::int32_t minute) const noexcept;
    Clock minus(std::int32_t minute) const noexcept;

    [[nodiscard]] std::string to_string() const;

    bool operator==(const Clock& other) const noexcept;

private:
    explicit Clock(std::int32_t total_minutes) noexcept;

    std::int32_t minutes_{static_cast<std::int32_t>(0)};
    static constexpr std::int32_t kMinutesPerDay{static_cast<std::int32_t>(1440)};
};
namespace clock
{
inline Clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept
{
    return Clock::at(hour, minute);
}
}  // namespace clock

inline std::string string(const Clock& clk) noexcept
{
    return clk.to_string();
}

}  // namespace date_independent

#endif // CLOCK_H
