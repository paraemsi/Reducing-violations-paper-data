#if !defined(MEETUP_H)
#define MEETUP_H

#include <chrono>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

enum class schedule { first, second, third, fourth, last, teenth };

#if defined(__cpp_lib_chrono) && __cpp_lib_chrono >= 201907L
std::chrono::year_month_day meetup_day(std::chrono::year year,
                                       std::chrono::month month,
                                       std::chrono::weekday wd,
                                       schedule which);
#else
enum class weekday { Sunday = 0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

struct date {
    int year;
    unsigned month;
    unsigned day;
};

date meetup_day(int year, unsigned month, weekday wd, schedule which);
#endif

class scheduler {
public:
    scheduler(boost::gregorian::months_of_year month, int year);

    // teenth
    boost::gregorian::date monteenth() const;
    boost::gregorian::date tuesteenth() const;
    boost::gregorian::date wednesteenth() const;
    boost::gregorian::date thursteenth() const;
    boost::gregorian::date friteenth() const;
    boost::gregorian::date saturteenth() const;
    boost::gregorian::date sunteenth() const;

    // first
    boost::gregorian::date first_monday() const;
    boost::gregorian::date first_tuesday() const;
    boost::gregorian::date first_wednesday() const;
    boost::gregorian::date first_thursday() const;
    boost::gregorian::date first_friday() const;
    boost::gregorian::date first_saturday() const;
    boost::gregorian::date first_sunday() const;

    // second
    boost::gregorian::date second_monday() const;
    boost::gregorian::date second_tuesday() const;
    boost::gregorian::date second_wednesday() const;
    boost::gregorian::date second_thursday() const;
    boost::gregorian::date second_friday() const;
    boost::gregorian::date second_saturday() const;
    boost::gregorian::date second_sunday() const;

    // third
    boost::gregorian::date third_monday() const;
    boost::gregorian::date third_tuesday() const;
    boost::gregorian::date third_wednesday() const;
    boost::gregorian::date third_thursday() const;
    boost::gregorian::date third_friday() const;
    boost::gregorian::date third_saturday() const;
    boost::gregorian::date third_sunday() const;

    // fourth
    boost::gregorian::date fourth_monday() const;
    boost::gregorian::date fourth_tuesday() const;
    boost::gregorian::date fourth_wednesday() const;
    boost::gregorian::date fourth_thursday() const;
    boost::gregorian::date fourth_friday() const;
    boost::gregorian::date fourth_saturday() const;
    boost::gregorian::date fourth_sunday() const;

    // last
    boost::gregorian::date last_monday() const;
    boost::gregorian::date last_tuesday() const;
    boost::gregorian::date last_wednesday() const;
    boost::gregorian::date last_thursday() const;
    boost::gregorian::date last_friday() const;
    boost::gregorian::date last_saturday() const;
    boost::gregorian::date last_sunday() const;

private:
    boost::gregorian::date first_of_month_;

    boost::gregorian::date nth_weekday(unsigned n, boost::date_time::weekdays wd) const;
    boost::gregorian::date last_weekday(boost::date_time::weekdays wd) const;
    boost::gregorian::date teenth_weekday(boost::date_time::weekdays wd) const;
};

}  // namespace meetup

#endif // MEETUP_H
