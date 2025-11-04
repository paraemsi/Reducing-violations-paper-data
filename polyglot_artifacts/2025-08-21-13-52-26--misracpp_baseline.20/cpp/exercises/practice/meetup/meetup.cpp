#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

namespace {
    // Map weekday index: 0=Sunday, ..., 6=Saturday
    int weekday_index(const std::string& name) {
        if (name == "Monday") return 1;
        if (name == "Tuesday") return 2;
        if (name == "Wednesday") return 3;
        if (name == "Thursday") return 4;
        if (name == "Friday") return 5;
        if (name == "Saturday") return 6;
        if (name == "Sunday") return 0;
        throw std::invalid_argument("Invalid weekday name");
    }
}

scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : m_month(month), m_year(year) {}

boost::gregorian::date scheduler::get_nth_weekday(int weekday, int n) const {
    // n = 1 (first), 2 (second), 3 (third), 4 (fourth)
    boost::gregorian::date first_day(m_year, m_month, 1);
    int first_wday = first_day.day_of_week();
    int offset = (weekday - first_wday + 7) % 7;
    int day = 1 + offset + 7 * (n - 1);
    if (day > boost::gregorian::gregorian_calendar::end_of_month_day(m_year, m_month))
        throw std::logic_error("No such weekday in this month");
    return boost::gregorian::date(m_year, m_month, day);
}

boost::gregorian::date scheduler::get_last_weekday(int weekday) const {
    int last_day_num = boost::gregorian::gregorian_calendar::end_of_month_day(m_year, m_month);
    boost::gregorian::date last_day(m_year, m_month, last_day_num);
    int last_wday = last_day.day_of_week();
    int offset = (last_wday - weekday + 7) % 7;
    int day = last_day_num - offset;
    return boost::gregorian::date(m_year, m_month, day);
}

boost::gregorian::date scheduler::get_teenth_weekday(int weekday) const {
    for (int d = 13; d <= 19; ++d) {
        boost::gregorian::date date(m_year, m_month, d);
        if (date.day_of_week() == weekday)
            return date;
    }
    throw std::logic_error("No teenth weekday found");
}

// Teenth
boost::gregorian::date scheduler::monteenth() const { return get_teenth_weekday(1); }
boost::gregorian::date scheduler::tuesteenth() const { return get_teenth_weekday(2); }
boost::gregorian::date scheduler::wednesteenth() const { return get_teenth_weekday(3); }
boost::gregorian::date scheduler::thursteenth() const { return get_teenth_weekday(4); }
boost::gregorian::date scheduler::friteenth() const { return get_teenth_weekday(5); }
boost::gregorian::date scheduler::saturteenth() const { return get_teenth_weekday(6); }
boost::gregorian::date scheduler::sunteenth() const { return get_teenth_weekday(0); }

// First
boost::gregorian::date scheduler::first_monday() const { return get_nth_weekday(1, 1); }
boost::gregorian::date scheduler::first_tuesday() const { return get_nth_weekday(2, 1); }
boost::gregorian::date scheduler::first_wednesday() const { return get_nth_weekday(3, 1); }
boost::gregorian::date scheduler::first_thursday() const { return get_nth_weekday(4, 1); }
boost::gregorian::date scheduler::first_friday() const { return get_nth_weekday(5, 1); }
boost::gregorian::date scheduler::first_saturday() const { return get_nth_weekday(6, 1); }
boost::gregorian::date scheduler::first_sunday() const { return get_nth_weekday(0, 1); }

// Second
boost::gregorian::date scheduler::second_monday() const { return get_nth_weekday(1, 2); }
boost::gregorian::date scheduler::second_tuesday() const { return get_nth_weekday(2, 2); }
boost::gregorian::date scheduler::second_wednesday() const { return get_nth_weekday(3, 2); }
boost::gregorian::date scheduler::second_thursday() const { return get_nth_weekday(4, 2); }
boost::gregorian::date scheduler::second_friday() const { return get_nth_weekday(5, 2); }
boost::gregorian::date scheduler::second_saturday() const { return get_nth_weekday(6, 2); }
boost::gregorian::date scheduler::second_sunday() const { return get_nth_weekday(0, 2); }

// Third
boost::gregorian::date scheduler::third_monday() const { return get_nth_weekday(1, 3); }
boost::gregorian::date scheduler::third_tuesday() const { return get_nth_weekday(2, 3); }
boost::gregorian::date scheduler::third_wednesday() const { return get_nth_weekday(3, 3); }
boost::gregorian::date scheduler::third_thursday() const { return get_nth_weekday(4, 3); }
boost::gregorian::date scheduler::third_friday() const { return get_nth_weekday(5, 3); }
boost::gregorian::date scheduler::third_saturday() const { return get_nth_weekday(6, 3); }
boost::gregorian::date scheduler::third_sunday() const { return get_nth_weekday(0, 3); }

// Fourth
boost::gregorian::date scheduler::fourth_monday() const { return get_nth_weekday(1, 4); }
boost::gregorian::date scheduler::fourth_tuesday() const { return get_nth_weekday(2, 4); }
boost::gregorian::date scheduler::fourth_wednesday() const { return get_nth_weekday(3, 4); }
boost::gregorian::date scheduler::fourth_thursday() const { return get_nth_weekday(4, 4); }
boost::gregorian::date scheduler::fourth_friday() const { return get_nth_weekday(5, 4); }
boost::gregorian::date scheduler::fourth_saturday() const { return get_nth_weekday(6, 4); }
boost::gregorian::date scheduler::fourth_sunday() const { return get_nth_weekday(0, 4); }

// Last
boost::gregorian::date scheduler::last_monday() const { return get_last_weekday(1); }
boost::gregorian::date scheduler::last_tuesday() const { return get_last_weekday(2); }
boost::gregorian::date scheduler::last_wednesday() const { return get_last_weekday(3); }
boost::gregorian::date scheduler::last_thursday() const { return get_last_weekday(4); }
boost::gregorian::date scheduler::last_friday() const { return get_last_weekday(5); }
boost::gregorian::date scheduler::last_saturday() const { return get_last_weekday(6); }
boost::gregorian::date scheduler::last_sunday() const { return get_last_weekday(0); }

}  // namespace meetup
