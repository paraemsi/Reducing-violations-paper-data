#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

    scheduler::scheduler(boost::gregorian::month_enum month, int year)
        : m_month(month), m_year(year) {}

    boost::gregorian::date scheduler::get_nth_weekday(int n, boost::date_time::weekdays wd) const {
        using namespace boost::gregorian;
        date first(m_year, m_month, 1);
        int first_wday = first.day_of_week();
        int add_days = (7 + wd - first_wday) % 7 + 7 * (n - 1);
        date result = first + date_duration(add_days);
        if (result.month().as_enum() != m_month)
            throw std::domain_error("No such meetup day");
        return result;
    }

    boost::gregorian::date scheduler::get_last_weekday(boost::date_time::weekdays wd) const {
        using namespace boost::gregorian;
        date first_next_month = (m_month == boost::gregorian::Dec)
            ? date(m_year + 1, boost::gregorian::Jan, 1)
            : date(m_year, static_cast<boost::gregorian::month_enum>(m_month + 1), 1);
        date last = first_next_month - date_duration(1);
        int last_wday = last.day_of_week();
        int sub_days = (7 + last_wday - wd) % 7;
        date result = last - date_duration(sub_days);
        return result;
    }

    boost::gregorian::date scheduler::get_teenth_weekday(boost::date_time::weekdays wd) const {
        using namespace boost::gregorian;
        for (int d = 13; d <= 19; ++d) {
            date dt(m_year, m_month, d);
            if (dt.day_of_week() == wd)
                return dt;
        }
        throw std::domain_error("No such teenth day");
    }

    // Teenth
    boost::gregorian::date scheduler::monteenth() const { return get_teenth_weekday(boost::date_time::Monday); }
    boost::gregorian::date scheduler::tuesteenth() const { return get_teenth_weekday(boost::date_time::Tuesday); }
    boost::gregorian::date scheduler::wednesteenth() const { return get_teenth_weekday(boost::date_time::Wednesday); }
    boost::gregorian::date scheduler::thursteenth() const { return get_teenth_weekday(boost::date_time::Thursday); }
    boost::gregorian::date scheduler::friteenth() const { return get_teenth_weekday(boost::date_time::Friday); }
    boost::gregorian::date scheduler::saturteenth() const { return get_teenth_weekday(boost::date_time::Saturday); }
    boost::gregorian::date scheduler::sunteenth() const { return get_teenth_weekday(boost::date_time::Sunday); }

    // First
    boost::gregorian::date scheduler::first_monday() const { return get_nth_weekday(1, boost::date_time::Monday); }
    boost::gregorian::date scheduler::first_tuesday() const { return get_nth_weekday(1, boost::date_time::Tuesday); }
    boost::gregorian::date scheduler::first_wednesday() const { return get_nth_weekday(1, boost::date_time::Wednesday); }
    boost::gregorian::date scheduler::first_thursday() const { return get_nth_weekday(1, boost::date_time::Thursday); }
    boost::gregorian::date scheduler::first_friday() const { return get_nth_weekday(1, boost::date_time::Friday); }
    boost::gregorian::date scheduler::first_saturday() const { return get_nth_weekday(1, boost::date_time::Saturday); }
    boost::gregorian::date scheduler::first_sunday() const { return get_nth_weekday(1, boost::date_time::Sunday); }

    // Second
    boost::gregorian::date scheduler::second_monday() const { return get_nth_weekday(2, boost::date_time::Monday); }
    boost::gregorian::date scheduler::second_tuesday() const { return get_nth_weekday(2, boost::date_time::Tuesday); }
    boost::gregorian::date scheduler::second_wednesday() const { return get_nth_weekday(2, boost::date_time::Wednesday); }
    boost::gregorian::date scheduler::second_thursday() const { return get_nth_weekday(2, boost::date_time::Thursday); }
    boost::gregorian::date scheduler::second_friday() const { return get_nth_weekday(2, boost::date_time::Friday); }
    boost::gregorian::date scheduler::second_saturday() const { return get_nth_weekday(2, boost::date_time::Saturday); }
    boost::gregorian::date scheduler::second_sunday() const { return get_nth_weekday(2, boost::date_time::Sunday); }

    // Third
    boost::gregorian::date scheduler::third_monday() const { return get_nth_weekday(3, boost::date_time::Monday); }
    boost::gregorian::date scheduler::third_tuesday() const { return get_nth_weekday(3, boost::date_time::Tuesday); }
    boost::gregorian::date scheduler::third_wednesday() const { return get_nth_weekday(3, boost::date_time::Wednesday); }
    boost::gregorian::date scheduler::third_thursday() const { return get_nth_weekday(3, boost::date_time::Thursday); }
    boost::gregorian::date scheduler::third_friday() const { return get_nth_weekday(3, boost::date_time::Friday); }
    boost::gregorian::date scheduler::third_saturday() const { return get_nth_weekday(3, boost::date_time::Saturday); }
    boost::gregorian::date scheduler::third_sunday() const { return get_nth_weekday(3, boost::date_time::Sunday); }

    // Fourth
    boost::gregorian::date scheduler::fourth_monday() const { return get_nth_weekday(4, boost::date_time::Monday); }
    boost::gregorian::date scheduler::fourth_tuesday() const { return get_nth_weekday(4, boost::date_time::Tuesday); }
    boost::gregorian::date scheduler::fourth_wednesday() const { return get_nth_weekday(4, boost::date_time::Wednesday); }
    boost::gregorian::date scheduler::fourth_thursday() const { return get_nth_weekday(4, boost::date_time::Thursday); }
    boost::gregorian::date scheduler::fourth_friday() const { return get_nth_weekday(4, boost::date_time::Friday); }
    boost::gregorian::date scheduler::fourth_saturday() const { return get_nth_weekday(4, boost::date_time::Saturday); }
    boost::gregorian::date scheduler::fourth_sunday() const { return get_nth_weekday(4, boost::date_time::Sunday); }

    // Last
    boost::gregorian::date scheduler::last_monday() const { return get_last_weekday(boost::date_time::Monday); }
    boost::gregorian::date scheduler::last_tuesday() const { return get_last_weekday(boost::date_time::Tuesday); }
    boost::gregorian::date scheduler::last_wednesday() const { return get_last_weekday(boost::date_time::Wednesday); }
    boost::gregorian::date scheduler::last_thursday() const { return get_last_weekday(boost::date_time::Thursday); }
    boost::gregorian::date scheduler::last_friday() const { return get_last_weekday(boost::date_time::Friday); }
    boost::gregorian::date scheduler::last_saturday() const { return get_last_weekday(boost::date_time::Saturday); }
    boost::gregorian::date scheduler::last_sunday() const { return get_last_weekday(boost::date_time::Sunday); }

}  // namespace meetup
