#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(boost::gregorian::greg_month month, std::int32_t year)
    : m_month(month), m_year(year)
{
}

boost::gregorian::date scheduler::find_nth_weekday(boost::date_time::weekdays wd, int n) const
{
    boost::gregorian::date first(m_year, m_month, 1);
    int first_wd = static_cast<int>(first.day_of_week());
    int target_wd = static_cast<int>(wd);
    int day = 1 + ((target_wd - first_wd + 7) % 7) + 7 * (n - 1);
    if(day > static_cast<int>(boost::gregorian::gregorian_calendar::end_of_month_day(m_year, m_month.as_number())))
    {
        throw std::out_of_range("No such weekday in this month");
    }
    return boost::gregorian::date(m_year, m_month, day);
}

boost::gregorian::date scheduler::find_teenth_weekday(boost::date_time::weekdays wd) const
{
    for(int d = 13; d <= 19; ++d)
    {
        boost::gregorian::date dt(m_year, m_month, d);
        if(dt.day_of_week() == wd)
        {
            return dt;
        }
    }
    throw std::out_of_range("No teenth weekday found");
}

boost::gregorian::date scheduler::find_last_weekday(boost::date_time::weekdays wd) const
{
    int last_day = boost::gregorian::gregorian_calendar::end_of_month_day(m_year, m_month.as_number());
    boost::gregorian::date last(m_year, m_month, last_day);
    int last_wd = static_cast<int>(last.day_of_week());
    int target_wd = static_cast<int>(wd);
    int day = last_day - ((last_wd - target_wd + 7) % 7);
    return boost::gregorian::date(m_year, m_month, day);
}

// Teenth
boost::gregorian::date scheduler::monteenth() const { return find_teenth_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return find_teenth_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return find_teenth_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return find_teenth_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return find_teenth_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return find_teenth_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return find_teenth_weekday(boost::date_time::Sunday); }

// First
boost::gregorian::date scheduler::first_monday() const { return find_nth_weekday(boost::date_time::Monday, 1); }
boost::gregorian::date scheduler::first_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 1); }
boost::gregorian::date scheduler::first_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 1); }
boost::gregorian::date scheduler::first_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 1); }
boost::gregorian::date scheduler::first_friday() const { return find_nth_weekday(boost::date_time::Friday, 1); }
boost::gregorian::date scheduler::first_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 1); }
boost::gregorian::date scheduler::first_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 1); }

// Second
boost::gregorian::date scheduler::second_monday() const { return find_nth_weekday(boost::date_time::Monday, 2); }
boost::gregorian::date scheduler::second_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 2); }
boost::gregorian::date scheduler::second_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 2); }
boost::gregorian::date scheduler::second_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 2); }
boost::gregorian::date scheduler::second_friday() const { return find_nth_weekday(boost::date_time::Friday, 2); }
boost::gregorian::date scheduler::second_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 2); }
boost::gregorian::date scheduler::second_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 2); }

// Third
boost::gregorian::date scheduler::third_monday() const { return find_nth_weekday(boost::date_time::Monday, 3); }
boost::gregorian::date scheduler::third_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 3); }
boost::gregorian::date scheduler::third_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 3); }
boost::gregorian::date scheduler::third_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 3); }
boost::gregorian::date scheduler::third_friday() const { return find_nth_weekday(boost::date_time::Friday, 3); }
boost::gregorian::date scheduler::third_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 3); }
boost::gregorian::date scheduler::third_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 3); }

// Fourth
boost::gregorian::date scheduler::fourth_monday() const { return find_nth_weekday(boost::date_time::Monday, 4); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 4); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 4); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 4); }
boost::gregorian::date scheduler::fourth_friday() const { return find_nth_weekday(boost::date_time::Friday, 4); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 4); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 4); }

// Last
boost::gregorian::date scheduler::last_monday() const { return find_last_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return find_last_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return find_last_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return find_last_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return find_last_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return find_last_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return find_last_weekday(boost::date_time::Sunday); }

} // namespace meetup
