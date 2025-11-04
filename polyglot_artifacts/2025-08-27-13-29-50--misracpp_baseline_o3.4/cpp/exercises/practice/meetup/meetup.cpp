#include "meetup.h"

using boost::gregorian::date;

namespace meetup {

scheduler::scheduler(int month, int year)
    : m_month(month), m_year(year) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument{"month must be in 1..12"};
    }
}

namespace {

// helper to convert our enum 'schedule' to an ordinal index (1-based)
inline int ordinal_index(schedule s) {
    switch (s) {
    case schedule::first:  return 1;
    case schedule::second: return 2;
    case schedule::third:  return 3;
    case schedule::fourth: return 4;
    case schedule::fifth:  return 5;
    default:               return 0;   // teenth / last handled separately
    }
}

} // anonymous namespace

date scheduler::day(boost::date_time::weekdays desired_weekday,
                    schedule s) const {
    const int y = m_year;
    const int m = m_month;

    // Handle "teenth" specially
    if (s == schedule::teenth) {
        for (int d = 13; d <= 19; ++d) {
            date current{y, m, d};
            if (current.day_of_week().as_number() == desired_weekday) {
                return current;
            }
        }
        throw std::logic_error{"no teenth day found – unreachable"};
    }

    // Handle "last" by walking backwards from end-of-month
    if (s == schedule::last) {
        int last_dom = boost::gregorian::gregorian_calendar::end_of_month_day(
            y, static_cast<unsigned short>(m));
        for (int d = last_dom; d >= last_dom - 6; --d) {
            date current{y, m, d};
            if (current.day_of_week().as_number() == desired_weekday) {
                return current;
            }
        }
        throw std::logic_error{"no last weekday found – unreachable"};
    }

    // Ordinal occurrences (1-5)
    int index = ordinal_index(s);
    int day_start = 1 + 7 * (index - 1);          // 1,8,15,22,29
    for (int d = day_start; d < day_start + 7; ++d) {
        // Guard against months that have no 5th occurrence
        if (d > boost::gregorian::gregorian_calendar::end_of_month_day(
                    y, static_cast<unsigned short>(m))) {
            throw std::domain_error{"requested occurrence does not exist"};
        }
        date current{y, m, d};
        if (current.day_of_week().as_number() == desired_weekday) {
            return current;
        }
    }

    throw std::logic_error{"weekday not found – unreachable"};
}

/* ---- helper to avoid repetition ---- */
inline date pick(const scheduler& sch, boost::date_time::weekdays wd, schedule s)
{
    return sch.day(wd, s);
}

/* ---- teenth ---- */
date scheduler::monteenth()  const { return pick(*this, boost::date_time::Monday,    schedule::teenth); }
date scheduler::tuesteenth() const { return pick(*this, boost::date_time::Tuesday,   schedule::teenth); }
date scheduler::wednesteenth() const { return pick(*this, boost::date_time::Wednesday, schedule::teenth); }
date scheduler::thursteenth() const { return pick(*this, boost::date_time::Thursday,  schedule::teenth); }
date scheduler::friteenth()   const { return pick(*this, boost::date_time::Friday,    schedule::teenth); }
date scheduler::saturteenth() const { return pick(*this, boost::date_time::Saturday,  schedule::teenth); }
date scheduler::sunteenth()   const { return pick(*this, boost::date_time::Sunday,    schedule::teenth); }

/* ---- ordinal helpers ---- */
#define MAKE_ORDINAL(ORD, ENUM) \
    date scheduler::ORD##_monday()    const { return pick(*this, boost::date_time::Monday,    schedule::ENUM); } \
    date scheduler::ORD##_tuesday()   const { return pick(*this, boost::date_time::Tuesday,   schedule::ENUM); } \
    date scheduler::ORD##_wednesday() const { return pick(*this, boost::date_time::Wednesday, schedule::ENUM); } \
    date scheduler::ORD##_thursday()  const { return pick(*this, boost::date_time::Thursday,  schedule::ENUM); } \
    date scheduler::ORD##_friday()    const { return pick(*this, boost::date_time::Friday,    schedule::ENUM); } \
    date scheduler::ORD##_saturday()  const { return pick(*this, boost::date_time::Saturday,  schedule::ENUM); } \
    date scheduler::ORD##_sunday()    const { return pick(*this, boost::date_time::Sunday,    schedule::ENUM); }

MAKE_ORDINAL(first,  first)
MAKE_ORDINAL(second, second)
MAKE_ORDINAL(third,  third)
MAKE_ORDINAL(fourth, fourth)
MAKE_ORDINAL(last,   last)

#undef MAKE_ORDINAL

} // namespace meetup
