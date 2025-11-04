#include "meetup.h"
#include <ctime>
#include <map>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

namespace meetup {

class scheduler {
public:
    scheduler(boost::gregorian::months_of_year month, year_t year)
        : m_month(month), m_year(year) {}

    boost::gregorian::date monteenth() const { return get_teenth("Monday"); }
    boost::gregorian::date tuesteenth() const { return get_teenth("Tuesday"); }
    boost::gregorian::date wednesteenth() const { return get_teenth("Wednesday"); }
    boost::gregorian::date thursteenth() const { return get_teenth("Thursday"); }
    boost::gregorian::date friteenth() const { return get_teenth("Friday"); }
    boost::gregorian::date saturteenth() const { return get_teenth("Saturday"); }
    boost::gregorian::date sunteenth() const { return get_teenth("Sunday"); }

    boost::gregorian::date first_monday() const { return get_nth("Monday", 1); }
    boost::gregorian::date first_tuesday() const { return get_nth("Tuesday", 1); }
    boost::gregorian::date first_wednesday() const { return get_nth("Wednesday", 1); }
    boost::gregorian::date first_thursday() const { return get_nth("Thursday", 1); }
    boost::gregorian::date first_friday() const { return get_nth("Friday", 1); }
    boost::gregorian::date first_saturday() const { return get_nth("Saturday", 1); }
    boost::gregorian::date first_sunday() const { return get_nth("Sunday", 1); }

    boost::gregorian::date second_monday() const { return get_nth("Monday", 2); }
    boost::gregorian::date second_tuesday() const { return get_nth("Tuesday", 2); }
    boost::gregorian::date second_wednesday() const { return get_nth("Wednesday", 2); }
    boost::gregorian::date second_thursday() const { return get_nth("Thursday", 2); }
    boost::gregorian::date second_friday() const { return get_nth("Friday", 2); }
    boost::gregorian::date second_saturday() const { return get_nth("Saturday", 2); }
    boost::gregorian::date second_sunday() const { return get_nth("Sunday", 2); }

    boost::gregorian::date third_monday() const { return get_nth("Monday", 3); }
    boost::gregorian::date third_tuesday() const { return get_nth("Tuesday", 3); }
    boost::gregorian::date third_wednesday() const { return get_nth("Wednesday", 3); }
    boost::gregorian::date third_thursday() const { return get_nth("Thursday", 3); }
    boost::gregorian::date third_friday() const { return get_nth("Friday", 3); }
    boost::gregorian::date third_saturday() const { return get_nth("Saturday", 3); }
    boost::gregorian::date third_sunday() const { return get_nth("Sunday", 3); }

    boost::gregorian::date fourth_monday() const { return get_nth("Monday", 4); }
    boost::gregorian::date fourth_tuesday() const { return get_nth("Tuesday", 4); }
    boost::gregorian::date fourth_wednesday() const { return get_nth("Wednesday", 4); }
    boost::gregorian::date fourth_thursday() const { return get_nth("Thursday", 4); }
    boost::gregorian::date fourth_friday() const { return get_nth("Friday", 4); }
    boost::gregorian::date fourth_saturday() const { return get_nth("Saturday", 4); }
    boost::gregorian::date fourth_sunday() const { return get_nth("Sunday", 4); }

    boost::gregorian::date last_monday() const { return get_last("Monday"); }
    boost::gregorian::date last_tuesday() const { return get_last("Tuesday"); }
    boost::gregorian::date last_wednesday() const { return get_last("Wednesday"); }
    boost::gregorian::date last_thursday() const { return get_last("Thursday"); }
    boost::gregorian::date last_friday() const { return get_last("Friday"); }
    boost::gregorian::date last_saturday() const { return get_last("Saturday"); }
    boost::gregorian::date last_sunday() const { return get_last("Sunday"); }

private:
    boost::gregorian::months_of_year m_month;
    year_t m_year;

    boost::gregorian::date get_teenth(const std::string& weekday) const {
        for (int d = 13; d <= 19; ++d) {
            boost::gregorian::date date(m_year, m_month, d);
            if (date.day_of_week().as_long_string() == weekday) {
                return date;
            }
        }
        throw std::domain_error("No teenth " + weekday);
    }

    boost::gregorian::date get_nth(const std::string& weekday, int n) const {
        int count = 0;
        boost::gregorian::date first(m_year, m_month, 1);
        boost::gregorian::date end = first.end_of_month();
        for (boost::gregorian::date d = first; d <= end; d += boost::gregorian::days(1)) {
            if (d.day_of_week().as_long_string() == weekday) {
                ++count;
                if (count == n) {
                    return d;
                }
            }
        }
        throw std::domain_error("No such weekday in this month");
    }

    boost::gregorian::date get_last(const std::string& weekday) const {
        boost::gregorian::date first(m_year, m_month, 1);
        boost::gregorian::date end = first.end_of_month();
        for (boost::gregorian::date d = end; d >= first; d -= boost::gregorian::days(1)) {
            if (d.day_of_week().as_long_string() == weekday) {
                return d;
            }
        }
        throw std::domain_error("No such weekday in this month");
    }
};

} // namespace meetup
