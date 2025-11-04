#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>

namespace boost { namespace gregorian { class date; } }

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
    first = 0U,
    second = 1U,
    third = 2U,
    fourth = 3U,
    last = 4U,
    teenth = 5U
};

class scheduler {
public:
    scheduler(std::int32_t year, std::int32_t month) noexcept;

    // Returns the day-of-month (1..31) for the requested weekday/schedule.
    // May throw std::out_of_range if the stored month is invalid.
    std::int32_t day(weekday wd, schedule s) const;

    // Teenth occurrences
    boost::gregorian::date monteenth() const;
    boost::gregorian::date tuesteenth() const;
    boost::gregorian::date wednesteenth() const;
    boost::gregorian::date thursteenth() const;
    boost::gregorian::date friteenth() const;
    boost::gregorian::date saturteenth() const;
    boost::gregorian::date sunteenth() const;

    // First occurrences
    boost::gregorian::date first_monday() const;
    boost::gregorian::date first_tuesday() const;
    boost::gregorian::date first_wednesday() const;
    boost::gregorian::date first_thursday() const;
    boost::gregorian::date first_friday() const;
    boost::gregorian::date first_saturday() const;
    boost::gregorian::date first_sunday() const;

    // Second occurrences
    boost::gregorian::date second_monday() const;
    boost::gregorian::date second_tuesday() const;
    boost::gregorian::date second_wednesday() const;
    boost::gregorian::date second_thursday() const;
    boost::gregorian::date second_friday() const;
    boost::gregorian::date second_saturday() const;
    boost::gregorian::date second_sunday() const;

    // Third occurrences
    boost::gregorian::date third_monday() const;
    boost::gregorian::date third_tuesday() const;
    boost::gregorian::date third_wednesday() const;
    boost::gregorian::date third_thursday() const;
    boost::gregorian::date third_friday() const;
    boost::gregorian::date third_saturday() const;
    boost::gregorian::date third_sunday() const;

    // Fourth occurrences
    boost::gregorian::date fourth_monday() const;
    boost::gregorian::date fourth_tuesday() const;
    boost::gregorian::date fourth_wednesday() const;
    boost::gregorian::date fourth_thursday() const;
    boost::gregorian::date fourth_friday() const;
    boost::gregorian::date fourth_saturday() const;
    boost::gregorian::date fourth_sunday() const;

    // Last occurrences
    boost::gregorian::date last_monday() const;
    boost::gregorian::date last_tuesday() const;
    boost::gregorian::date last_wednesday() const;
    boost::gregorian::date last_thursday() const;
    boost::gregorian::date last_friday() const;
    boost::gregorian::date last_saturday() const;
    boost::gregorian::date last_sunday() const;

private:
    const std::int32_t m_year;
    const std::int32_t m_month;

    boost::gregorian::date date_for(weekday wd, schedule s) const;
};

}  // namespace meetup

#endif // MEETUP_H
