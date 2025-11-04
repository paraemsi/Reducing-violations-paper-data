#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

enum class schedule {
    first,
    second,
    third,
    fourth,
    last,
    teenth
};

class scheduler {
public:
    explicit scheduler(int year, unsigned int month)
        : m_year{year}, m_month{month} {}

    boost::gregorian::date
    meetup_day(boost::date_time::weekdays wd, schedule sc) const;

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
    int m_year;
    unsigned int m_month;
};

/* Generated convenience wrapper implementations */

inline boost::gregorian::date scheduler::monteenth() const  { return meetup_day(boost::date_time::Monday,    schedule::teenth); }
inline boost::gregorian::date scheduler::tuesteenth() const { return meetup_day(boost::date_time::Tuesday,   schedule::teenth); }
inline boost::gregorian::date scheduler::wednesteenth() const { return meetup_day(boost::date_time::Wednesday, schedule::teenth); }
inline boost::gregorian::date scheduler::thursteenth() const { return meetup_day(boost::date_time::Thursday,  schedule::teenth); }
inline boost::gregorian::date scheduler::friteenth() const  { return meetup_day(boost::date_time::Friday,    schedule::teenth); }
inline boost::gregorian::date scheduler::saturteenth() const{ return meetup_day(boost::date_time::Saturday,  schedule::teenth); }
inline boost::gregorian::date scheduler::sunteenth() const  { return meetup_day(boost::date_time::Sunday,    schedule::teenth); }

#define MAKE_FUNCS(dayname_lower, DAYENUM) \
    inline boost::gregorian::date scheduler::first_##dayname_lower()  const { return meetup_day(boost::date_time::DAYENUM, schedule::first); } \
    inline boost::gregorian::date scheduler::second_##dayname_lower() const { return meetup_day(boost::date_time::DAYENUM, schedule::second); } \
    inline boost::gregorian::date scheduler::third_##dayname_lower()  const { return meetup_day(boost::date_time::DAYENUM, schedule::third); } \
    inline boost::gregorian::date scheduler::fourth_##dayname_lower() const { return meetup_day(boost::date_time::DAYENUM, schedule::fourth); } \
    inline boost::gregorian::date scheduler::last_##dayname_lower()   const { return meetup_day(boost::date_time::DAYENUM, schedule::last); }

MAKE_FUNCS(monday,    Monday)
MAKE_FUNCS(tuesday,   Tuesday)
MAKE_FUNCS(wednesday, Wednesday)
MAKE_FUNCS(thursday,  Thursday)
MAKE_FUNCS(friday,    Friday)
MAKE_FUNCS(saturday,  Saturday)
MAKE_FUNCS(sunday,    Sunday)

#undef MAKE_FUNCS

}  // namespace meetup

#endif // MEETUP_H
