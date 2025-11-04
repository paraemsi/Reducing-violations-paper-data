#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using date = boost::gregorian::date;
using weekday = boost::gregorian::greg_weekday;

class scheduler {
public:
    scheduler(int year, int month) noexcept;

    // teenth weekday helpers
    date monteenth() const noexcept;
    date tuesteenth() const noexcept;
    date wednesteenth() const noexcept;
    date thursteenth() const noexcept;
    date friteenth() const noexcept;
    date saturteenth() const noexcept;
    date sunteenth() const noexcept;

    // first weekday
    date first_monday() const noexcept;
    date first_tuesday() const noexcept;
    date first_wednesday() const noexcept;
    date first_thursday() const noexcept;
    date first_friday() const noexcept;
    date first_saturday() const noexcept;
    date first_sunday() const noexcept;

    // second weekday
    date second_monday() const noexcept;
    date second_tuesday() const noexcept;
    date second_wednesday() const noexcept;
    date second_thursday() const noexcept;
    date second_friday() const noexcept;
    date second_saturday() const noexcept;
    date second_sunday() const noexcept;

    // third weekday
    date third_monday() const noexcept;
    date third_tuesday() const noexcept;
    date third_wednesday() const noexcept;
    date third_thursday() const noexcept;
    date third_friday() const noexcept;
    date third_saturday() const noexcept;
    date third_sunday() const noexcept;

    // fourth weekday
    date fourth_monday() const noexcept;
    date fourth_tuesday() const noexcept;
    date fourth_wednesday() const noexcept;
    date fourth_thursday() const noexcept;
    date fourth_friday() const noexcept;
    date fourth_saturday() const noexcept;
    date fourth_sunday() const noexcept;

    // last weekday
    date last_monday() const noexcept;
    date last_tuesday() const noexcept;
    date last_wednesday() const noexcept;
    date last_thursday() const noexcept;
    date last_friday() const noexcept;
    date last_saturday() const noexcept;
    date last_sunday() const noexcept;

private:
    int year_;
    unsigned month_;

    date nth_weekday(int n, weekday wd) const;
    date last_weekday(weekday wd) const;
    date teenth_weekday(weekday wd) const;
};

}  // namespace meetup

#endif // MEETUP_H
