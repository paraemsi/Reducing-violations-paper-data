#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <string>
#include <cstddef>

namespace meetup {

namespace {
    boost::date_time::weekdays weekday_from_string(const std::string& weekday) {
        if(weekday == "Monday") return boost::date_time::Monday;
        if(weekday == "Tuesday") return boost::date_time::Tuesday;
        if(weekday == "Wednesday") return boost::date_time::Wednesday;
        if(weekday == "Thursday") return boost::date_time::Thursday;
        if(weekday == "Friday") return boost::date_time::Friday;
        if(weekday == "Saturday") return boost::date_time::Saturday;
        if(weekday == "Sunday") return boost::date_time::Sunday;
        throw std::invalid_argument("Invalid weekday: " + weekday);
    }
}

scheduler::scheduler(boost::gregorian::greg_month month, std::int32_t year)
    : m_month(month), m_year(year)
{}

boost::gregorian::date scheduler::find_nth_weekday(boost::date_time::weekdays wd, std::size_t n) const {
    boost::gregorian::date first(m_year, m_month, 1);
    std::size_t count = 0U;
    for(boost::gregorian::date d = first;
        d.month() == m_month;
        d = d + boost::gregorian::days(1)) {
        if(d.day_of_week() == wd) {
            ++count;
            if(count == n) {
                return d;
            }
        }
    }
    throw std::logic_error("No such weekday in month");
}

boost::gregorian::date scheduler::find_last_weekday(boost::date_time::weekdays wd) const {
    boost::gregorian::date d(m_year, m_month, 1);
    boost::gregorian::date last = d.end_of_month();
    for(boost::gregorian::date cur = last;
        cur.month() == m_month;
        cur = cur - boost::gregorian::days(1)) {
        if(cur.day_of_week() == wd) {
            return cur;
        }
    }
    throw std::logic_error("No such weekday in month");
}

boost::gregorian::date scheduler::find_teenth_weekday(boost::date_time::weekdays wd) const {
    for(boost::gregorian::date d(m_year, m_month, 13);
        d.day() <= 19;
        d = d + boost::gregorian::days(1)) {
        if(d.day_of_week() == wd) {
            return d;
        }
    }
    throw std::logic_error("No teenth weekday in month");
}

// teenth
boost::gregorian::date scheduler::monteenth() const { return find_teenth_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return find_teenth_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return find_teenth_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return find_teenth_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return find_teenth_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return find_teenth_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return find_teenth_weekday(boost::date_time::Sunday); }

// first
boost::gregorian::date scheduler::first_monday() const { return find_nth_weekday(boost::date_time::Monday, 1U); }
boost::gregorian::date scheduler::first_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 1U); }
boost::gregorian::date scheduler::first_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 1U); }
boost::gregorian::date scheduler::first_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 1U); }
boost::gregorian::date scheduler::first_friday() const { return find_nth_weekday(boost::date_time::Friday, 1U); }
boost::gregorian::date scheduler::first_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 1U); }
boost::gregorian::date scheduler::first_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 1U); }

// second
boost::gregorian::date scheduler::second_monday() const { return find_nth_weekday(boost::date_time::Monday, 2U); }
boost::gregorian::date scheduler::second_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 2U); }
boost::gregorian::date scheduler::second_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 2U); }
boost::gregorian::date scheduler::second_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 2U); }
boost::gregorian::date scheduler::second_friday() const { return find_nth_weekday(boost::date_time::Friday, 2U); }
boost::gregorian::date scheduler::second_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 2U); }
boost::gregorian::date scheduler::second_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 2U); }

// third
boost::gregorian::date scheduler::third_monday() const { return find_nth_weekday(boost::date_time::Monday, 3U); }
boost::gregorian::date scheduler::third_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 3U); }
boost::gregorian::date scheduler::third_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 3U); }
boost::gregorian::date scheduler::third_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 3U); }
boost::gregorian::date scheduler::third_friday() const { return find_nth_weekday(boost::date_time::Friday, 3U); }
boost::gregorian::date scheduler::third_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 3U); }
boost::gregorian::date scheduler::third_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 3U); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return find_nth_weekday(boost::date_time::Monday, 4U); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 4U); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 4U); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 4U); }
boost::gregorian::date scheduler::fourth_friday() const { return find_nth_weekday(boost::date_time::Friday, 4U); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 4U); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 4U); }

// last
boost::gregorian::date scheduler::last_monday() const { return find_last_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return find_last_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return find_last_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return find_last_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return find_last_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return find_last_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return find_last_weekday(boost::date_time::Sunday); }

} // namespace meetup
