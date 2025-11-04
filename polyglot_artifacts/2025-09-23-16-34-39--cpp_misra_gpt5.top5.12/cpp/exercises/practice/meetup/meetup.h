#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>


namespace meetup {

enum class weekday : std::uint8_t {
    sunday = 0U,
    monday = 1U,
    tuesday = 2U,
    wednesday = 3U,
    thursday = 4U,
    friday = 5U,
    saturday = 6U
};

enum class schedule : std::uint8_t {
    first = 1U,
    second = 2U,
    third = 3U,
    fourth = 4U,
    last = 5U,
    teenth = 6U
};

class scheduler {
public:
    scheduler(std::uint16_t year, std::uint8_t month) noexcept;
    // Overload to support construction as {month, year} (e.g., {May, 2013})
    scheduler(std::uint8_t month, std::uint16_t year) noexcept;
    // Overload to accept {boost::gregorian::MonthEnum, 2013} without narrowing
    scheduler(std::int32_t month, std::int32_t year) noexcept;

    // Returns the day-of-month (1..31) for the requested weekday/schedule.
    std::uint8_t day(weekday which_weekday, schedule which_schedule) const;

    // Teenth dates
    boost::gregorian::date monteenth() const;
    boost::gregorian::date tuesteenth() const;
    boost::gregorian::date wednesteenth() const;
    boost::gregorian::date thursteenth() const;
    boost::gregorian::date friteenth() const;
    boost::gregorian::date saturteenth() const;
    boost::gregorian::date sunteenth() const;

    // First
    boost::gregorian::date first_monday() const;
    boost::gregorian::date first_tuesday() const;
    boost::gregorian::date first_wednesday() const;
    boost::gregorian::date first_thursday() const;
    boost::gregorian::date first_friday() const;
    boost::gregorian::date first_saturday() const;
    boost::gregorian::date first_sunday() const;

    // Second
    boost::gregorian::date second_monday() const;
    boost::gregorian::date second_tuesday() const;
    boost::gregorian::date second_wednesday() const;
    boost::gregorian::date second_thursday() const;
    boost::gregorian::date second_friday() const;
    boost::gregorian::date second_saturday() const;
    boost::gregorian::date second_sunday() const;

    // Third
    boost::gregorian::date third_monday() const;
    boost::gregorian::date third_tuesday() const;
    boost::gregorian::date third_wednesday() const;
    boost::gregorian::date third_thursday() const;
    boost::gregorian::date third_friday() const;
    boost::gregorian::date third_saturday() const;
    boost::gregorian::date third_sunday() const;

    // Fourth
    boost::gregorian::date fourth_monday() const;
    boost::gregorian::date fourth_tuesday() const;
    boost::gregorian::date fourth_wednesday() const;
    boost::gregorian::date fourth_thursday() const;
    boost::gregorian::date fourth_friday() const;
    boost::gregorian::date fourth_saturday() const;
    boost::gregorian::date fourth_sunday() const;

    // Last
    boost::gregorian::date last_monday() const;
    boost::gregorian::date last_tuesday() const;
    boost::gregorian::date last_wednesday() const;
    boost::gregorian::date last_thursday() const;
    boost::gregorian::date last_friday() const;
    boost::gregorian::date last_saturday() const;
    boost::gregorian::date last_sunday() const;

private:
    std::uint16_t m_year;
    std::uint8_t m_month;
};

}  // namespace meetup

#endif // MEETUP_H
