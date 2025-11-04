#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

// Which week of the month is being requested.
enum class schedule {
    first,
    second,
    third,
    fourth,
    last,
    teenth
};

// The scheduler represents a particular month of a given year and can
// answer which exact day satisfies a weekday/schedule query.
class scheduler {
public:
    explicit scheduler(int year, unsigned int month);

    // Return the exact calendar day that matches the requested weekday
    // and schedule within the stored month/year.
    //
    // Example:
    //   scheduler s{2025, 8};                              // August-2025
    //   auto d = s.day(std::chrono::weekday{4},            // Thursday
    //                  schedule::teenth);                  // 2025-08-14
    //
    // The returned type is boost::gregorian::date.
    [[nodiscard]]
    boost::gregorian::date day(boost::gregorian::greg_weekday wd,
                               schedule s) const;

#define MEETUP_INLINE_FN(name, wd_idx, sched_enum) \
    inline boost::gregorian::date name() const { \
        return day(boost::gregorian::greg_weekday{wd_idx}, schedule::sched_enum); \
    }

#define MEETUP_GENERATE(prefix, sched_enum) \
    MEETUP_INLINE_FN(prefix##_monday,    1, sched_enum) \
    MEETUP_INLINE_FN(prefix##_tuesday,   2, sched_enum) \
    MEETUP_INLINE_FN(prefix##_wednesday, 3, sched_enum) \
    MEETUP_INLINE_FN(prefix##_thursday,  4, sched_enum) \
    MEETUP_INLINE_FN(prefix##_friday,    5, sched_enum) \
    MEETUP_INLINE_FN(prefix##_saturday,  6, sched_enum) \
    MEETUP_INLINE_FN(prefix##_sunday,    0, sched_enum)

    // teenth helpers
    MEETUP_INLINE_FN(monteenth,    1, teenth)
    MEETUP_INLINE_FN(tuesteenth,   2, teenth)
    MEETUP_INLINE_FN(wednesteenth, 3, teenth)
    MEETUP_INLINE_FN(thursteenth,  4, teenth)
    MEETUP_INLINE_FN(friteenth,    5, teenth)
    MEETUP_INLINE_FN(saturteenth,  6, teenth)
    MEETUP_INLINE_FN(sunteenth,    0, teenth)

    // ordinal helpers
    MEETUP_GENERATE(first,  first)
    MEETUP_GENERATE(second, second)
    MEETUP_GENERATE(third,  third)
    MEETUP_GENERATE(fourth, fourth)
    MEETUP_GENERATE(last,   last)

#undef MEETUP_INLINE_FN
#undef MEETUP_GENERATE

private:
    int        m_year;
    unsigned int   m_month; // 1-12
};

}  // namespace meetup

#endif // MEETUP_H
