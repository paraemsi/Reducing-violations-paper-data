#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock
{
public:
    static clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0));

    /* return a new clock with the requested delta applied */
    clock plus(std::int32_t minutes) const;
    clock minus(std::int32_t minutes) const;

    [[nodiscard]] std::string to_string() const;
    operator std::string() const;          /* implicit conversion helper */

private:
    explicit clock(std::int32_t totalMinutes) noexcept;

    std::int32_t m_minutes; /* total minutes modulo one day */

    static constexpr std::int32_t MINUTES_PER_HOUR =
        static_cast<std::int32_t>(60);
    static constexpr std::int32_t MINUTES_PER_DAY =
        static_cast<std::int32_t>(24) * MINUTES_PER_HOUR;

    static std::int32_t normalize(std::int32_t minutes) noexcept;

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;
};

bool operator==(const clock& lhs, const clock& rhs) noexcept;
bool operator!=(const clock& lhs, const clock& rhs) noexcept;

} // namespace date_independent

#endif // CLOCK_H
