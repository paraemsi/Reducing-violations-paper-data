#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock {
public:
    static clock at(std::int32_t hour, std::int32_t minute = 0) noexcept;

    clock plus(std::int32_t minutes) const noexcept;
    clock minus(std::int32_t minutes) const noexcept;

    std::string to_string() const;
    operator std::string() const;

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    explicit clock(std::int32_t total_minutes_since_midnight) noexcept;
    static std::int32_t normalize(std::int32_t total_minutes) noexcept;

    std::int32_t minutes_since_midnight_;
};

}  // namespace date_independent

#endif // CLOCK_H
