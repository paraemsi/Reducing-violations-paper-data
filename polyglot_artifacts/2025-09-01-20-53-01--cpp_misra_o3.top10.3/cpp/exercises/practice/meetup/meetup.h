#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

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
    scheduler(std::int32_t year, std::uint32_t month) noexcept;

    /* ---- teenth helpers ---- */
    [[nodiscard]] boost::gregorian::date monteenth() const noexcept;
    [[nodiscard]] boost::gregorian::date tuesteenth() const noexcept;
    [[nodiscard]] boost::gregorian::date wednesteenth() const noexcept;
    [[nodiscard]] boost::gregorian::date thursteenth() const noexcept;
    [[nodiscard]] boost::gregorian::date friteenth() const noexcept;
    [[nodiscard]] boost::gregorian::date saturteenth() const noexcept;
    [[nodiscard]] boost::gregorian::date sunteenth() const noexcept;

    /* ---- first week helpers ---- */
    [[nodiscard]] boost::gregorian::date first_monday() const noexcept;
    [[nodiscard]] boost::gregorian::date first_tuesday() const noexcept;
    [[nodiscard]] boost::gregorian::date first_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date first_thursday() const noexcept;
    [[nodiscard]] boost::gregorian::date first_friday() const noexcept;
    [[nodiscard]] boost::gregorian::date first_saturday() const noexcept;
    [[nodiscard]] boost::gregorian::date first_sunday() const noexcept;

    /* ---- second week helpers ---- */
    [[nodiscard]] boost::gregorian::date second_monday() const noexcept;
    [[nodiscard]] boost::gregorian::date second_tuesday() const noexcept;
    [[nodiscard]] boost::gregorian::date second_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date second_thursday() const noexcept;
    [[nodiscard]] boost::gregorian::date second_friday() const noexcept;
    [[nodiscard]] boost::gregorian::date second_saturday() const noexcept;
    [[nodiscard]] boost::gregorian::date second_sunday() const noexcept;

    /* ---- third week helpers ---- */
    [[nodiscard]] boost::gregorian::date third_monday() const noexcept;
    [[nodiscard]] boost::gregorian::date third_tuesday() const noexcept;
    [[nodiscard]] boost::gregorian::date third_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date third_thursday() const noexcept;
    [[nodiscard]] boost::gregorian::date third_friday() const noexcept;
    [[nodiscard]] boost::gregorian::date third_saturday() const noexcept;
    [[nodiscard]] boost::gregorian::date third_sunday() const noexcept;

    /* ---- fourth week helpers ---- */
    [[nodiscard]] boost::gregorian::date fourth_monday() const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_tuesday() const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_thursday() const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_friday() const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_saturday() const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_sunday() const noexcept;

    /* ---- last week helpers ---- */
    [[nodiscard]] boost::gregorian::date last_monday() const noexcept;
    [[nodiscard]] boost::gregorian::date last_tuesday() const noexcept;
    [[nodiscard]] boost::gregorian::date last_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date last_thursday() const noexcept;
    [[nodiscard]] boost::gregorian::date last_friday() const noexcept;
    [[nodiscard]] boost::gregorian::date last_saturday() const noexcept;
    [[nodiscard]] boost::gregorian::date last_sunday() const noexcept;

private:
    [[nodiscard]] boost::gregorian::date
    day(boost::date_time::weekdays weekday_req, schedule schedule_req) const noexcept;

    std::int32_t  m_year;
    std::uint32_t m_month;
};

}  // namespace meetup

#endif // MEETUP_H
