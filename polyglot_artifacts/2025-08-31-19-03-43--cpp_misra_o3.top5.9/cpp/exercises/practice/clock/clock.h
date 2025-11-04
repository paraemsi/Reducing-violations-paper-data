#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

class clock final
{
public:
    static clock at(std::int32_t hour, std::int32_t minute = 0) noexcept;

    clock& plus(std::int32_t minute) noexcept;
    clock& minus(std::int32_t minute) noexcept;

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] operator std::string() const
    {
        return to_string();
    }

    bool operator==(const clock& other) const noexcept;

private:
    explicit clock(std::int32_t total_minutes) noexcept;

    std::int32_t minutes_since_midnight_{0};
    static constexpr std::int32_t minutes_in_day{(24 * 60)};
};

}  // namespace date_independent

#endif // CLOCK_H
