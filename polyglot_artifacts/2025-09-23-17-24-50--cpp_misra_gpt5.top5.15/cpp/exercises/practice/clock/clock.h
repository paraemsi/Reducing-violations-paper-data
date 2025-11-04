#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock {
public:
    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

    clock plus(std::int32_t minutes) const;

    std::string str() const;

    explicit operator std::string() const
    {
        return this->str();
    }

    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    explicit clock(std::int32_t normalized_minutes);

    static std::int32_t normalize(std::int32_t total_minutes);

    static constexpr std::int32_t kHoursPerDay = static_cast<std::int32_t>(24);
    static constexpr std::int32_t kMinutesPerHour = static_cast<std::int32_t>(60);
    static constexpr std::int32_t kMinutesPerDay = (kHoursPerDay * kMinutesPerHour);

    std::int32_t minutes_from_midnight_;
};

}  // namespace date_independent

#endif // CLOCK_H
