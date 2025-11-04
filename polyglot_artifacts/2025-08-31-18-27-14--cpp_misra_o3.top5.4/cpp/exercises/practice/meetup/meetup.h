#if !defined(MEETUP_H)
#define MEETUP_H

#include <chrono>
#include <cstdint>

namespace meetup {

// Weekday with the same ordering convention as std::chrono::weekday
enum class weekday : std::uint8_t {
    Sunday   = 0U,
    Monday   = 1U,
    Tuesday  = 2U,
    Wednesday= 3U,
    Thursday = 4U,
    Friday   = 5U,
    Saturday = 6U
};

enum class schedule : std::uint8_t {
    first  = 0U,
    second = 1U,
    third  = 2U,
    fourth = 3U,
    last,
    teenth
};

class scheduler {
public:
    scheduler(std::int32_t year, std::uint32_t month) noexcept;

    std::chrono::year_month_day get_day(weekday day_of_week, schedule sched) const;

private:
    std::int32_t  m_year;
    std::uint32_t m_month;
};

}  // namespace meetup

#endif // MEETUP_H
