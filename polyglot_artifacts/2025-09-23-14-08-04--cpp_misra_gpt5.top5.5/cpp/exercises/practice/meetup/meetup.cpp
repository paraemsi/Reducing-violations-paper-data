#include "meetup.h"

namespace meetup {

scheduler::scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept
    : month_(boost::gregorian::greg_month(month)), year_(year) { }

boost::gregorian::date scheduler::find_teenth(boost::date_time::weekdays wd) const noexcept {
    const boost::gregorian::greg_weekday target{wd};
    boost::gregorian::date d(year_, month_, 13);
    while ((d.day_of_week() != target)) {
        d += boost::gregorian::date_duration(1);
    }
    return d;
}

boost::gregorian::date scheduler::find_first(boost::date_time::weekdays wd) const noexcept {
    const boost::gregorian::greg_weekday target{wd};
    boost::gregorian::date d(year_, month_, 1);
    while ((d.day_of_week() != target)) {
        d += boost::gregorian::date_duration(1);
    }
    return d;
}

boost::gregorian::date scheduler::find_nth(boost::date_time::weekdays wd, std::int32_t n) const noexcept {
    boost::gregorian::date d = find_first(wd);
    for (std::int32_t i = 1; (i < n); ++i) {
        d += boost::gregorian::date_duration(7);
    }
    return d;
}

boost::gregorian::date scheduler::find_last(boost::date_time::weekdays wd) const noexcept {
    const boost::gregorian::greg_weekday target{wd};
    const std::int32_t last_dom =
        static_cast<std::int32_t>(boost::gregorian::gregorian_calendar::end_of_month_day(
            static_cast<std::int32_t>(year_),
            static_cast<std::int32_t>(month_.as_number())));
    boost::gregorian::date d(year_, month_, last_dom);
    while ((d.day_of_week() != target)) {
        d -= boost::gregorian::date_duration(1);
    }
    return d;
}

// Teenth
boost::gregorian::date scheduler::monteenth() const noexcept { return find_teenth(boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth() const noexcept { return find_teenth(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const noexcept { return find_teenth(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const noexcept { return find_teenth(boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth() const noexcept { return find_teenth(boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const noexcept { return find_teenth(boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth() const noexcept { return find_teenth(boost::date_time::Sunday); }

// First
boost::gregorian::date scheduler::first_monday() const noexcept { return find_nth(boost::date_time::Monday, 1); }
boost::gregorian::date scheduler::first_tuesday() const noexcept { return find_nth(boost::date_time::Tuesday, 1); }
boost::gregorian::date scheduler::first_wednesday() const noexcept { return find_nth(boost::date_time::Wednesday, 1); }
boost::gregorian::date scheduler::first_thursday() const noexcept { return find_nth(boost::date_time::Thursday, 1); }
boost::gregorian::date scheduler::first_friday() const noexcept { return find_nth(boost::date_time::Friday, 1); }
boost::gregorian::date scheduler::first_saturday() const noexcept { return find_nth(boost::date_time::Saturday, 1); }
boost::gregorian::date scheduler::first_sunday() const noexcept { return find_nth(boost::date_time::Sunday, 1); }

// Second
boost::gregorian::date scheduler::second_monday() const noexcept { return find_nth(boost::date_time::Monday, 2); }
boost::gregorian::date scheduler::second_tuesday() const noexcept { return find_nth(boost::date_time::Tuesday, 2); }
boost::gregorian::date scheduler::second_wednesday() const noexcept { return find_nth(boost::date_time::Wednesday, 2); }
boost::gregorian::date scheduler::second_thursday() const noexcept { return find_nth(boost::date_time::Thursday, 2); }
boost::gregorian::date scheduler::second_friday() const noexcept { return find_nth(boost::date_time::Friday, 2); }
boost::gregorian::date scheduler::second_saturday() const noexcept { return find_nth(boost::date_time::Saturday, 2); }
boost::gregorian::date scheduler::second_sunday() const noexcept { return find_nth(boost::date_time::Sunday, 2); }

// Third
boost::gregorian::date scheduler::third_monday() const noexcept { return find_nth(boost::date_time::Monday, 3); }
boost::gregorian::date scheduler::third_tuesday() const noexcept { return find_nth(boost::date_time::Tuesday, 3); }
boost::gregorian::date scheduler::third_wednesday() const noexcept { return find_nth(boost::date_time::Wednesday, 3); }
boost::gregorian::date scheduler::third_thursday() const noexcept { return find_nth(boost::date_time::Thursday, 3); }
boost::gregorian::date scheduler::third_friday() const noexcept { return find_nth(boost::date_time::Friday, 3); }
boost::gregorian::date scheduler::third_saturday() const noexcept { return find_nth(boost::date_time::Saturday, 3); }
boost::gregorian::date scheduler::third_sunday() const noexcept { return find_nth(boost::date_time::Sunday, 3); }

// Fourth
boost::gregorian::date scheduler::fourth_monday() const noexcept { return find_nth(boost::date_time::Monday, 4); }
boost::gregorian::date scheduler::fourth_tuesday() const noexcept { return find_nth(boost::date_time::Tuesday, 4); }
boost::gregorian::date scheduler::fourth_wednesday() const noexcept { return find_nth(boost::date_time::Wednesday, 4); }
boost::gregorian::date scheduler::fourth_thursday() const noexcept { return find_nth(boost::date_time::Thursday, 4); }
boost::gregorian::date scheduler::fourth_friday() const noexcept { return find_nth(boost::date_time::Friday, 4); }
boost::gregorian::date scheduler::fourth_saturday() const noexcept { return find_nth(boost::date_time::Saturday, 4); }
boost::gregorian::date scheduler::fourth_sunday() const noexcept { return find_nth(boost::date_time::Sunday, 4); }

// Last
boost::gregorian::date scheduler::last_monday() const noexcept { return find_last(boost::date_time::Monday); }
boost::gregorian::date scheduler::last_tuesday() const noexcept { return find_last(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const noexcept { return find_last(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const noexcept { return find_last(boost::date_time::Thursday); }
boost::gregorian::date scheduler::last_friday() const noexcept { return find_last(boost::date_time::Friday); }
boost::gregorian::date scheduler::last_saturday() const noexcept { return find_last(boost::date_time::Saturday); }
boost::gregorian::date scheduler::last_sunday() const noexcept { return find_last(boost::date_time::Sunday); }

}  // namespace meetup
