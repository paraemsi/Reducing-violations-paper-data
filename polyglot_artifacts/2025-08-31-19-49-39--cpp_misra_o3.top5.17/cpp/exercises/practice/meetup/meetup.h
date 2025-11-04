#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <stdexcept>

namespace meetup {

enum class schedule {
    first,
    second,
    third,
    fourth,
    fifth,
    last,
    teenth
};

enum class weekday {
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday
};

class scheduler {
public:
    constexpr scheduler(std::int32_t year, std::int32_t month) noexcept
        : m_year(year), m_month(month) {}

    std::uint32_t day(weekday target_weekday, schedule target_schedule) const;

    /* Convenience helpers for tests */
    /* ---------- teenth ---------- */
    inline std::uint32_t monteenth()  const { return day(weekday::monday,    schedule::teenth); }
    inline std::uint32_t tuesteenth() const { return day(weekday::tuesday,   schedule::teenth); }
    inline std::uint32_t wednesteenth() const { return day(weekday::wednesday, schedule::teenth); }
    inline std::uint32_t thursteenth() const { return day(weekday::thursday, schedule::teenth); }
    inline std::uint32_t friteenth()   const { return day(weekday::friday,   schedule::teenth); }
    inline std::uint32_t saturteenth() const { return day(weekday::saturday, schedule::teenth); }
    inline std::uint32_t sunteenth()   const { return day(weekday::sunday,   schedule::teenth); }

    /* ---------- first ---------- */
    inline std::uint32_t first_monday()    const { return day(weekday::monday,    schedule::first); }
    inline std::uint32_t first_tuesday()   const { return day(weekday::tuesday,   schedule::first); }
    inline std::uint32_t first_wednesday() const { return day(weekday::wednesday, schedule::first); }
    inline std::uint32_t first_thursday()  const { return day(weekday::thursday,  schedule::first); }
    inline std::uint32_t first_friday()    const { return day(weekday::friday,    schedule::first); }
    inline std::uint32_t first_saturday()  const { return day(weekday::saturday,  schedule::first); }
    inline std::uint32_t first_sunday()    const { return day(weekday::sunday,    schedule::first); }

    /* ---------- second ---------- */
    inline std::uint32_t second_monday()    const { return day(weekday::monday,    schedule::second); }
    inline std::uint32_t second_tuesday()   const { return day(weekday::tuesday,   schedule::second); }
    inline std::uint32_t second_wednesday() const { return day(weekday::wednesday, schedule::second); }
    inline std::uint32_t second_thursday()  const { return day(weekday::thursday,  schedule::second); }
    inline std::uint32_t second_friday()    const { return day(weekday::friday,    schedule::second); }
    inline std::uint32_t second_saturday()  const { return day(weekday::saturday,  schedule::second); }
    inline std::uint32_t second_sunday()    const { return day(weekday::sunday,    schedule::second); }

    /* ---------- third ---------- */
    inline std::uint32_t third_monday()    const { return day(weekday::monday,    schedule::third); }
    inline std::uint32_t third_tuesday()   const { return day(weekday::tuesday,   schedule::third); }
    inline std::uint32_t third_wednesday() const { return day(weekday::wednesday, schedule::third); }
    inline std::uint32_t third_thursday()  const { return day(weekday::thursday,  schedule::third); }
    inline std::uint32_t third_friday()    const { return day(weekday::friday,    schedule::third); }
    inline std::uint32_t third_saturday()  const { return day(weekday::saturday,  schedule::third); }
    inline std::uint32_t third_sunday()    const { return day(weekday::sunday,    schedule::third); }

    /* ---------- fourth ---------- */
    inline std::uint32_t fourth_monday()    const { return day(weekday::monday,    schedule::fourth); }
    inline std::uint32_t fourth_tuesday()   const { return day(weekday::tuesday,   schedule::fourth); }
    inline std::uint32_t fourth_wednesday() const { return day(weekday::wednesday, schedule::fourth); }
    inline std::uint32_t fourth_thursday()  const { return day(weekday::thursday,  schedule::fourth); }
    inline std::uint32_t fourth_friday()    const { return day(weekday::friday,    schedule::fourth); }
    inline std::uint32_t fourth_saturday()  const { return day(weekday::saturday,  schedule::fourth); }
    inline std::uint32_t fourth_sunday()    const { return day(weekday::sunday,    schedule::fourth); }

    /* ---------- last ---------- */
    inline std::uint32_t last_monday()    const { return day(weekday::monday,    schedule::last); }
    inline std::uint32_t last_tuesday()   const { return day(weekday::tuesday,   schedule::last); }
    inline std::uint32_t last_wednesday() const { return day(weekday::wednesday, schedule::last); }
    inline std::uint32_t last_thursday()  const { return day(weekday::thursday,  schedule::last); }
    inline std::uint32_t last_friday()    const { return day(weekday::friday,    schedule::last); }
    inline std::uint32_t last_saturday()  const { return day(weekday::saturday,  schedule::last); }
    inline std::uint32_t last_sunday()    const { return day(weekday::sunday,    schedule::last); }

private:
    std::int32_t m_year;
    std::int32_t m_month;

    static bool is_leap_year(std::int32_t year) noexcept;
    static std::uint32_t days_in_month(std::int32_t year, std::int32_t month) noexcept;
    static weekday weekday_of(std::int32_t year, std::int32_t month, std::uint32_t day) noexcept;
};

}  // namespace meetup

#endif // MEETUP_H
