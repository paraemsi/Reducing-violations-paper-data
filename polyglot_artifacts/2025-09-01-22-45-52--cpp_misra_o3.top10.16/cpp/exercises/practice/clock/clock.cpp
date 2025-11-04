#include "clock.h"

#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

namespace {

constexpr std::int32_t modulo(std::int32_t value, std::int32_t mod)
{
    return ( ( (value % mod) + mod ) % mod );
}

} // unnamed namespace

Clock::Clock(std::int32_t totalMinutes)
    : totalMinutes_{ modulo(totalMinutes, Clock::minutesPerDay_) }
{
}

[[nodiscard]] Clock Clock::at(std::int32_t hours, std::int32_t minutes)
{
    std::int32_t total{ (hours * static_cast<std::int32_t>(60)) + minutes };
    return Clock(total);
}

[[nodiscard]] Clock Clock::plus(std::int32_t minutes) const
{
    return Clock(totalMinutes_ + minutes);
}

[[nodiscard]] Clock Clock::minus(std::int32_t minutes) const
{
    return Clock(totalMinutes_ - minutes);
}

std::string Clock::to_string() const
{
    std::int32_t hours{ totalMinutes_ / static_cast<std::int32_t>(60) };
    std::int32_t minutes{ totalMinutes_ % static_cast<std::int32_t>(60) };

    std::ostringstream oss{};
    oss << std::setfill(static_cast<char>('0')) << std::setw(2) << hours
        << ':' << std::setw(2) << minutes;
    return oss.str();
}

Clock::operator std::string() const
{
    return to_string();
}

bool operator==(const Clock& lhs, const Clock& rhs)
{
    return (lhs.totalMinutes_ == rhs.totalMinutes_);
}

bool operator!=(const Clock& lhs, const Clock& rhs)
{
    return (!(lhs == rhs));
}

std::ostream& operator<<(std::ostream& os, const Clock& clock)
{
    os << clock.to_string();
    return os;
}

}  // namespace date_independent
