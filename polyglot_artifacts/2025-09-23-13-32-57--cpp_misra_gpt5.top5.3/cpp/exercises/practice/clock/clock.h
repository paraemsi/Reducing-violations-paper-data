#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock final {
public:
    explicit clock(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;
    clock plus(std::int32_t minutes) const noexcept;
    clock minus(std::int32_t minutes) const noexcept;
    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

    std::string str() const;
    explicit operator std::string() const;

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    std::int32_t minutes_since_midnight_;
};


clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

}  // namespace date_independent

#endif // CLOCK_H
