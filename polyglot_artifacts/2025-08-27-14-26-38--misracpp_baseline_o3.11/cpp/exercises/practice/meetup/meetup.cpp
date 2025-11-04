#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {
using boost::gregorian::date;
using boost::gregorian::days;
using boost::date_time::weekdays;
using weekday = boost::gregorian::greg_weekday;

// constructor
scheduler::scheduler(int year, int month) noexcept
    : year_{year}, month_{static_cast<unsigned>(month)} {}

// helper: nth weekday (1–4)
date scheduler::nth_weekday(int n, weekday wd) const {
    if (n < 1 || n > 4) {
        throw std::invalid_argument("nth_weekday: n must be 1..4");
    }

    date first_day(year_, month_, 1);
    int diff = static_cast<int>(wd.as_number()) - static_cast<int>(first_day.day_of_week());
    if (diff < 0) diff += 7;
    date result = first_day + days(diff + 7 * (n - 1));
    return result;
}

// helper: last weekday
date scheduler::last_weekday(weekday wd) const {
    date last_day(year_, month_, boost::gregorian::gregorian_calendar::end_of_month_day(year_, month_));
    int diff = static_cast<int>(last_day.day_of_week()) - static_cast<int>(wd.as_number());
    if (diff < 0) diff += 7;
    date result = last_day - days(diff);
    return result;
}

// helper: teenth weekday (13–19)
date scheduler::teenth_weekday(weekday wd) const {
    date first_teenth(year_, month_, 13);
    int diff = static_cast<int>(wd.as_number()) - static_cast<int>(first_teenth.day_of_week());
    if (diff < 0) diff += 7;
    return first_teenth + days(diff);
}

// --------------------------
// teenth functions
// --------------------------
date scheduler::monteenth() const noexcept {
    return teenth_weekday(weekday(weekdays::Monday));
}
date scheduler::tuesteenth() const noexcept {
    return teenth_weekday(weekday(weekdays::Tuesday));
}
date scheduler::wednesteenth() const noexcept {
    return teenth_weekday(weekday(weekdays::Wednesday));
}
date scheduler::thursteenth() const noexcept {
    return teenth_weekday(weekday(weekdays::Thursday));
}
date scheduler::friteenth() const noexcept {
    return teenth_weekday(weekday(weekdays::Friday));
}
date scheduler::saturteenth() const noexcept {
    return teenth_weekday(weekday(weekdays::Saturday));
}
date scheduler::sunteenth() const noexcept {
    return teenth_weekday(weekday(weekdays::Sunday));
}

// --------------------------
// first weekday
// --------------------------
date scheduler::first_monday() const noexcept {
    return nth_weekday(1, weekday(weekdays::Monday));
}
date scheduler::first_tuesday() const noexcept {
    return nth_weekday(1, weekday(weekdays::Tuesday));
}
date scheduler::first_wednesday() const noexcept {
    return nth_weekday(1, weekday(weekdays::Wednesday));
}
date scheduler::first_thursday() const noexcept {
    return nth_weekday(1, weekday(weekdays::Thursday));
}
date scheduler::first_friday() const noexcept {
    return nth_weekday(1, weekday(weekdays::Friday));
}
date scheduler::first_saturday() const noexcept {
    return nth_weekday(1, weekday(weekdays::Saturday));
}
date scheduler::first_sunday() const noexcept {
    return nth_weekday(1, weekday(weekdays::Sunday));
}

// --------------------------
// second weekday
// --------------------------
date scheduler::second_monday() const noexcept {
    return nth_weekday(2, weekday(weekdays::Monday));
}
date scheduler::second_tuesday() const noexcept {
    return nth_weekday(2, weekday(weekdays::Tuesday));
}
date scheduler::second_wednesday() const noexcept {
    return nth_weekday(2, weekday(weekdays::Wednesday));
}
date scheduler::second_thursday() const noexcept {
    return nth_weekday(2, weekday(weekdays::Thursday));
}
date scheduler::second_friday() const noexcept {
    return nth_weekday(2, weekday(weekdays::Friday));
}
date scheduler::second_saturday() const noexcept {
    return nth_weekday(2, weekday(weekdays::Saturday));
}
date scheduler::second_sunday() const noexcept {
    return nth_weekday(2, weekday(weekdays::Sunday));
}

// --------------------------
// third weekday
// --------------------------
date scheduler::third_monday() const noexcept {
    return nth_weekday(3, weekday(weekdays::Monday));
}
date scheduler::third_tuesday() const noexcept {
    return nth_weekday(3, weekday(weekdays::Tuesday));
}
date scheduler::third_wednesday() const noexcept {
    return nth_weekday(3, weekday(weekdays::Wednesday));
}
date scheduler::third_thursday() const noexcept {
    return nth_weekday(3, weekday(weekdays::Thursday));
}
date scheduler::third_friday() const noexcept {
    return nth_weekday(3, weekday(weekdays::Friday));
}
date scheduler::third_saturday() const noexcept {
    return nth_weekday(3, weekday(weekdays::Saturday));
}
date scheduler::third_sunday() const noexcept {
    return nth_weekday(3, weekday(weekdays::Sunday));
}

// --------------------------
// fourth weekday
// --------------------------
date scheduler::fourth_monday() const noexcept {
    return nth_weekday(4, weekday(weekdays::Monday));
}
date scheduler::fourth_tuesday() const noexcept {
    return nth_weekday(4, weekday(weekdays::Tuesday));
}
date scheduler::fourth_wednesday() const noexcept {
    return nth_weekday(4, weekday(weekdays::Wednesday));
}
date scheduler::fourth_thursday() const noexcept {
    return nth_weekday(4, weekday(weekdays::Thursday));
}
date scheduler::fourth_friday() const noexcept {
    return nth_weekday(4, weekday(weekdays::Friday));
}
date scheduler::fourth_saturday() const noexcept {
    return nth_weekday(4, weekday(weekdays::Saturday));
}
date scheduler::fourth_sunday() const noexcept {
    return nth_weekday(4, weekday(weekdays::Sunday));
}

// --------------------------
// last weekday
// --------------------------
date scheduler::last_monday() const noexcept {
    return last_weekday(weekday(weekdays::Monday));
}
date scheduler::last_tuesday() const noexcept {
    return last_weekday(weekday(weekdays::Tuesday));
}
date scheduler::last_wednesday() const noexcept {
    return last_weekday(weekday(weekdays::Wednesday));
}
date scheduler::last_thursday() const noexcept {
    return last_weekday(weekday(weekdays::Thursday));
}
date scheduler::last_friday() const noexcept {
    return last_weekday(weekday(weekdays::Friday));
}
date scheduler::last_saturday() const noexcept {
    return last_weekday(weekday(weekdays::Saturday));
}
date scheduler::last_sunday() const noexcept {
    return last_weekday(weekday(weekdays::Sunday));
}

} // namespace meetup
