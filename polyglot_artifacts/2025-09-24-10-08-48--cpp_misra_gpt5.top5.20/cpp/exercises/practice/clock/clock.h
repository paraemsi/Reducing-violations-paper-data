#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock {
public:
    explicit clock(std::int32_t hour, std::int32_t minute = 0);
    static clock at(std::int32_t hour, std::int32_t minute = 0);
    clock plus(std::int32_t minutes) const;
    std::string to_string() const;
    operator std::string() const;

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    static constexpr std::int32_t minutes_per_day = (24 * 60);
    static std::int32_t normalize(std::int32_t total) noexcept;

    std::int32_t minutes_;  // minutes since midnight, normalized to [0, minutes_per_day)
};


}  // namespace date_independent

#endif // CLOCK_H
