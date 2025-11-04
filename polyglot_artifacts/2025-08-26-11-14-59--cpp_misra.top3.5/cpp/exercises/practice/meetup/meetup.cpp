#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <string>
#include <map>

namespace meetup {

namespace {
    boost::date_time::weekdays weekday_from_name(const std::string& name) {
        static const std::map<std::string, boost::date_time::weekdays> lookup = {
            {"Monday",    boost::date_time::Monday},
            {"Tuesday",   boost::date_time::Tuesday},
            {"Wednesday", boost::date_time::Wednesday},
            {"Thursday",  boost::date_time::Thursday},
            {"Friday",    boost::date_time::Friday},
            {"Saturday",  boost::date_time::Saturday},
            {"Sunday",    boost::date_time::Sunday}
        };
        auto it = lookup.find(name);
        if(it == lookup.end()) {
            throw std::invalid_argument("Invalid weekday: " + name);
        }
        return it->second;
    }
}

scheduler::scheduler(boost::gregorian::months_of_year month, std::int32_t year)
    : m_month(month), m_year(year)
{
}

boost::gregorian::date scheduler::find_nth_weekday(boost::date_time::weekdays wd, std::int32_t nth) const
{
    boost::gregorian::date first(m_year, m_month, 1);
    std::int32_t first_wd = static_cast<std::int32_t>(first.day_of_week());
    std::int32_t offset = (static_cast<std::int32_t>(wd) - first_wd + 7) % 7;
    std::int32_t day = 1 + offset + 7 * (nth - 1);
    boost::gregorian::date d(m_year, m_month, 1);
    boost::gregorian::date end = d.end_of_month();
    if(day > static_cast<std::int32_t>(end.day())) {
        throw std::logic_error("No such weekday in given week");
    }
    return boost::gregorian::date(m_year, m_month, day);
}

boost::gregorian::date scheduler::find_teenth_weekday(boost::date_time::weekdays wd) const
{
    for(std::int32_t d = 13; d <= 19; ++d) {
        boost::gregorian::date date(m_year, m_month, d);
        if(date.day_of_week() == wd) {
            return date;
        }
    }
    throw std::logic_error("No teenth weekday found");
}

boost::gregorian::date scheduler::find_last_weekday(boost::date_time::weekdays wd) const
{
    boost::gregorian::date d(m_year, m_month, 1);
    boost::gregorian::date end = d.end_of_month();
    std::int32_t last_day = static_cast<std::int32_t>(end.day());
    for(std::int32_t day = last_day; day >= 1; --day) {
        boost::gregorian::date date(m_year, m_month, day);
        if(date.day_of_week() == wd) {
            return date;
        }
    }
    throw std::logic_error("No last weekday found");
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
boost::gregorian::date scheduler::first_monday() const { return find_nth_weekday(boost::date_time::Monday, 1); }
boost::gregorian::date scheduler::first_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 1); }
boost::gregorian::date scheduler::first_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 1); }
boost::gregorian::date scheduler::first_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 1); }
boost::gregorian::date scheduler::first_friday() const { return find_nth_weekday(boost::date_time::Friday, 1); }
boost::gregorian::date scheduler::first_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 1); }
boost::gregorian::date scheduler::first_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 1); }

// second
boost::gregorian::date scheduler::second_monday() const { return find_nth_weekday(boost::date_time::Monday, 2); }
boost::gregorian::date scheduler::second_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 2); }
boost::gregorian::date scheduler::second_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 2); }
boost::gregorian::date scheduler::second_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 2); }
boost::gregorian::date scheduler::second_friday() const { return find_nth_weekday(boost::date_time::Friday, 2); }
boost::gregorian::date scheduler::second_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 2); }
boost::gregorian::date scheduler::second_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 2); }

// third
boost::gregorian::date scheduler::third_monday() const { return find_nth_weekday(boost::date_time::Monday, 3); }
boost::gregorian::date scheduler::third_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 3); }
boost::gregorian::date scheduler::third_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 3); }
boost::gregorian::date scheduler::third_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 3); }
boost::gregorian::date scheduler::third_friday() const { return find_nth_weekday(boost::date_time::Friday, 3); }
boost::gregorian::date scheduler::third_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 3); }
boost::gregorian::date scheduler::third_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 3); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return find_nth_weekday(boost::date_time::Monday, 4); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 4); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 4); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 4); }
boost::gregorian::date scheduler::fourth_friday() const { return find_nth_weekday(boost::date_time::Friday, 4); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 4); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 4); }

// last
boost::gregorian::date scheduler::last_monday() const { return find_last_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return find_last_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return find_last_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return find_last_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return find_last_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return find_last_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return find_last_weekday(boost::date_time::Sunday); }

} // namespace meetup
