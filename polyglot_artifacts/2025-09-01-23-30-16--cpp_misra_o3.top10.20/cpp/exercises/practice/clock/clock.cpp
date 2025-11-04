#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
    constexpr std::int32_t kMinutesPerHour = static_cast<std::int32_t>(60);
    constexpr std::int32_t kMinutesPerDay  = static_cast<std::int32_t>(24) * kMinutesPerHour;

    // Bring any minute count into the canonical range [0, 1439].
    inline std::int32_t canonicalise(std::int32_t minutes) noexcept
    {
        std::int32_t result = minutes % kMinutesPerDay;
        if(result < static_cast<std::int32_t>(0))
        {
            result += kMinutesPerDay;
        }
        return result;
    }
}  // unnamed namespace

clock::clock(std::int32_t canonical_minutes) noexcept
: m_minutes(canonical_minutes)
{
    // Assumes argument already canonical.
}

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    std::int32_t total_minutes = (hour * kMinutesPerHour) + minute;
    return clock(canonicalise(total_minutes));
}

clock clock::plus(std::int32_t minutes) const noexcept
{
    return clock(canonicalise(m_minutes + minutes));
}

std::string clock::to_string() const
{
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << (m_minutes / kMinutesPerHour)
        << ':'
        << std::setfill('0')
        << std::setw(2) << (m_minutes % kMinutesPerHour);
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.m_minutes == rhs.m_minutes);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept
{
    return !(lhs == rhs);
}

}  // namespace date_independent
