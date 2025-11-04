#include "meetup.h"

namespace meetup {

#if defined(__cpp_lib_chrono) && __cpp_lib_chrono >= 201907L

std::chrono::year_month_day meetup_day(std::chrono::year year,
                                       std::chrono::month month,
                                       std::chrono::weekday wd,
                                       schedule which) {
    using namespace std::chrono;

    const sys_days first_of_month = sys_days{year / month / day{1}};

    switch (which) {
        case schedule::first: {
            sys_days d = first_of_month + (wd - weekday{first_of_month});
            return year_month_day{d};
        }
        case schedule::second: {
            sys_days d = first_of_month + (wd - weekday{first_of_month}) + days{7};
            return year_month_day{d};
        }
        case schedule::third: {
            sys_days d = first_of_month + (wd - weekday{first_of_month}) + days{14};
            return year_month_day{d};
        }
        case schedule::fourth: {
            sys_days d = first_of_month + (wd - weekday{first_of_month}) + days{21};
            return year_month_day{d};
        }
        case schedule::last: {
            const sys_days last_of_month = sys_days{year_month_day_last{year, month / last}};
            sys_days d = last_of_month - (weekday{last_of_month} - wd);
            return year_month_day{d};
        }
        case schedule::teenth: {
            const sys_days thirteenth = sys_days{year / month / day{13}};
            sys_days d = thirteenth + (wd - weekday{thirteenth});
            return year_month_day{d};
        }
    }

    // Unreachable, but quiets potential compiler warnings.
    return year_month_day{};
}

#else

namespace {

// Gregorian leap year
inline bool is_leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

inline unsigned days_in_month(int y, unsigned m) {
    static const unsigned mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2) return mdays[1] + (is_leap(y) ? 1u : 0u);
    return mdays[m - 1];
}

// Day of week: 0=Sunday, 1=Monday, ..., 6=Saturday
inline int dow(int y, unsigned m, unsigned d) {
    static const int offsets[12] = {0,3,2,5,0,3,5,1,4,6,2,4};
    if (m < 3) y -= 1;
    int w = (y + y/4 - y/100 + y/400 + offsets[m - 1] + static_cast<int>(d)) % 7;
    if (w < 0) w += 7;
    return w;
}

} // unnamed namespace

date meetup_day(int year, unsigned month, weekday wd, schedule which) {
    int target = static_cast<int>(wd);
    unsigned dim = days_in_month(year, month);

    auto first_weekday = [&]() -> unsigned {
        int w0 = dow(year, month, 1);
        int delta = (target - w0 + 7) % 7;
        return 1u + static_cast<unsigned>(delta);
    };

    unsigned day = 0;
    switch (which) {
        case schedule::first:
            day = first_weekday();
            break;
        case schedule::second:
            day = first_weekday() + 7u;
            break;
        case schedule::third:
            day = first_weekday() + 14u;
            break;
        case schedule::fourth:
            day = first_weekday() + 21u;
            break;
        case schedule::last: {
            int w_last = dow(year, month, dim);
            int delta_back = (w_last - target + 7) % 7;
            day = dim - static_cast<unsigned>(delta_back);
            break;
        }
        case schedule::teenth: {
            int w13 = dow(year, month, 13u);
            int delta = (target - w13 + 7) % 7;
            day = 13u + static_cast<unsigned>(delta);
            break;
        }
    }

    return date{year, month, day};
}

#endif

// scheduler implementation (Boost-based)
namespace {

inline int weekday_number(const boost::gregorian::date& d) {
    // 0=Sunday, 1=Monday, ..., 6=Saturday
    return d.day_of_week().as_number();
}

} // unnamed namespace

scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : first_of_month_{boost::gregorian::date(year, month, 1)} {}

boost::gregorian::date scheduler::nth_weekday(unsigned n, boost::date_time::weekdays wd) const {
    const int target = static_cast<int>(wd);
    const int w0 = weekday_number(first_of_month_);
    const int delta = (target - w0 + 7) % 7;
    const unsigned day = 1u + static_cast<unsigned>(delta) + 7u * (n - 1u);
    return first_of_month_ + boost::gregorian::days(static_cast<long>(day) - 1L);
}

boost::gregorian::date scheduler::last_weekday(boost::date_time::weekdays wd) const {
    const boost::gregorian::date last = first_of_month_.end_of_month();
    const int target = static_cast<int>(wd);
    const int w_last = weekday_number(last);
    const int delta_back = (w_last - target + 7) % 7;
    return last - boost::gregorian::days(delta_back);
}

boost::gregorian::date scheduler::teenth_weekday(boost::date_time::weekdays wd) const {
    const boost::gregorian::date thirteenth(first_of_month_.year(), first_of_month_.month(), 13);
    const int target = static_cast<int>(wd);
    const int w13 = weekday_number(thirteenth);
    const int delta = (target - w13 + 7) % 7;
    return thirteenth + boost::gregorian::days(delta);
}

// teenth
boost::gregorian::date scheduler::monteenth() const { return teenth_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return teenth_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return teenth_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return teenth_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return teenth_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return teenth_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return teenth_weekday(boost::date_time::Sunday); }

// first
boost::gregorian::date scheduler::first_monday() const { return nth_weekday(1, boost::date_time::Monday); }
boost::gregorian::date scheduler::first_tuesday() const { return nth_weekday(1, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::first_wednesday() const { return nth_weekday(1, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::first_thursday() const { return nth_weekday(1, boost::date_time::Thursday); }
boost::gregorian::date scheduler::first_friday() const { return nth_weekday(1, boost::date_time::Friday); }
boost::gregorian::date scheduler::first_saturday() const { return nth_weekday(1, boost::date_time::Saturday); }
boost::gregorian::date scheduler::first_sunday() const { return nth_weekday(1, boost::date_time::Sunday); }

// second
boost::gregorian::date scheduler::second_monday() const { return nth_weekday(2, boost::date_time::Monday); }
boost::gregorian::date scheduler::second_tuesday() const { return nth_weekday(2, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::second_wednesday() const { return nth_weekday(2, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::second_thursday() const { return nth_weekday(2, boost::date_time::Thursday); }
boost::gregorian::date scheduler::second_friday() const { return nth_weekday(2, boost::date_time::Friday); }
boost::gregorian::date scheduler::second_saturday() const { return nth_weekday(2, boost::date_time::Saturday); }
boost::gregorian::date scheduler::second_sunday() const { return nth_weekday(2, boost::date_time::Sunday); }

// third
boost::gregorian::date scheduler::third_monday() const { return nth_weekday(3, boost::date_time::Monday); }
boost::gregorian::date scheduler::third_tuesday() const { return nth_weekday(3, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::third_wednesday() const { return nth_weekday(3, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::third_thursday() const { return nth_weekday(3, boost::date_time::Thursday); }
boost::gregorian::date scheduler::third_friday() const { return nth_weekday(3, boost::date_time::Friday); }
boost::gregorian::date scheduler::third_saturday() const { return nth_weekday(3, boost::date_time::Saturday); }
boost::gregorian::date scheduler::third_sunday() const { return nth_weekday(3, boost::date_time::Sunday); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return nth_weekday(4, boost::date_time::Monday); }
boost::gregorian::date scheduler::fourth_tuesday() const { return nth_weekday(4, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::fourth_wednesday() const { return nth_weekday(4, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::fourth_thursday() const { return nth_weekday(4, boost::date_time::Thursday); }
boost::gregorian::date scheduler::fourth_friday() const { return nth_weekday(4, boost::date_time::Friday); }
boost::gregorian::date scheduler::fourth_saturday() const { return nth_weekday(4, boost::date_time::Saturday); }
boost::gregorian::date scheduler::fourth_sunday() const { return nth_weekday(4, boost::date_time::Sunday); }

// last
boost::gregorian::date scheduler::last_monday() const { return last_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return last_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return last_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return last_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return last_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return last_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return last_weekday(boost::date_time::Sunday); }

} // namespace meetup
