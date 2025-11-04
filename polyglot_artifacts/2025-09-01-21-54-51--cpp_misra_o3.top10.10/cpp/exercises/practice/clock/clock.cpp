#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

Clock Clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    const std::int32_t minutes_in_day{static_cast<std::int32_t>(60 * 24)};
    std::int32_t total_minutes{(hour * static_cast<std::int32_t>(60)) + minute};

    total_minutes = (total_minutes % minutes_in_day);
    if(total_minutes < static_cast<std::int32_t>(0)) {
        total_minutes += minutes_in_day;
    }

    return Clock{total_minutes};
}

Clock Clock::plus(std::int32_t minute_delta) const noexcept
{
    Clock result{m_minute_of_day};
    result.m_minute_of_day += minute_delta;
    result.normalize();
    return result;
}

Clock Clock::minus(std::int32_t minute_delta) const noexcept
{
    Clock result{m_minute_of_day};
    result.m_minute_of_day -= minute_delta;
    result.normalize();
    return result;
}

std::string Clock::to_string() const
{
    std::ostringstream oss{};
    const std::int32_t hour{m_minute_of_day / static_cast<std::int32_t>(60)};
    const std::int32_t minute{m_minute_of_day % static_cast<std::int32_t>(60)};

    oss << std::setfill('0') << std::setw(2) << hour << ':'
        << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}


bool operator==(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.m_minute_of_day == rhs.m_minute_of_day);
}

bool operator!=(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.m_minute_of_day != rhs.m_minute_of_day);
}

Clock::Clock(std::int32_t minute_of_day) noexcept
    : m_minute_of_day{minute_of_day}
{
    normalize();
}

void Clock::normalize() noexcept
{
    const std::int32_t minutes_in_day{static_cast<std::int32_t>(60 * 24)};
    m_minute_of_day = (m_minute_of_day % minutes_in_day);
    if(m_minute_of_day < static_cast<std::int32_t>(0)) {
        m_minute_of_day += minutes_in_day;
    }
}

}  // namespace date_independent
