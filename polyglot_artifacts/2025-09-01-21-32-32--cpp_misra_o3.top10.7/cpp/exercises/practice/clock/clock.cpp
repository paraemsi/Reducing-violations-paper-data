#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

/* static */ auto Clock::at(std::int32_t hour, std::int32_t minute) -> Clock
{
    const std::int32_t total((hour * static_cast<std::int32_t>(60)) + minute);
    return Clock{normalise(total)};
}

auto Clock::plus(std::int32_t minute_delta) const -> Clock
{
    const std::int32_t updated(normalise(total_minutes_ + minute_delta));
    return Clock{updated};
}

auto Clock::minus(std::int32_t minute_delta) const -> Clock
{
    /* Subtract the requested number of minutes.                     */
    const std::int32_t updated(normalise(total_minutes_ - minute_delta));
    return Clock{updated};
}

auto Clock::to_string() const -> std::string
{
    const std::int32_t hour(total_minutes_ / static_cast<std::int32_t>(60));
    const std::int32_t minute(total_minutes_ % static_cast<std::int32_t>(60));

    std::ostringstream oss;
    oss << std::setw(static_cast<std::streamsize>(2)) << std::setfill('0') << hour
        << ':' << std::setw(static_cast<std::streamsize>(2)) << std::setfill('0') << minute;
    return oss.str();
}

auto operator==(const Clock& lhs, const Clock& rhs) -> bool
{
    return (lhs.total_minutes_ == rhs.total_minutes_);
}

auto operator!=(const Clock& lhs, const Clock& rhs) -> bool
{
    return !(lhs == rhs);
}

/* static */ auto Clock::normalise(std::int32_t minutes) -> std::int32_t
{
    const std::int32_t minutes_in_day(static_cast<std::int32_t>(24) * static_cast<std::int32_t>(60));

    /* Ensure positive modulo behaviour even for negative inputs. */
    const std::int32_t result(((minutes % minutes_in_day) + minutes_in_day) % minutes_in_day);
    return result;
}

}  // namespace date_independent
