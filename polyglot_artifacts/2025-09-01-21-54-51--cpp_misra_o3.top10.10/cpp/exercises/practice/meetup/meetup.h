#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

/* Enumeration representing the days of the week.
 * The underlying type is std::uint8_t to comply with the fixed-width rule.
 * The sequence starts with monday == 0 so that simple modular arithmetic
 * can be used when needed.
 */
enum class Weekday : std::uint8_t
{
    monday   = 0U,
    tuesday  = 1U,
    wednesday= 2U,
    thursday = 3U,
    friday   = 4U,
    saturday = 5U,
    sunday   = 6U
};

/* Enumeration representing the required schedule
 * (first/second/third/fourth/last/teenth).
 */
enum class Schedule : std::uint8_t
{
    first  = 0U,
    second = 1U,
    third  = 2U,
    fourth = 3U,
    last   = 4U,
    teenth = 5U
};

/* Lightweight date structure – small, trivially copyable, and independent
 * of any specific calendar library.  All fields use fixed-width types.
 */
struct date final
{
    std::int32_t year;   /* full gregorian year (e.g. 2025)              */
    std::uint8_t month;  /* 1-12                                          */
    std::uint8_t day;    /* 1-31 (validated by the implementation code)  */
};

/* Compute the exact meetup day for the given parameters.
 * Any invalid combination (e.g. “fifth Tuesday” when only four exist)
 * results in std::invalid_argument being thrown.
 */
date meetup_day(std::int32_t year,
                std::uint8_t month,
                Weekday weekday,
                Schedule schedule);

/* ------------------------------------------------------------------------- */
/*  Class modelling a month/year meetup schedule (API required by tests).    */
/* ------------------------------------------------------------------------- */
class scheduler final
{
public:
    /* Construct with Boost month enumeration and gregorian year.            */
    scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept;

    /* ----------- “teenth” helpers ---------------------------------------- */
    boost::gregorian::date monteenth() const;
    boost::gregorian::date tuesteenth() const;
    boost::gregorian::date wednesteenth() const;
    boost::gregorian::date thursteenth() const;
    boost::gregorian::date friteenth() const;
    boost::gregorian::date saturteenth() const;
    boost::gregorian::date sunteenth() const;

    /* ----------- first helpers ------------------------------------------- */
    boost::gregorian::date first_monday() const;
    boost::gregorian::date first_tuesday() const;
    boost::gregorian::date first_wednesday() const;
    boost::gregorian::date first_thursday() const;
    boost::gregorian::date first_friday() const;
    boost::gregorian::date first_saturday() const;
    boost::gregorian::date first_sunday() const;

    /* ----------- second helpers ------------------------------------------ */
    boost::gregorian::date second_monday() const;
    boost::gregorian::date second_tuesday() const;
    boost::gregorian::date second_wednesday() const;
    boost::gregorian::date second_thursday() const;
    boost::gregorian::date second_friday() const;
    boost::gregorian::date second_saturday() const;
    boost::gregorian::date second_sunday() const;

    /* ----------- third helpers ------------------------------------------- */
    boost::gregorian::date third_monday() const;
    boost::gregorian::date third_tuesday() const;
    boost::gregorian::date third_wednesday() const;
    boost::gregorian::date third_thursday() const;
    boost::gregorian::date third_friday() const;
    boost::gregorian::date third_saturday() const;
    boost::gregorian::date third_sunday() const;

    /* ----------- fourth helpers ------------------------------------------ */
    boost::gregorian::date fourth_monday() const;
    boost::gregorian::date fourth_tuesday() const;
    boost::gregorian::date fourth_wednesday() const;
    boost::gregorian::date fourth_thursday() const;
    boost::gregorian::date fourth_friday() const;
    boost::gregorian::date fourth_saturday() const;
    boost::gregorian::date fourth_sunday() const;

    /* ----------- last helpers -------------------------------------------- */
    boost::gregorian::date last_monday() const;
    boost::gregorian::date last_tuesday() const;
    boost::gregorian::date last_wednesday() const;
    boost::gregorian::date last_thursday() const;
    boost::gregorian::date last_friday() const;
    boost::gregorian::date last_saturday() const;
    boost::gregorian::date last_sunday() const;

private:
    boost::gregorian::date
    make_date(Weekday weekday, Schedule schedule) const;

    std::int32_t m_year;
    std::uint8_t m_month;
};

}  // namespace meetup

#endif // MEETUP_H
