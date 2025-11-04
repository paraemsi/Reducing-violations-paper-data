#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
    constexpr minute_type MINUTES_IN_DAY =
        static_cast<minute_type>(24 * 60); /* 1440 */
}

/* static */ Clock Clock::at(minute_type hour,
                             minute_type minute) noexcept
{
    minute_type total =
        static_cast<minute_type>((hour * static_cast<minute_type>(60)) + minute);

    total = static_cast<minute_type>(total % MINUTES_IN_DAY);
    if (total < static_cast<minute_type>(0)) {
        total =
            static_cast<minute_type>(total + MINUTES_IN_DAY);
    }

    return Clock{total};
}

Clock::Clock(minute_type total_minutes) noexcept
    : minutes_since_midnight_{
          static_cast<minute_type>(total_minutes % MINUTES_IN_DAY)}
{
    if (minutes_since_midnight_ < static_cast<minute_type>(0)) {
        minutes_since_midnight_ =
            static_cast<minute_type>(minutes_since_midnight_ +
                                     MINUTES_IN_DAY);
    }
}

Clock Clock::plus(minute_type minutes) const noexcept
{
    minute_type combined =
        static_cast<minute_type>(minutes_since_midnight_ + minutes);

    combined = static_cast<minute_type>(combined % MINUTES_IN_DAY);
    if (combined < static_cast<minute_type>(0)) {
        combined = static_cast<minute_type>(combined + MINUTES_IN_DAY);
    }

    return Clock{combined};
}

Clock Clock::minus(minute_type minutes) const noexcept
{
    return plus(static_cast<minute_type>(-minutes));
}

std::string Clock::to_string() const
{
    minute_type hour =
        static_cast<minute_type>(minutes_since_midnight_ /
                                 static_cast<minute_type>(60));
    minute_type minute =
        static_cast<minute_type>(minutes_since_midnight_ %
                                 static_cast<minute_type>(60));

    std::ostringstream os{};
    os << std::setfill('0') << std::setw(2) << hour << ':'
       << std::setw(2) << minute;
    return os.str();
}

bool operator==(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.minutes_since_midnight_ == rhs.minutes_since_midnight_);
}

bool operator!=(const Clock& lhs, const Clock& rhs) noexcept
{
    return !(lhs == rhs);
}

}  // namespace date_independent
