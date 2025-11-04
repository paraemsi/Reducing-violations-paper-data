#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

// A clock that handles times without dates.
// Supports creating a time, adding/subtracting minutes, comparison, and string formatting "HH:MM".
class clock final {
public:
    // Factory to create a clock at hour:minute. Minutes may be outside 0..59; values are normalized to 24h.
    static auto at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept -> clock;

    // Return a new clock advanced by the given number of minutes (can be negative).
    auto plus(std::int32_t minutes) const noexcept -> clock;

    // Return a new clock moved back by the given number of minutes (can be negative).
    auto minus(std::int32_t minutes) const noexcept -> clock;

    // Format as "HH:MM".
    auto to_string() const -> std::string;

    // Implicit conversion to std::string to interoperate with tests that do string(clock).
    operator std::string() const;


    ~clock() = default;

    // Equality: two clocks are equal if they represent the same time of day.
    friend auto operator==(const clock& lhs, const clock& rhs) noexcept -> bool
    {
        return (lhs.m_total_minutes == rhs.m_total_minutes);
    }

    friend auto operator!=(const clock& lhs, const clock& rhs) noexcept -> bool
    {
        return (!(lhs == rhs));
    }

private:
    explicit clock(std::int32_t total_minutes_normalized) noexcept : m_total_minutes(total_minutes_normalized) {}

    static auto normalize_minutes(std::int32_t total_minutes) noexcept -> std::int32_t;

    std::int32_t m_total_minutes;

    static constexpr std::int32_t kMinutesPerHour = static_cast<std::int32_t>(60);
    static constexpr std::int32_t kHoursPerDay = static_cast<std::int32_t>(24);
    static constexpr std::int32_t kMinutesPerDay = static_cast<std::int32_t>((kHoursPerDay * kMinutesPerHour));
};

// Free function to obtain the string representation, for convenience and potential test expectations.
auto to_string(const clock& c) -> std::string;

}  // namespace date_independent

#endif // CLOCK_H
