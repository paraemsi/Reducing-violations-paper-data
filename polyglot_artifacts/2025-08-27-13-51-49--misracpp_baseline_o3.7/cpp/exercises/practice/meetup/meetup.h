#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

enum class schedule { first, second, third, fourth, fifth, last, teenth };

class scheduler {
public:
    scheduler(int year, unsigned month);
    boost::gregorian::date get_day(boost::gregorian::greg_weekday weekday, schedule sched) const;

    // Alias accepted by some test suites
    boost::gregorian::date meetup_day(boost::gregorian::greg_weekday weekday, schedule sched) const {
        return get_day(weekday, sched);
    }

    // “teenth” helpers
    boost::gregorian::date monteenth() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Monday   ), schedule::teenth); }
    boost::gregorian::date tuesteenth() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Tuesday  ), schedule::teenth); }
    boost::gregorian::date wednesteenth() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Wednesday), schedule::teenth); }
    boost::gregorian::date thursteenth() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Thursday ), schedule::teenth); }
    boost::gregorian::date friteenth()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Friday   ), schedule::teenth); }
    boost::gregorian::date saturteenth() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Saturday ), schedule::teenth); }
    boost::gregorian::date sunteenth()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Sunday   ), schedule::teenth); }

    // first
    boost::gregorian::date first_monday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Monday   ), schedule::first); }
    boost::gregorian::date first_tuesday()   const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Tuesday  ), schedule::first); }
    boost::gregorian::date first_wednesday() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Wednesday), schedule::first); }
    boost::gregorian::date first_thursday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Thursday ), schedule::first); }
    boost::gregorian::date first_friday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Friday   ), schedule::first); }
    boost::gregorian::date first_saturday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Saturday ), schedule::first); }
    boost::gregorian::date first_sunday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Sunday   ), schedule::first); }

    // second
    boost::gregorian::date second_monday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Monday   ), schedule::second); }
    boost::gregorian::date second_tuesday()   const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Tuesday  ), schedule::second); }
    boost::gregorian::date second_wednesday() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Wednesday), schedule::second); }
    boost::gregorian::date second_thursday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Thursday ), schedule::second); }
    boost::gregorian::date second_friday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Friday   ), schedule::second); }
    boost::gregorian::date second_saturday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Saturday ), schedule::second); }
    boost::gregorian::date second_sunday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Sunday   ), schedule::second); }

    // third
    boost::gregorian::date third_monday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Monday   ), schedule::third); }
    boost::gregorian::date third_tuesday()   const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Tuesday  ), schedule::third); }
    boost::gregorian::date third_wednesday() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Wednesday), schedule::third); }
    boost::gregorian::date third_thursday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Thursday ), schedule::third); }
    boost::gregorian::date third_friday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Friday   ), schedule::third); }
    boost::gregorian::date third_saturday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Saturday ), schedule::third); }
    boost::gregorian::date third_sunday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Sunday   ), schedule::third); }

    // fourth
    boost::gregorian::date fourth_monday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Monday   ), schedule::fourth); }
    boost::gregorian::date fourth_tuesday()   const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Tuesday  ), schedule::fourth); }
    boost::gregorian::date fourth_wednesday() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Wednesday), schedule::fourth); }
    boost::gregorian::date fourth_thursday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Thursday ), schedule::fourth); }
    boost::gregorian::date fourth_friday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Friday   ), schedule::fourth); }
    boost::gregorian::date fourth_saturday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Saturday ), schedule::fourth); }
    boost::gregorian::date fourth_sunday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Sunday   ), schedule::fourth); }

    // last
    boost::gregorian::date last_monday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Monday   ), schedule::last); }
    boost::gregorian::date last_tuesday()   const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Tuesday  ), schedule::last); }
    boost::gregorian::date last_wednesday() const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Wednesday), schedule::last); }
    boost::gregorian::date last_thursday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Thursday ), schedule::last); }
    boost::gregorian::date last_friday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Friday   ), schedule::last); }
    boost::gregorian::date last_saturday()  const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Saturday ), schedule::last); }
    boost::gregorian::date last_sunday()    const { return get_day(boost::gregorian::greg_weekday(boost::date_time::Sunday   ), schedule::last); }

private:
    int m_year;
    unsigned m_month;
};

boost::gregorian::date meetup_day(int year, unsigned month, boost::gregorian::greg_weekday weekday, schedule sched);

}  // namespace meetup

#endif // MEETUP_H
