#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

// Which occurrence of the weekday is being requested
enum class schedule {
    first,
    second,
    third,
    fourth,
    fifth,
    last,
    teenth
};

// Provides meetup–date calculations for a given month/year
class scheduler {
public:
    // month: 1–12, year: four-digit Gregorian year
    scheduler(int year, unsigned int month);

    // Return the exact day in the constructor’s month/year that satisfies
    // the requested weekday & schedule combination.
    // Example: day(boost::date_time::Friday, schedule::teenth)
    boost::gregorian::date
    day(boost::date_time::weekdays weekday, schedule s) const;

    // --- convenience helpers required by the tests ---
    boost::gregorian::date monteenth() const;
    boost::gregorian::date tuesteenth() const;
    boost::gregorian::date wednesteenth() const;
    boost::gregorian::date thursteenth() const;
    boost::gregorian::date friteenth() const;
    boost::gregorian::date saturteenth() const;
    boost::gregorian::date sunteenth() const;

    boost::gregorian::date first_monday() const;
    boost::gregorian::date first_tuesday() const;
    boost::gregorian::date first_wednesday() const;
    boost::gregorian::date first_thursday() const;
    boost::gregorian::date first_friday() const;
    boost::gregorian::date first_saturday() const;
    boost::gregorian::date first_sunday() const;

    boost::gregorian::date second_monday() const;
    boost::gregorian::date second_tuesday() const;
    boost::gregorian::date second_wednesday() const;
    boost::gregorian::date second_thursday() const;
    boost::gregorian::date second_friday() const;
    boost::gregorian::date second_saturday() const;
    boost::gregorian::date second_sunday() const;

    boost::gregorian::date third_monday() const;
    boost::gregorian::date third_tuesday() const;
    boost::gregorian::date third_wednesday() const;
    boost::gregorian::date third_thursday() const;
    boost::gregorian::date third_friday() const;
    boost::gregorian::date third_saturday() const;
    boost::gregorian::date third_sunday() const;

    boost::gregorian::date fourth_monday() const;
    boost::gregorian::date fourth_tuesday() const;
    boost::gregorian::date fourth_wednesday() const;
    boost::gregorian::date fourth_thursday() const;
    boost::gregorian::date fourth_friday() const;
    boost::gregorian::date fourth_saturday() const;
    boost::gregorian::date fourth_sunday() const;

    boost::gregorian::date last_monday() const;
    boost::gregorian::date last_tuesday() const;
    boost::gregorian::date last_wednesday() const;
    boost::gregorian::date last_thursday() const;
    boost::gregorian::date last_friday() const;
    boost::gregorian::date last_saturday() const;
    boost::gregorian::date last_sunday() const;

private:
    int  year_;
    unsigned int month_;
};

inline boost::gregorian::date scheduler::monteenth()  const { return day(boost::date_time::Monday   , schedule::teenth); }
inline boost::gregorian::date scheduler::tuesteenth() const { return day(boost::date_time::Tuesday  , schedule::teenth); }
inline boost::gregorian::date scheduler::wednesteenth() const { return day(boost::date_time::Wednesday, schedule::teenth); }
inline boost::gregorian::date scheduler::thursteenth() const { return day(boost::date_time::Thursday , schedule::teenth); }
inline boost::gregorian::date scheduler::friteenth()   const { return day(boost::date_time::Friday   , schedule::teenth); }
inline boost::gregorian::date scheduler::saturteenth() const { return day(boost::date_time::Saturday , schedule::teenth); }
inline boost::gregorian::date scheduler::sunteenth()   const { return day(boost::date_time::Sunday   , schedule::teenth); }

#define MEETUP_GEN(ORD, ORD_ENUM) \
inline boost::gregorian::date scheduler::ORD##_monday()    const { return day(boost::date_time::Monday   , schedule::ORD_ENUM); } \
inline boost::gregorian::date scheduler::ORD##_tuesday()   const { return day(boost::date_time::Tuesday  , schedule::ORD_ENUM); } \
inline boost::gregorian::date scheduler::ORD##_wednesday() const { return day(boost::date_time::Wednesday, schedule::ORD_ENUM); } \
inline boost::gregorian::date scheduler::ORD##_thursday()  const { return day(boost::date_time::Thursday , schedule::ORD_ENUM); } \
inline boost::gregorian::date scheduler::ORD##_friday()    const { return day(boost::date_time::Friday   , schedule::ORD_ENUM); } \
inline boost::gregorian::date scheduler::ORD##_saturday()  const { return day(boost::date_time::Saturday , schedule::ORD_ENUM); } \
inline boost::gregorian::date scheduler::ORD##_sunday()    const { return day(boost::date_time::Sunday   , schedule::ORD_ENUM); }

MEETUP_GEN(first , first)
MEETUP_GEN(second, second)
MEETUP_GEN(third , third)
MEETUP_GEN(fourth, fourth)
MEETUP_GEN(last  , last)

#undef MEETUP_GEN

}  // namespace meetup

#endif // MEETUP_H
