#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <iosfwd>

namespace date_independent {

class clock
{
public:
    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

    clock& plus(std::int32_t minute) noexcept;
    clock& minus(std::int32_t minute) noexcept;

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] explicit operator std::string() const { return to_string(); }

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const clock& clock_obj);

private:
    explicit clock(std::int32_t total_minutes) noexcept;

    std::int32_t _minutes; // minutes since midnight, range 0-1439 inclusive

    static const std::int32_t minutes_per_day{static_cast<std::int32_t>(1440)};
    static std::int32_t normalise(std::int32_t total_minutes) noexcept;
};

}  // namespace date_independent

#endif // CLOCK_H
