#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    static auto at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) -> Clock;

    auto to_string() const -> std::string;

    auto plus(std::int32_t minutes) const -> Clock;
    auto minus(std::int32_t minutes) const -> Clock;

    auto operator==(Clock const& other) const -> bool;
    auto operator!=(Clock const& other) const -> bool;
    explicit operator std::string() const;

private:
    explicit Clock(std::int32_t total_minutes);

    static auto normalize(std::int32_t total_minutes) -> std::int32_t;

    std::int32_t m_total_minutes;
};
using clock = Clock;

/* Non-member arithmetic operators */
auto operator+(Clock const& clk, std::int32_t minutes) -> Clock;
auto operator-(Clock const& clk, std::int32_t minutes) -> Clock;

}  // namespace date_independent

#endif // CLOCK_H
