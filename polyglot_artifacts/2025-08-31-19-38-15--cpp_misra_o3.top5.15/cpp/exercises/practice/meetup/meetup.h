#if !defined(MEETUP_H)
#define MEETUP_H

#include <chrono>
#include <cstdint>

namespace meetup {

/* Enumeration describing the required occurrence within the month */
enum class schedule : std::uint8_t {
    first,
    second,
    third,
    fourth,
    last,
    teenth
};

/*  Return the calendar day matching the requested weekday and schedule
 *  for the supplied year / month.
 */
auto day(const std::chrono::year_month& ym,
         const std::chrono::weekday&     wd,
         schedule                        recurrence) -> std::chrono::year_month_day;

}  // namespace meetup

#endif // MEETUP_H
