#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

/* Class providing all required “teenth”, first/second/third/fourth
 * and last weekday queries for the configured month. */
class scheduler {
public:
    scheduler(std::int32_t year, std::uint32_t month) noexcept;

    /* ——— teenth ——— */
    [[nodiscard]] boost::gregorian::date monteenth() const;
    [[nodiscard]] boost::gregorian::date tuesteenth() const;
    [[nodiscard]] boost::gregorian::date wednesteenth() const;
    [[nodiscard]] boost::gregorian::date thursteenth() const;
    [[nodiscard]] boost::gregorian::date friteenth() const;
    [[nodiscard]] boost::gregorian::date saturteenth() const;
    [[nodiscard]] boost::gregorian::date sunteenth() const;

    /* ——— first ——— */
    [[nodiscard]] boost::gregorian::date first_monday() const;
    [[nodiscard]] boost::gregorian::date first_tuesday() const;
    [[nodiscard]] boost::gregorian::date first_wednesday() const;
    [[nodiscard]] boost::gregorian::date first_thursday() const;
    [[nodiscard]] boost::gregorian::date first_friday() const;
    [[nodiscard]] boost::gregorian::date first_saturday() const;
    [[nodiscard]] boost::gregorian::date first_sunday() const;

    /* ——— second ——— */
    [[nodiscard]] boost::gregorian::date second_monday() const;
    [[nodiscard]] boost::gregorian::date second_tuesday() const;
    [[nodiscard]] boost::gregorian::date second_wednesday() const;
    [[nodiscard]] boost::gregorian::date second_thursday() const;
    [[nodiscard]] boost::gregorian::date second_friday() const;
    [[nodiscard]] boost::gregorian::date second_saturday() const;
    [[nodiscard]] boost::gregorian::date second_sunday() const;

    /* ——— third ——— */
    [[nodiscard]] boost::gregorian::date third_monday() const;
    [[nodiscard]] boost::gregorian::date third_tuesday() const;
    [[nodiscard]] boost::gregorian::date third_wednesday() const;
    [[nodiscard]] boost::gregorian::date third_thursday() const;
    [[nodiscard]] boost::gregorian::date third_friday() const;
    [[nodiscard]] boost::gregorian::date third_saturday() const;
    [[nodiscard]] boost::gregorian::date third_sunday() const;

    /* ——— fourth ——— */
    [[nodiscard]] boost::gregorian::date fourth_monday() const;
    [[nodiscard]] boost::gregorian::date fourth_tuesday() const;
    [[nodiscard]] boost::gregorian::date fourth_wednesday() const;
    [[nodiscard]] boost::gregorian::date fourth_thursday() const;
    [[nodiscard]] boost::gregorian::date fourth_friday() const;
    [[nodiscard]] boost::gregorian::date fourth_saturday() const;
    [[nodiscard]] boost::gregorian::date fourth_sunday() const;

    /* ——— last ——— */
    [[nodiscard]] boost::gregorian::date last_monday() const;
    [[nodiscard]] boost::gregorian::date last_tuesday() const;
    [[nodiscard]] boost::gregorian::date last_wednesday() const;
    [[nodiscard]] boost::gregorian::date last_thursday() const;
    [[nodiscard]] boost::gregorian::date last_friday() const;
    [[nodiscard]] boost::gregorian::date last_saturday() const;
    [[nodiscard]] boost::gregorian::date last_sunday() const;

private:
    std::int32_t  year_{0};
    std::uint32_t month_{0U};

    [[nodiscard]] boost::gregorian::date teenth_day(boost::date_time::weekdays wd) const;
    [[nodiscard]] boost::gregorian::date nth_weekday(int ordinal,
                                                     boost::date_time::weekdays wd) const;
};

}  // namespace meetup

#endif // MEETUP_H
