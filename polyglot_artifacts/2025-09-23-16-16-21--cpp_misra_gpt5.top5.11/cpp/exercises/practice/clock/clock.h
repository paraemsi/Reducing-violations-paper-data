#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock final {
public:
    using minute_type = std::int32_t;

    static clock at(minute_type hour, minute_type minute = minute_type{0}) noexcept;

    clock plus(minute_type minutes) const noexcept;
    clock minus(minute_type minutes) const noexcept;

    std::string to_string() const;

    explicit operator std::string() const;

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    explicit clock(minute_type normalized_minutes) noexcept;
    static minute_type normalize(minute_type total_minutes) noexcept;

    minute_type minutes_since_midnight_;
};

}  // namespace date_independent

#endif // CLOCK_H
