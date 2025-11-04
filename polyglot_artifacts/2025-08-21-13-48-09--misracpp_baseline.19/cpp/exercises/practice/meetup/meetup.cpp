#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, months_of_year month)
    : m_year(year), m_month(month) {}

date scheduler::monteenth() const {
    return teenth_weekday(greg_weekday(Monday));
}
date scheduler::tuesteenth() const {
    return teenth_weekday(greg_weekday(Tuesday));
}
date scheduler::wednesteenth() const {
    return teenth_weekday(greg_weekday(Wednesday));
}
date scheduler::thursteenth() const {
    return teenth_weekday(greg_weekday(Thursday));
}
date scheduler::friteenth() const {
    return teenth_weekday(greg_weekday(Friday));
}
date scheduler::saturteenth() const {
    return teenth_weekday(greg_weekday(Saturday));
}
date scheduler::sunteenth() const {
    return teenth_weekday(greg_weekday(Sunday));
}

date scheduler::first_monday() const {
    return nth_weekday(1, greg_weekday(Monday));
}
date scheduler::first_tuesday() const {
    return nth_weekday(1, greg_weekday(Tuesday));
}
date scheduler::first_wednesday() const {
    return nth_weekday(1, greg_weekday(Wednesday));
}
date scheduler::first_thursday() const {
    return nth_weekday(1, greg_weekday(Thursday));
}
date scheduler::first_friday() const {
    return nth_weekday(1, greg_weekday(Friday));
}
date scheduler::first_saturday() const {
    return nth_weekday(1, greg_weekday(Saturday));
}
date scheduler::first_sunday() const {
    return nth_weekday(1, greg_weekday(Sunday));
}

date scheduler::second_monday() const {
    return nth_weekday(2, greg_weekday(Monday));
}
date scheduler::second_tuesday() const {
    return nth_weekday(2, greg_weekday(Tuesday));
}
date scheduler::second_wednesday() const {
    return nth_weekday(2, greg_weekday(Wednesday));
}
date scheduler::second_thursday() const {
    return nth_weekday(2, greg_weekday(Thursday));
}
date scheduler::second_friday() const {
    return nth_weekday(2, greg_weekday(Friday));
}
date scheduler::second_saturday() const {
    return nth_weekday(2, greg_weekday(Saturday));
}
date scheduler::second_sunday() const {
    return nth_weekday(2, greg_weekday(Sunday));
}

date scheduler::third_monday() const {
    return nth_weekday(3, greg_weekday(Monday));
}
date scheduler::third_tuesday() const {
    return nth_weekday(3, greg_weekday(Tuesday));
}
date scheduler::third_wednesday() const {
    return nth_weekday(3, greg_weekday(Wednesday));
}
date scheduler::third_thursday() const {
    return nth_weekday(3, greg_weekday(Thursday));
}
date scheduler::third_friday() const {
    return nth_weekday(3, greg_weekday(Friday));
}
date scheduler::third_saturday() const {
    return nth_weekday(3, greg_weekday(Saturday));
}
date scheduler::third_sunday() const {
    return nth_weekday(3, greg_weekday(Sunday));
}

date scheduler::fourth_monday() const {
    return nth_weekday(4, greg_weekday(Monday));
}
date scheduler::fourth_tuesday() const {
    return nth_weekday(4, greg_weekday(Tuesday));
}
date scheduler::fourth_wednesday() const {
    return nth_weekday(4, greg_weekday(Wednesday));
}
date scheduler::fourth_thursday() const {
    return nth_weekday(4, greg_weekday(Thursday));
}
date scheduler::fourth_friday() const {
    return nth_weekday(4, greg_weekday(Friday));
}
date scheduler::fourth_saturday() const {
    return nth_weekday(4, greg_weekday(Saturday));
}
date scheduler::fourth_sunday() const {
    return nth_weekday(4, greg_weekday(Sunday));
}

date scheduler::last_monday() const {
    return last_weekday(greg_weekday(Monday));
}
date scheduler::last_tuesday() const {
    return last_weekday(greg_weekday(Tuesday));
}
date scheduler::last_wednesday() const {
    return last_weekday(greg_weekday(Wednesday));
}
date scheduler::last_thursday() const {
    return last_weekday(greg_weekday(Thursday));
}
date scheduler::last_friday() const {
    return last_weekday(greg_weekday(Friday));
}
date scheduler::last_saturday() const {
    return last_weekday(greg_weekday(Saturday));
}
date scheduler::last_sunday() const {
    return last_weekday(greg_weekday(Sunday));
}

date scheduler::nth_weekday(int n, greg_weekday wd) const {
    // Find the first day of the month
    date first(m_year, m_month, 1);
    greg_weekday first_wday = first.day_of_week();
    int days_to_add = (wd.as_number() - first_wday.as_number() + 7) % 7 + (n - 1) * 7;
    date result = first + date_duration(days_to_add);
    if (result.month() != m_month)
        throw std::domain_error("No such weekday in this month");
    return result;
}

date scheduler::last_weekday(greg_weekday wd) const {
    // Find the last day of the month
    date first(m_year, m_month, 1);
    date last = first.end_of_month();
    greg_weekday last_wday = last.day_of_week();
    int days_to_sub = (last_wday.as_number() - wd.as_number() + 7) % 7;
    date result = last - date_duration(days_to_sub);
    if (result.month() != m_month)
        throw std::domain_error("No such weekday in this month");
    return result;
}

date scheduler::teenth_weekday(greg_weekday wd) const {
    for (int d = 13; d <= 19; ++d) {
        date dt(m_year, m_month, d);
        if (dt.day_of_week() == wd)
            return dt;
    }
    throw std::domain_error("No teenth weekday in this month");
}

}  // namespace meetup
