#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <map>
#include <stdexcept>

namespace meetup {


scheduler::scheduler(int month, int year)
    : month_(month), year_(year) {
    if (month < 1 || month > 12) {
        throw std::domain_error("invalid month");
    }
}

int scheduler::monteenth() const { return meetup_day("Monday", "teenth"); }
int scheduler::tuesteenth() const { return meetup_day("Tuesday", "teenth"); }
int scheduler::wednesteenth() const { return meetup_day("Wednesday", "teenth"); }
int scheduler::thursteenth() const { return meetup_day("Thursday", "teenth"); }
int scheduler::friteenth() const { return meetup_day("Friday", "teenth"); }
int scheduler::saturteenth() const { return meetup_day("Saturday", "teenth"); }
int scheduler::sunteenth() const { return meetup_day("Sunday", "teenth"); }
int scheduler::first_monday() const { return meetup_day("Monday", "first"); }
int scheduler::first_tuesday() const { return meetup_day("Tuesday", "first"); }
int scheduler::first_wednesday() const { return meetup_day("Wednesday", "first"); }
int scheduler::first_thursday() const { return meetup_day("Thursday", "first"); }
int scheduler::first_friday() const { return meetup_day("Friday", "first"); }
int scheduler::first_saturday() const { return meetup_day("Saturday", "first"); }
int scheduler::first_sunday() const { return meetup_day("Sunday", "first"); }
int scheduler::second_monday() const { return meetup_day("Monday", "second"); }
int scheduler::second_tuesday() const { return meetup_day("Tuesday", "second"); }
int scheduler::second_wednesday() const { return meetup_day("Wednesday", "second"); }
int scheduler::second_thursday() const { return meetup_day("Thursday", "second"); }
int scheduler::second_friday() const { return meetup_day("Friday", "second"); }
int scheduler::second_saturday() const { return meetup_day("Saturday", "second"); }
int scheduler::second_sunday() const { return meetup_day("Sunday", "second"); }
int scheduler::third_monday() const { return meetup_day("Monday", "third"); }
int scheduler::third_tuesday() const { return meetup_day("Tuesday", "third"); }
int scheduler::third_wednesday() const { return meetup_day("Wednesday", "third"); }
int scheduler::third_thursday() const { return meetup_day("Thursday", "third"); }
int scheduler::third_friday() const { return meetup_day("Friday", "third"); }
int scheduler::third_saturday() const { return meetup_day("Saturday", "third"); }
int scheduler::third_sunday() const { return meetup_day("Sunday", "third"); }
int scheduler::fourth_monday() const { return meetup_day("Monday", "fourth"); }
int scheduler::fourth_tuesday() const { return meetup_day("Tuesday", "fourth"); }
int scheduler::fourth_wednesday() const { return meetup_day("Wednesday", "fourth"); }
int scheduler::fourth_thursday() const { return meetup_day("Thursday", "fourth"); }
int scheduler::fourth_friday() const { return meetup_day("Friday", "fourth"); }
int scheduler::fourth_saturday() const { return meetup_day("Saturday", "fourth"); }
int scheduler::fourth_sunday() const { return meetup_day("Sunday", "fourth"); }
int scheduler::last_monday() const { return meetup_day("Monday", "last"); }
int scheduler::last_tuesday() const { return meetup_day("Tuesday", "last"); }
int scheduler::last_wednesday() const { return meetup_day("Wednesday", "last"); }
int scheduler::last_thursday() const { return meetup_day("Thursday", "last"); }
int scheduler::last_friday() const { return meetup_day("Friday", "last"); }
int scheduler::last_saturday() const { return meetup_day("Saturday", "last"); }
int scheduler::last_sunday() const { return meetup_day("Sunday", "last"); }

int scheduler::meetup_day(const std::string& weekday,
                          const std::string& week) const {
    namespace gregorian = boost::gregorian;

    static const std::map<std::string, gregorian::weekday> weekday_map{
        {"Sunday", gregorian::Sunday}, {"Monday", gregorian::Monday},
        {"Tuesday", gregorian::Tuesday}, {"Wednesday", gregorian::Wednesday},
        {"Thursday", gregorian::Thursday}, {"Friday", gregorian::Friday},
        {"Saturday", gregorian::Saturday}};
    const auto target_wday = weekday_map.at(weekday);

    if (week == "teenth") {
        for (int day = 13; day <= 19; ++day) {
            gregorian::date d(year_, month_, day);
            if (d.day_of_week() == target_wday) {
                return day;
            }
        }
    } else if (week == "last") {
        gregorian::last_day_of_week_in_month ldotwim(target_wday, month_);
        return ldotwim.get_date(year_).day();
    } else {
        static const std::map<std::string, gregorian::nth_day_of_week_in_month::week_num> week_map{
            {"first", gregorian::nth_day_of_week_in_month::first},
            {"second", gregorian::nth_day_of_week_in_month::second},
            {"third", gregorian::nth_day_of_week_in_month::third},
            {"fourth", gregorian::nth_day_of_week_in_month::fourth},
        };
        const auto it = week_map.find(week);
        if (it != week_map.end()) {
            gregorian::nth_day_of_week_in_month ndotwim(it->second, target_wday, month_);
            return ndotwim.get_date(year_).day();
        }
    }

    throw std::domain_error("invalid week");
}

}  // namespace meetup
