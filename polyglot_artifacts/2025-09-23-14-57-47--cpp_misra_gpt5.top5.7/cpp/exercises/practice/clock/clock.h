#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock {
public:
    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

    clock plus(std::int32_t minutes) const noexcept;
    clock minus(std::int32_t minutes) const noexcept;

    std::string to_string() const;
    operator std::string() const;

    bool operator==(const clock& other) const noexcept;
    bool operator!=(const clock& other) const noexcept;

private:
    explicit clock(std::int32_t normalized_minutes) noexcept;

    static std::int32_t normalize_minutes(std::int32_t minutes_total) noexcept;

    std::int32_t minutes_since_midnight_;
};

}  // namespace date_independent

#endif // CLOCK_H
