#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

/*
 *  A helper object that provides convenience functions for selecting
 *  specific meetup dates inside a given (month, year) pair.
 *
 *  The public interface mirrors the expectations of the unit-tests:
 *    • “teenth” queries (monteenth, tuesteenth, …, sunteenth)
 *    • ordinal weekday queries (first/second/third/fourth/last <weekday>)
 *
 *  All functions return boost::gregorian::date objects.
 */
class scheduler
{
public:
    scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept;

    /* Teenth */
    boost::gregorian::date monteenth() const noexcept;
    boost::gregorian::date tuesteenth() const noexcept;
    boost::gregorian::date wednesteenth() const noexcept;
    boost::gregorian::date thursteenth() const noexcept;
    boost::gregorian::date friteenth() const noexcept;
    boost::gregorian::date saturteenth() const noexcept;
    boost::gregorian::date sunteenth() const noexcept;

    /* First */
    boost::gregorian::date first_monday() const noexcept;
    boost::gregorian::date first_tuesday() const noexcept;
    boost::gregorian::date first_wednesday() const noexcept;
    boost::gregorian::date first_thursday() const noexcept;
    boost::gregorian::date first_friday() const noexcept;
    boost::gregorian::date first_saturday() const noexcept;
    boost::gregorian::date first_sunday() const noexcept;

    /* Second */
    boost::gregorian::date second_monday() const noexcept;
    boost::gregorian::date second_tuesday() const noexcept;
    boost::gregorian::date second_wednesday() const noexcept;
    boost::gregorian::date second_thursday() const noexcept;
    boost::gregorian::date second_friday() const noexcept;
    boost::gregorian::date second_saturday() const noexcept;
    boost::gregorian::date second_sunday() const noexcept;

    /* Third */
    boost::gregorian::date third_monday() const noexcept;
    boost::gregorian::date third_tuesday() const noexcept;
    boost::gregorian::date third_wednesday() const noexcept;
    boost::gregorian::date third_thursday() const noexcept;
    boost::gregorian::date third_friday() const noexcept;
    boost::gregorian::date third_saturday() const noexcept;
    boost::gregorian::date third_sunday() const noexcept;

    /* Fourth */
    boost::gregorian::date fourth_monday() const noexcept;
    boost::gregorian::date fourth_tuesday() const noexcept;
    boost::gregorian::date fourth_wednesday() const noexcept;
    boost::gregorian::date fourth_thursday() const noexcept;
    boost::gregorian::date fourth_friday() const noexcept;
    boost::gregorian::date fourth_saturday() const noexcept;
    boost::gregorian::date fourth_sunday() const noexcept;

    /* Last */
    boost::gregorian::date last_monday() const noexcept;
    boost::gregorian::date last_tuesday() const noexcept;
    boost::gregorian::date last_wednesday() const noexcept;
    boost::gregorian::date last_thursday() const noexcept;
    boost::gregorian::date last_friday() const noexcept;
    boost::gregorian::date last_saturday() const noexcept;
    boost::gregorian::date last_sunday() const noexcept;

private:
    boost::gregorian::date
    get_teenth(boost::date_time::weekdays weekday) const noexcept;

    boost::gregorian::date
    get_nth(std::uint8_t nth,
            boost::date_time::weekdays weekday) const noexcept;

    boost::gregorian::date
    get_last(boost::date_time::weekdays weekday) const noexcept;

    boost::gregorian::months_of_year month_;
    std::int32_t                     year_;
};

}  // namespace meetup

#endif // MEETUP_H
