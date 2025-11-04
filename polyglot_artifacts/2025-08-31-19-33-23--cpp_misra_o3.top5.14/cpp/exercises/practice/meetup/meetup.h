#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>

namespace meetup {

/* Enumeration of weekdays – 0U maps to Sunday to align with Zeller-based helper. */
enum class weekday : std::uint8_t {
    sunday    = 0U,
    monday    = 1U,
    tuesday   = 2U,
    wednesday = 3U,
    thursday  = 4U,
    friday    = 5U,
    saturday  = 6U
};

/* Enumeration of requested schedules within a month. */
enum class schedule : std::uint8_t {
    first  = 0U,
    second = 1U,
    third  = 2U,
    fourth = 3U,
    last   = 4U,
    teenth = 5U
};

/* Stateless helper object storing the year and month for which meetup days are requested. */
class scheduler {
public:
    /* Inline constexpr constructor so it is available in constant-expression
       contexts across translation units. */
    constexpr scheduler(std::uint32_t year_in, std::uint32_t month_in) noexcept
        : m_year(year_in),
          m_month(month_in)
    {
    }

    /* Return the day-of-month (1-31) that satisfies the given weekday & schedule. */
    std::uint32_t day(weekday weekday_in, schedule schedule_in) const;

    /* --- convenience wrappers demanded by unit-tests ---------------------- */

    /* teenth helpers */
    std::uint32_t monteenth()      const { return day(weekday::monday,    schedule::teenth); }
    std::uint32_t tuesteenth()     const { return day(weekday::tuesday,   schedule::teenth); }
    std::uint32_t wednesteenth()   const { return day(weekday::wednesday, schedule::teenth); }
    std::uint32_t thursteenth()    const { return day(weekday::thursday,  schedule::teenth); }
    std::uint32_t friteenth()      const { return day(weekday::friday,    schedule::teenth); }
    std::uint32_t saturteenth()    const { return day(weekday::saturday,  schedule::teenth); }
    std::uint32_t sunteenth()      const { return day(weekday::sunday,    schedule::teenth); }

    /* first */
    std::uint32_t first_monday()    const { return day(weekday::monday,    schedule::first); }
    std::uint32_t first_tuesday()   const { return day(weekday::tuesday,   schedule::first); }
    std::uint32_t first_wednesday() const { return day(weekday::wednesday, schedule::first); }
    std::uint32_t first_thursday()  const { return day(weekday::thursday,  schedule::first); }
    std::uint32_t first_friday()    const { return day(weekday::friday,    schedule::first); }
    std::uint32_t first_saturday()  const { return day(weekday::saturday,  schedule::first); }
    std::uint32_t first_sunday()    const { return day(weekday::sunday,    schedule::first); }

    /* second */
    std::uint32_t second_monday()    const { return day(weekday::monday,    schedule::second); }
    std::uint32_t second_tuesday()   const { return day(weekday::tuesday,   schedule::second); }
    std::uint32_t second_wednesday() const { return day(weekday::wednesday, schedule::second); }
    std::uint32_t second_thursday()  const { return day(weekday::thursday,  schedule::second); }
    std::uint32_t second_friday()    const { return day(weekday::friday,    schedule::second); }
    std::uint32_t second_saturday()  const { return day(weekday::saturday,  schedule::second); }
    std::uint32_t second_sunday()    const { return day(weekday::sunday,    schedule::second); }

    /* third */
    std::uint32_t third_monday()    const { return day(weekday::monday,    schedule::third); }
    std::uint32_t third_tuesday()   const { return day(weekday::tuesday,   schedule::third); }
    std::uint32_t third_wednesday() const { return day(weekday::wednesday, schedule::third); }
    std::uint32_t third_thursday()  const { return day(weekday::thursday,  schedule::third); }
    std::uint32_t third_friday()    const { return day(weekday::friday,    schedule::third); }
    std::uint32_t third_saturday()  const { return day(weekday::saturday,  schedule::third); }
    std::uint32_t third_sunday()    const { return day(weekday::sunday,    schedule::third); }

    /* fourth */
    std::uint32_t fourth_monday()    const { return day(weekday::monday,    schedule::fourth); }
    std::uint32_t fourth_tuesday()   const { return day(weekday::tuesday,   schedule::fourth); }
    std::uint32_t fourth_wednesday() const { return day(weekday::wednesday, schedule::fourth); }
    std::uint32_t fourth_thursday()  const { return day(weekday::thursday,  schedule::fourth); }
    std::uint32_t fourth_friday()    const { return day(weekday::friday,    schedule::fourth); }
    std::uint32_t fourth_saturday()  const { return day(weekday::saturday,  schedule::fourth); }
    std::uint32_t fourth_sunday()    const { return day(weekday::sunday,    schedule::fourth); }

    /* last */
    std::uint32_t last_monday()    const { return day(weekday::monday,    schedule::last); }
    std::uint32_t last_tuesday()   const { return day(weekday::tuesday,   schedule::last); }
    std::uint32_t last_wednesday() const { return day(weekday::wednesday, schedule::last); }
    std::uint32_t last_thursday()  const { return day(weekday::thursday,  schedule::last); }
    std::uint32_t last_friday()    const { return day(weekday::friday,    schedule::last); }
    std::uint32_t last_saturday()  const { return day(weekday::saturday,  schedule::last); }
    std::uint32_t last_sunday()    const { return day(weekday::sunday,    schedule::last); }

private:
    std::uint32_t m_year;
    std::uint32_t m_month;
};

}  // namespace meetup

#endif // MEETUP_H
