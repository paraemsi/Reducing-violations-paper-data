#include "meetup.h"
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {

constexpr Weekday weekday_from_index(int idx)
{
    switch(idx) {
        case 0: return Weekday::Sunday;
        case 1: return Weekday::Monday;
        case 2: return Weekday::Tuesday;
        case 3: return Weekday::Wednesday;
        case 4: return Weekday::Thursday;
        case 5: return Weekday::Friday;
        case 6: return Weekday::Saturday;
        default: return Weekday::Sunday;
    }
}

constexpr int index_from_weekday(Weekday wd)
{
    switch(wd) {
        case Weekday::Sunday: return 0;
        case Weekday::Monday: return 1;
        case Weekday::Tuesday: return 2;
        case Weekday::Wednesday: return 3;
        case Weekday::Thursday: return 4;
        case Weekday::Friday: return 5;
        case Weekday::Saturday: return 6;
        default: return 0;
    }
}

} // anonymous namespace

scheduler::scheduler(::boost::gregorian::months_of_year month, year_t year)
    : m_month(static_cast<month_t>(month)), m_year(year)
{
}

day_t scheduler::get_day(Weekday weekday, Schedule schedule) const
{
    using namespace boost::gregorian;
    int wd = index_from_weekday(weekday);
    date first_of_month(static_cast<int>(m_year), static_cast<int>(m_month), 1);
    int first_wd = static_cast<int>(first_of_month.day_of_week());
    int day_of_month = 0;

    if(schedule == Schedule::Teenth) {
        for(int d = 13; d <= 19; ++d) {
            date dt(static_cast<int>(m_year), static_cast<int>(m_month), d);
            if(static_cast<int>(dt.day_of_week()) == wd) {
                day_of_month = d;
                break;
            }
        }
    } else if(schedule == Schedule::Last) {
        date end_of_month = first_of_month.end_of_month();
        int last_day = static_cast<int>(end_of_month.day());
        for(int d = last_day; d >= last_day - 6; --d) {
            date dt(static_cast<int>(m_year), static_cast<int>(m_month), d);
            if(static_cast<int>(dt.day_of_week()) == wd) {
                day_of_month = d;
                break;
            }
        }
    } else {
        int start = 1;
        if(schedule == Schedule::First) {
            start = 1;
        } else if(schedule == Schedule::Second) {
            start = 8;
        } else if(schedule == Schedule::Third) {
            start = 15;
        } else if(schedule == Schedule::Fourth) {
            start = 22;
        }
        for(int d = start; d < start + 7; ++d) {
            date dt(static_cast<int>(m_year), static_cast<int>(m_month), d);
            if(static_cast<int>(dt.day_of_week()) == wd) {
                day_of_month = d;
                break;
            }
        }
    }
    if(day_of_month == 0) {
        throw std::logic_error("No such meetup day in this month");
    }
    return static_cast<day_t>(day_of_month);
}

// Teenth
day_t scheduler::monteenth() const { return get_day(Weekday::Monday, Schedule::Teenth); }
day_t scheduler::tuesteenth() const { return get_day(Weekday::Tuesday, Schedule::Teenth); }
day_t scheduler::wednesteenth() const { return get_day(Weekday::Wednesday, Schedule::Teenth); }
day_t scheduler::thursteenth() const { return get_day(Weekday::Thursday, Schedule::Teenth); }
day_t scheduler::friteenth() const { return get_day(Weekday::Friday, Schedule::Teenth); }
day_t scheduler::saturteenth() const { return get_day(Weekday::Saturday, Schedule::Teenth); }
day_t scheduler::sunteenth() const { return get_day(Weekday::Sunday, Schedule::Teenth); }

// First
day_t scheduler::first_monday() const { return get_day(Weekday::Monday, Schedule::First); }
day_t scheduler::first_tuesday() const { return get_day(Weekday::Tuesday, Schedule::First); }
day_t scheduler::first_wednesday() const { return get_day(Weekday::Wednesday, Schedule::First); }
day_t scheduler::first_thursday() const { return get_day(Weekday::Thursday, Schedule::First); }
day_t scheduler::first_friday() const { return get_day(Weekday::Friday, Schedule::First); }
day_t scheduler::first_saturday() const { return get_day(Weekday::Saturday, Schedule::First); }
day_t scheduler::first_sunday() const { return get_day(Weekday::Sunday, Schedule::First); }

// Second
day_t scheduler::second_monday() const { return get_day(Weekday::Monday, Schedule::Second); }
day_t scheduler::second_tuesday() const { return get_day(Weekday::Tuesday, Schedule::Second); }
day_t scheduler::second_wednesday() const { return get_day(Weekday::Wednesday, Schedule::Second); }
day_t scheduler::second_thursday() const { return get_day(Weekday::Thursday, Schedule::Second); }
day_t scheduler::second_friday() const { return get_day(Weekday::Friday, Schedule::Second); }
day_t scheduler::second_saturday() const { return get_day(Weekday::Saturday, Schedule::Second); }
day_t scheduler::second_sunday() const { return get_day(Weekday::Sunday, Schedule::Second); }

// Third
day_t scheduler::third_monday() const { return get_day(Weekday::Monday, Schedule::Third); }
day_t scheduler::third_tuesday() const { return get_day(Weekday::Tuesday, Schedule::Third); }
day_t scheduler::third_wednesday() const { return get_day(Weekday::Wednesday, Schedule::Third); }
day_t scheduler::third_thursday() const { return get_day(Weekday::Thursday, Schedule::Third); }
day_t scheduler::third_friday() const { return get_day(Weekday::Friday, Schedule::Third); }
day_t scheduler::third_saturday() const { return get_day(Weekday::Saturday, Schedule::Third); }
day_t scheduler::third_sunday() const { return get_day(Weekday::Sunday, Schedule::Third); }

// Fourth
day_t scheduler::fourth_monday() const { return get_day(Weekday::Monday, Schedule::Fourth); }
day_t scheduler::fourth_tuesday() const { return get_day(Weekday::Tuesday, Schedule::Fourth); }
day_t scheduler::fourth_wednesday() const { return get_day(Weekday::Wednesday, Schedule::Fourth); }
day_t scheduler::fourth_thursday() const { return get_day(Weekday::Thursday, Schedule::Fourth); }
day_t scheduler::fourth_friday() const { return get_day(Weekday::Friday, Schedule::Fourth); }
day_t scheduler::fourth_saturday() const { return get_day(Weekday::Saturday, Schedule::Fourth); }
day_t scheduler::fourth_sunday() const { return get_day(Weekday::Sunday, Schedule::Fourth); }

// Last
day_t scheduler::last_monday() const { return get_day(Weekday::Monday, Schedule::Last); }
day_t scheduler::last_tuesday() const { return get_day(Weekday::Tuesday, Schedule::Last); }
day_t scheduler::last_wednesday() const { return get_day(Weekday::Wednesday, Schedule::Last); }
day_t scheduler::last_thursday() const { return get_day(Weekday::Thursday, Schedule::Last); }
day_t scheduler::last_friday() const { return get_day(Weekday::Friday, Schedule::Last); }
day_t scheduler::last_saturday() const { return get_day(Weekday::Saturday, Schedule::Last); }
day_t scheduler::last_sunday() const { return get_day(Weekday::Sunday, Schedule::Last); }

}  // namespace meetup
