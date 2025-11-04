#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock final {
public:
    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

    clock plus(std::int32_t minutes_delta) const noexcept;
    clock minus(std::int32_t minutes_delta) const noexcept;

    std::string to_string() const;
    operator std::string() const;

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept {
        return (lhs.minutes_since_midnight_ == rhs.minutes_since_midnight_);
    }
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept {
        return (!(lhs == rhs));
    }

private:
    explicit clock(std::int32_t total_minutes) noexcept;

    static std::int32_t normalize(std::int32_t total_minutes) noexcept;

    static constexpr std::int32_t minutes_per_day =
        (static_cast<std::int32_t>(24) * static_cast<std::int32_t>(60));

    std::int32_t minutes_since_midnight_{ static_cast<std::int32_t>(0) };
};

}  // namespace date_independent

#endif // CLOCK_H
