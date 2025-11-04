#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock final {
public:
    using value_type = std::int32_t;

    static clock at(value_type hour, value_type minute = static_cast<value_type>(0)) noexcept;

    clock plus(value_type minutes) const noexcept;

    std::string to_string() const;

    explicit operator std::string() const
    {
        return to_string();
    }

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    explicit clock(value_type normalized_minutes) noexcept;

    static value_type normalize(value_type total_minutes) noexcept;

    static constexpr value_type kMinutesPerHour = static_cast<value_type>(60);
    static constexpr value_type kHoursPerDay = static_cast<value_type>(24);
    static constexpr value_type kMinutesPerDay =
        static_cast<value_type>((kHoursPerDay * kMinutesPerHour));

    value_type minutes_since_midnight_;
};

}  // namespace date_independent

#endif // CLOCK_H
