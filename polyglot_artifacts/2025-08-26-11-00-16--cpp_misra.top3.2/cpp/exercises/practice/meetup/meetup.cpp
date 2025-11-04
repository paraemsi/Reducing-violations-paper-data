#include "meetup.h"
#include <ctime>
#include <stdexcept>

namespace meetup {

namespace {

constexpr day_t days_in_month(year_t year, month_t month)
{
    switch(month) {
        case 1U: return 31U;
        case 2U:
            if(((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) {
                return 29U;
            } else {
                return 28U;
            }
        case 3U: return 31U;
        case 4U: return 30U;
        case 5U: return 31U;
        case 6U: return 30U;
        case 7U: return 31U;
        case 8U: return 31U;
        case 9U: return 30U;
        case 10U: return 31U;
        case 11U: return 30U;
        case 12U: return 31U;
        default: throw std::invalid_argument("Invalid month");
    }
}

// Returns 0=Sunday, 1=Monday, ..., 6=Saturday
std::uint8_t weekday_of(year_t year, month_t month, day_t day)
{
    std::tm timeinfo = {};
    timeinfo.tm_year = static_cast<int>(year - 1900);
    timeinfo.tm_mon = static_cast<int>(month - 1U);
    timeinfo.tm_mday = static_cast<int>(day);
    timeinfo.tm_hour = 12;

    std::time_t t = std::mktime(&timeinfo);
    if(t == static_cast<std::time_t>(-1)) {
        throw std::runtime_error("Invalid date");
    }
    return static_cast<std::uint8_t>(timeinfo.tm_wday);
}

day_t find_teenth(year_t year, month_t month, std::uint8_t weekday)
{
    for(day_t d = 13U; d <= 19U; ++d) {
        if(weekday_of(year, month, d) == weekday) {
            return d;
        }
    }
    throw std::runtime_error("No teenth day found");
}

day_t find_nth(year_t year, month_t month, std::uint8_t weekday, std::uint8_t n)
{
    day_t count = 0U;
    day_t days = days_in_month(year, month);
    for(day_t d = 1U; d <= days; ++d) {
        if(weekday_of(year, month, d) == weekday) {
            ++count;
            if(count == n) {
                return d;
            }
        }
    }
    throw std::runtime_error("No such weekday in month");
}

day_t find_last(year_t year, month_t month, std::uint8_t weekday)
{
    day_t days = days_in_month(year, month);
    for(day_t d = days; d >= 1U; --d) {
        if(weekday_of(year, month, d) == weekday) {
            return d;
        }
    }
    throw std::runtime_error("No such weekday in month");
}

} // anonymous namespace

// Helper to map function name to weekday index
static std::uint8_t weekday_index(const char* name)
{
    if(name[0] == 'm') return 1U; // monday
    if(name[0] == 't' && name[1] == 'u') return 2U; // tuesday
    if(name[0] == 'w') return 3U; // wednesday
    if(name[0] == 't' && name[1] == 'h') return 4U; // thursday
    if(name[0] == 'f') return 5U; // friday
    if(name[0] == 's' && name[1] == 'a') return 6U; // saturday
    if(name[0] == 's' && name[1] == 'u') return 0U; // sunday
    throw std::invalid_argument("Invalid weekday name");
}

scheduler::scheduler(year_t year, month_t month)
    : m_month(month), m_year(year)
{
}

#define MEETUP_TEENTH_METHOD(NAME, IDX) \
    day_t scheduler::NAME##teenth() const { \
        return find_teenth(m_year, m_month, IDX); \
    }

#define MEETUP_ORDINAL_METHOD(ORDINAL, N) \
    day_t scheduler::ORDINAL##_monday() const { return find_nth(m_year, m_month, 1U, N); } \
    day_t scheduler::ORDINAL##_tuesday() const { return find_nth(m_year, m_month, 2U, N); } \
    day_t scheduler::ORDINAL##_wednesday() const { return find_nth(m_year, m_month, 3U, N); } \
    day_t scheduler::ORDINAL##_thursday() const { return find_nth(m_year, m_month, 4U, N); } \
    day_t scheduler::ORDINAL##_friday() const { return find_nth(m_year, m_month, 5U, N); } \
    day_t scheduler::ORDINAL##_saturday() const { return find_nth(m_year, m_month, 6U, N); } \
    day_t scheduler::ORDINAL##_sunday() const { return find_nth(m_year, m_month, 0U, N); }

#define MEETUP_LAST_METHOD \
    day_t scheduler::last_monday() const { return find_last(m_year, m_month, 1U); } \
    day_t scheduler::last_tuesday() const { return find_last(m_year, m_month, 2U); } \
    day_t scheduler::last_wednesday() const { return find_last(m_year, m_month, 3U); } \
    day_t scheduler::last_thursday() const { return find_last(m_year, m_month, 4U); } \
    day_t scheduler::last_friday() const { return find_last(m_year, m_month, 5U); } \
    day_t scheduler::last_saturday() const { return find_last(m_year, m_month, 6U); } \
    day_t scheduler::last_sunday() const { return find_last(m_year, m_month, 0U); }

MEETUP_TEENTH_METHOD(mon, 1U)
MEETUP_TEENTH_METHOD(tues, 2U)
MEETUP_TEENTH_METHOD(wednes, 3U)
MEETUP_TEENTH_METHOD(thur, 4U)
MEETUP_TEENTH_METHOD(fri, 5U)
MEETUP_TEENTH_METHOD(satur, 6U)
MEETUP_TEENTH_METHOD(sun, 0U)

MEETUP_ORDINAL_METHOD(first, 1U)
MEETUP_ORDINAL_METHOD(second, 2U)
MEETUP_ORDINAL_METHOD(third, 3U)
MEETUP_ORDINAL_METHOD(fourth, 4U)
MEETUP_LAST_METHOD

}  // namespace meetup
