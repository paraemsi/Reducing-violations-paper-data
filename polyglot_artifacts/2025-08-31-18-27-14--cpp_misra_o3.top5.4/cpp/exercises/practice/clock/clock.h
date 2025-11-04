#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    // Factory method: create a Clock at the specified hour and minute
    static Clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

    // Return a new Clock that is this time plus the given minutes
    [[nodiscard]] Clock plus(std::int32_t minutes) const;

    // Return a new Clock that is this time minus the given minutes
    [[nodiscard]] Clock minus(std::int32_t minutes) const;

    // Return a "HH:MM" string representation
    std::string to_string() const;
    explicit operator std::string() const;

    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const;

private:
    explicit Clock(std::int32_t total_minutes);

    // Minutes since 00:00, always in the range [0, kMinutesPerDay - 1]
    std::int32_t minutes_;
    static constexpr std::int32_t kMinutesPerDay =
        static_cast<std::int32_t>(24) * static_cast<std::int32_t>(60);
};

    // Provide the lowercase alias expected by the tests
    using clock = Clock;

}  // namespace date_independent

#endif // CLOCK_H
