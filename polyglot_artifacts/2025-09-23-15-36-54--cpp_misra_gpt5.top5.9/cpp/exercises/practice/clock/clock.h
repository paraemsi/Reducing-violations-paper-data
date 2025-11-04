#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <ostream>

namespace date_independent {

class clock {
public:
    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;
    clock plus(std::int32_t minutes) const noexcept;
    clock minus(std::int32_t minutes) const noexcept;
    operator std::string() const;

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const clock& rhs);

private:
    explicit clock(std::int32_t minute_of_day) noexcept;
    static std::int32_t normalize(std::int32_t total_minutes) noexcept;

    std::int32_t m_minute_of_day;
};

}  // namespace date_independent

#endif // CLOCK_H
