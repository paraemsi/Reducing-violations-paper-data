#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

namespace {

int weekday_to_num(boost::date_time::weekdays wd) {
    // boost: Sunday=0, Monday=1, ..., Saturday=6
    return static_cast<int>(wd);
}

boost::date_time::weekdays weekday_from_index(int idx) {
    return static_cast<boost::date_time::weekdays>(idx);
}

boost::date_time::weekdays weekday_from_name(const std::string& name) {
    if (name == "Monday") return boost::date_time::Monday;
    if (name == "Tuesday") return boost::date_time::Tuesday;
    if (name == "Wednesday") return boost::date_time::Wednesday;
    if (name == "Thursday") return boost::date_time::Thursday;
    if (name == "Friday") return boost::date_time::Friday;
    if (name == "Saturday") return boost::date_time::Saturday;
    if (name == "Sunday") return boost::date_time::Sunday;
    throw std::invalid_argument("Invalid weekday name");
}

} // namespace

scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : m_month(month), m_year(year)
{}

boost::gregorian::date scheduler::get_nth_weekday(unsigned int weekday, unsigned int n) const
{
    // n: 1=first, 2=second, 3=third, 4=fourth
    boost::gregorian::date first(m_year, m_month, 1);
    unsigned int first_wday = static_cast<unsigned int>(weekday_to_num(first.day_of_week()));
    unsigned int delta = (weekday + 7U - first_wday) % 7U;
    unsigned int day = 1U + delta + 7U * (n - 1U);
    boost::gregorian::date d(m_year, m_month, static_cast<unsigned short>(day));
    if (d.month() != m_month) { throw std::domain_error("No such weekday in this month"); }
    return d;
}

boost::gregorian::date scheduler::get_teenth_weekday(unsigned int weekday) const
{
    for (unsigned int d = 13U; d <= 19U; ++d) {
        boost::gregorian::date date(m_year, m_month, static_cast<unsigned short>(d));
        if (static_cast<unsigned int>(weekday_to_num(date.day_of_week())) == weekday) {
            return date;
        }
    }
    throw std::domain_error("No teenth weekday found");
}

boost::gregorian::date scheduler::get_last_weekday(unsigned int weekday) const
{
    boost::gregorian::date d = boost::gregorian::date(m_year, static_cast<unsigned short>(m_month) + 1U, 1) - boost::gregorian::days(1);
    while (static_cast<unsigned int>(weekday_to_num(d.day_of_week())) != weekday) {
        d -= boost::gregorian::days(1);
    }
    return d;
}

// Teenth
boost::gregorian::date scheduler::monteenth() const { return get_teenth_weekday(weekday_to_num(boost::date_time::Monday)); }
boost::gregorian::date scheduler::tuesteenth() const { return get_teenth_weekday(weekday_to_num(boost::date_time::Tuesday)); }
boost::gregorian::date scheduler::wednesteenth() const { return get_teenth_weekday(weekday_to_num(boost::date_time::Wednesday)); }
boost::gregorian::date scheduler::thursteenth() const { return get_teenth_weekday(weekday_to_num(boost::date_time::Thursday)); }
boost::gregorian::date scheduler::friteenth() const { return get_teenth_weekday(weekday_to_num(boost::date_time::Friday)); }
boost::gregorian::date scheduler::saturteenth() const { return get_teenth_weekday(weekday_to_num(boost::date_time::Saturday)); }
boost::gregorian::date scheduler::sunteenth() const { return get_teenth_weekday(weekday_to_num(boost::date_time::Sunday)); }

// First
boost::gregorian::date scheduler::first_monday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Monday), 1); }
boost::gregorian::date scheduler::first_tuesday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Tuesday), 1); }
boost::gregorian::date scheduler::first_wednesday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Wednesday), 1); }
boost::gregorian::date scheduler::first_thursday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Thursday), 1); }
boost::gregorian::date scheduler::first_friday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Friday), 1); }
boost::gregorian::date scheduler::first_saturday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Saturday), 1); }
boost::gregorian::date scheduler::first_sunday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Sunday), 1); }

// Second
boost::gregorian::date scheduler::second_monday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Monday), 2); }
boost::gregorian::date scheduler::second_tuesday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Tuesday), 2); }
boost::gregorian::date scheduler::second_wednesday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Wednesday), 2); }
boost::gregorian::date scheduler::second_thursday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Thursday), 2); }
boost::gregorian::date scheduler::second_friday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Friday), 2); }
boost::gregorian::date scheduler::second_saturday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Saturday), 2); }
boost::gregorian::date scheduler::second_sunday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Sunday), 2); }

// Third
boost::gregorian::date scheduler::third_monday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Monday), 3); }
boost::gregorian::date scheduler::third_tuesday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Tuesday), 3); }
boost::gregorian::date scheduler::third_wednesday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Wednesday), 3); }
boost::gregorian::date scheduler::third_thursday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Thursday), 3); }
boost::gregorian::date scheduler::third_friday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Friday), 3); }
boost::gregorian::date scheduler::third_saturday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Saturday), 3); }
boost::gregorian::date scheduler::third_sunday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Sunday), 3); }

// Fourth
boost::gregorian::date scheduler::fourth_monday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Monday), 4); }
boost::gregorian::date scheduler::fourth_tuesday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Tuesday), 4); }
boost::gregorian::date scheduler::fourth_wednesday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Wednesday), 4); }
boost::gregorian::date scheduler::fourth_thursday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Thursday), 4); }
boost::gregorian::date scheduler::fourth_friday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Friday), 4); }
boost::gregorian::date scheduler::fourth_saturday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Saturday), 4); }
boost::gregorian::date scheduler::fourth_sunday() const { return get_nth_weekday(weekday_to_num(boost::date_time::Sunday), 4); }

// Last
boost::gregorian::date scheduler::last_monday() const { return get_last_weekday(weekday_to_num(boost::date_time::Monday)); }
boost::gregorian::date scheduler::last_tuesday() const { return get_last_weekday(weekday_to_num(boost::date_time::Tuesday)); }
boost::gregorian::date scheduler::last_wednesday() const { return get_last_weekday(weekday_to_num(boost::date_time::Wednesday)); }
boost::gregorian::date scheduler::last_thursday() const { return get_last_weekday(weekday_to_num(boost::date_time::Thursday)); }
boost::gregorian::date scheduler::last_friday() const { return get_last_weekday(weekday_to_num(boost::date_time::Friday)); }
boost::gregorian::date scheduler::last_saturday() const { return get_last_weekday(weekday_to_num(boost::date_time::Saturday)); }
boost::gregorian::date scheduler::last_sunday() const { return get_last_weekday(weekday_to_num(boost::date_time::Sunday)); }

} // namespace meetup
