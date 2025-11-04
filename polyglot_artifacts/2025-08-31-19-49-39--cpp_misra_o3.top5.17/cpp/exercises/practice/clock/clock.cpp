#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

Clock::Clock(std::int32_t total_minutes) noexcept
    : minutes_{static_cast<std::int32_t>(( ( total_minutes % kMinutesPerDay ) + kMinutesPerDay ) % kMinutesPerDay)}
{
}

Clock Clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    std::int32_t const total{(hour * static_cast<std::int32_t>(60)) + minute};
    return Clock{total};
}

Clock Clock::plus(std::int32_t minute) const noexcept
{
    /* Parenthesise the addition to make operator precedence explicit
       in accordance with the MISRA “parentheses” rule. */
    return Clock{(minutes_ + minute)};
}

Clock Clock::minus(std::int32_t minute) const noexcept
{
    /* Parenthesise the subtraction to make operator precedence explicit
       in accordance with the MISRA “parentheses” rule. */
    return Clock{(minutes_ - minute)};
}

bool Clock::operator==(const Clock& other) const noexcept
{
    std::int32_t const normalized_this{((minutes_ % kMinutesPerDay) + kMinutesPerDay) % kMinutesPerDay};
    std::int32_t const normalized_other{((other.minutes_ % kMinutesPerDay) + kMinutesPerDay) % kMinutesPerDay};
    return (normalized_this == normalized_other);
}

std::string Clock::to_string() const
{
    std::int32_t const norm_minutes{((minutes_ % kMinutesPerDay) + kMinutesPerDay) % kMinutesPerDay};
    std::int32_t const hour{norm_minutes / static_cast<std::int32_t>(60)};
    std::int32_t const minute{norm_minutes % static_cast<std::int32_t>(60)};

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ':' << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}

}  // namespace date_independent
