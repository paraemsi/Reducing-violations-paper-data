#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

enum class weekday : std::uint8_t {
    Sunday    = 0U,
    Monday    = 1U,
    Tuesday   = 2U,
    Wednesday = 3U,
    Thursday  = 4U,
    Friday    = 5U,
    Saturday  = 6U
};

enum class schedule : std::uint8_t {
    first  = 1U,
    second = 2U,
    third  = 3U,
    fourth = 4U,
    last   = 5U,
    teenth = 6U
};

class scheduler
{
public:
    scheduler(::boost::gregorian::greg_month month, std::int32_t year) noexcept;

    /* "teenth" occurrences */
    ::boost::gregorian::date monteenth() const;
    ::boost::gregorian::date tuesteenth() const;
    ::boost::gregorian::date wednesteenth() const;
    ::boost::gregorian::date thursteenth() const;
    ::boost::gregorian::date friteenth() const;
    ::boost::gregorian::date saturteenth() const;
    ::boost::gregorian::date sunteenth() const;

    /* first occurrences */
    ::boost::gregorian::date first_monday() const;
    ::boost::gregorian::date first_tuesday() const;
    ::boost::gregorian::date first_wednesday() const;
    ::boost::gregorian::date first_thursday() const;
    ::boost::gregorian::date first_friday() const;
    ::boost::gregorian::date first_saturday() const;
    ::boost::gregorian::date first_sunday() const;

    /* second occurrences */
    ::boost::gregorian::date second_monday() const;
    ::boost::gregorian::date second_tuesday() const;
    ::boost::gregorian::date second_wednesday() const;
    ::boost::gregorian::date second_thursday() const;
    ::boost::gregorian::date second_friday() const;
    ::boost::gregorian::date second_saturday() const;
    ::boost::gregorian::date second_sunday() const;

    /* third occurrences */
    ::boost::gregorian::date third_monday() const;
    ::boost::gregorian::date third_tuesday() const;
    ::boost::gregorian::date third_wednesday() const;
    ::boost::gregorian::date third_thursday() const;
    ::boost::gregorian::date third_friday() const;
    ::boost::gregorian::date third_saturday() const;
    ::boost::gregorian::date third_sunday() const;

    /* fourth occurrences */
    ::boost::gregorian::date fourth_monday() const;
    ::boost::gregorian::date fourth_tuesday() const;
    ::boost::gregorian::date fourth_wednesday() const;
    ::boost::gregorian::date fourth_thursday() const;
    ::boost::gregorian::date fourth_friday() const;
    ::boost::gregorian::date fourth_saturday() const;
    ::boost::gregorian::date fourth_sunday() const;

    /* last occurrences */
    ::boost::gregorian::date last_monday() const;
    ::boost::gregorian::date last_tuesday() const;
    ::boost::gregorian::date last_wednesday() const;
    ::boost::gregorian::date last_thursday() const;
    ::boost::gregorian::date last_friday() const;
    ::boost::gregorian::date last_saturday() const;
    ::boost::gregorian::date last_sunday() const;

private:
    ::boost::gregorian::date nth_weekday(schedule sched, weekday wday) const;

    ::boost::gregorian::greg_month month_;
    std::int32_t                   year_;
};

}  // namespace meetup

#endif // MEETUP_H
