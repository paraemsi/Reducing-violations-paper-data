#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {
    // Map our enum to weekday number (0=Sunday ... 6=Saturday)
    constexpr int to_wday(weekday wd) {
        switch (wd) {
            case weekday::Sunday:    return 0;
            case weekday::Monday:    return 1;
            case weekday::Tuesday:   return 2;
            case weekday::Wednesday: return 3;
            case weekday::Thursday:  return 4;
            case weekday::Friday:    return 5;
            case weekday::Saturday:  return 6;
        }
        return 0;
    }

    constexpr unsigned nth_from_schedule(schedule s) {
        switch (s) {
            case schedule::first:  return 1u;
            case schedule::second: return 2u;
            case schedule::third:  return 3u;
            case schedule::fourth: return 4u;
            default: return 0u; // for last/teenth we don't use this
        }
    }
} // namespace

scheduler::scheduler(int year, int month)
    : year_{year},
      month_{month} {
    if (month_ < 1 || month_ > 12) {
        throw std::invalid_argument("Invalid month (must be 1..12)");
    }
}

meetup::date scheduler::day(weekday wd, schedule s) const {
    using namespace boost::gregorian;

    const int desired = to_wday(wd);

    if (s == schedule::teenth) {
        for (unsigned d = 13; d <= 19; ++d) {
            date ymd{year_, month_, d};
            if (ymd.day_of_week().as_number() == desired) {
                return ymd;
            }
        }
        throw std::logic_error("No teenth weekday found (should be unreachable)");
    }

    if (s == schedule::last) {
        unsigned last_dom = gregorian_calendar::end_of_month_day(year_, month_);
        date last{year_, month_, last_dom};
        unsigned diff = (last.day_of_week().as_number() + 7u - static_cast<unsigned>(desired)) % 7u;
        return date{year_, month_, last_dom - diff};
    }

    const unsigned n = nth_from_schedule(s);
    if (n < 1 || n > 4) {
        throw std::invalid_argument("Invalid schedule for nth occurrence");
    }

    date first{year_, month_, 1};
    unsigned offset = (static_cast<unsigned>(desired) + 7u - first.day_of_week().as_number()) % 7u;
    unsigned d = 1u + offset + 7u * (n - 1u);
    unsigned last_dom = gregorian_calendar::end_of_month_day(year_, month_);
    if (d > last_dom) {
        throw std::logic_error("Computed date fell outside the target month");
    }
    return date{year_, month_, d};
}

date scheduler::monteenth() const { return day(weekday::Monday,    schedule::teenth); }
date scheduler::tuesteenth() const { return day(weekday::Tuesday,   schedule::teenth); }
date scheduler::wednesteenth() const { return day(weekday::Wednesday, schedule::teenth); }
date scheduler::thursteenth() const { return day(weekday::Thursday,  schedule::teenth); }
date scheduler::friteenth() const { return day(weekday::Friday,    schedule::teenth); }
date scheduler::saturteenth() const { return day(weekday::Saturday,  schedule::teenth); }
date scheduler::sunteenth() const { return day(weekday::Sunday,    schedule::teenth); }

date scheduler::first_monday() const { return day(weekday::Monday,    schedule::first); }
date scheduler::first_tuesday() const { return day(weekday::Tuesday,   schedule::first); }
date scheduler::first_wednesday() const { return day(weekday::Wednesday, schedule::first); }
date scheduler::first_thursday() const { return day(weekday::Thursday,  schedule::first); }
date scheduler::first_friday() const { return day(weekday::Friday,    schedule::first); }
date scheduler::first_saturday() const { return day(weekday::Saturday,  schedule::first); }
date scheduler::first_sunday() const { return day(weekday::Sunday,    schedule::first); }

date scheduler::second_monday() const { return day(weekday::Monday,    schedule::second); }
date scheduler::second_tuesday() const { return day(weekday::Tuesday,   schedule::second); }
date scheduler::second_wednesday() const { return day(weekday::Wednesday, schedule::second); }
date scheduler::second_thursday() const { return day(weekday::Thursday,  schedule::second); }
date scheduler::second_friday() const { return day(weekday::Friday,    schedule::second); }
date scheduler::second_saturday() const { return day(weekday::Saturday,  schedule::second); }
date scheduler::second_sunday() const { return day(weekday::Sunday,    schedule::second); }

date scheduler::third_monday() const { return day(weekday::Monday,    schedule::third); }
date scheduler::third_tuesday() const { return day(weekday::Tuesday,   schedule::third); }
date scheduler::third_wednesday() const { return day(weekday::Wednesday, schedule::third); }
date scheduler::third_thursday() const { return day(weekday::Thursday,  schedule::third); }
date scheduler::third_friday() const { return day(weekday::Friday,    schedule::third); }
date scheduler::third_saturday() const { return day(weekday::Saturday,  schedule::third); }
date scheduler::third_sunday() const { return day(weekday::Sunday,    schedule::third); }

date scheduler::fourth_monday() const { return day(weekday::Monday,    schedule::fourth); }
date scheduler::fourth_tuesday() const { return day(weekday::Tuesday,   schedule::fourth); }
date scheduler::fourth_wednesday() const { return day(weekday::Wednesday, schedule::fourth); }
date scheduler::fourth_thursday() const { return day(weekday::Thursday,  schedule::fourth); }
date scheduler::fourth_friday() const { return day(weekday::Friday,    schedule::fourth); }
date scheduler::fourth_saturday() const { return day(weekday::Saturday,  schedule::fourth); }
date scheduler::fourth_sunday() const { return day(weekday::Sunday,    schedule::fourth); }

date scheduler::last_monday() const { return day(weekday::Monday,    schedule::last); }
date scheduler::last_tuesday() const { return day(weekday::Tuesday,   schedule::last); }
date scheduler::last_wednesday() const { return day(weekday::Wednesday, schedule::last); }
date scheduler::last_thursday() const { return day(weekday::Thursday,  schedule::last); }
date scheduler::last_friday() const { return day(weekday::Friday,    schedule::last); }
date scheduler::last_saturday() const { return day(weekday::Saturday,  schedule::last); }
date scheduler::last_sunday() const { return day(weekday::Sunday,    schedule::last); }

}  // namespace meetup
