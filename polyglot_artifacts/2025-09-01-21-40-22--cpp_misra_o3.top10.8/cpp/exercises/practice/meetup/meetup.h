#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

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

class scheduler
{
public:
    scheduler(boost::gregorian::greg_month month, std::int32_t year) noexcept;

    [[nodiscard]] auto monteenth() const -> boost::gregorian::date;
    [[nodiscard]] auto tuesteenth() const -> boost::gregorian::date;
    [[nodiscard]] auto wednesteenth() const -> boost::gregorian::date;
    [[nodiscard]] auto thursteenth() const -> boost::gregorian::date;
    [[nodiscard]] auto friteenth() const -> boost::gregorian::date;
    [[nodiscard]] auto saturteenth() const -> boost::gregorian::date;
    [[nodiscard]] auto sunteenth() const -> boost::gregorian::date;

    [[nodiscard]] auto first_monday() const -> boost::gregorian::date;
    [[nodiscard]] auto first_tuesday() const -> boost::gregorian::date;
    [[nodiscard]] auto first_wednesday() const -> boost::gregorian::date;
    [[nodiscard]] auto first_thursday() const -> boost::gregorian::date;
    [[nodiscard]] auto first_friday() const -> boost::gregorian::date;
    [[nodiscard]] auto first_saturday() const -> boost::gregorian::date;
    [[nodiscard]] auto first_sunday() const -> boost::gregorian::date;

    [[nodiscard]] auto second_monday() const -> boost::gregorian::date;
    [[nodiscard]] auto second_tuesday() const -> boost::gregorian::date;
    [[nodiscard]] auto second_wednesday() const -> boost::gregorian::date;
    [[nodiscard]] auto second_thursday() const -> boost::gregorian::date;
    [[nodiscard]] auto second_friday() const -> boost::gregorian::date;
    [[nodiscard]] auto second_saturday() const -> boost::gregorian::date;
    [[nodiscard]] auto second_sunday() const -> boost::gregorian::date;

    [[nodiscard]] auto third_monday() const -> boost::gregorian::date;
    [[nodiscard]] auto third_tuesday() const -> boost::gregorian::date;
    [[nodiscard]] auto third_wednesday() const -> boost::gregorian::date;
    [[nodiscard]] auto third_thursday() const -> boost::gregorian::date;
    [[nodiscard]] auto third_friday() const -> boost::gregorian::date;
    [[nodiscard]] auto third_saturday() const -> boost::gregorian::date;
    [[nodiscard]] auto third_sunday() const -> boost::gregorian::date;

    [[nodiscard]] auto fourth_monday() const -> boost::gregorian::date;
    [[nodiscard]] auto fourth_tuesday() const -> boost::gregorian::date;
    [[nodiscard]] auto fourth_wednesday() const -> boost::gregorian::date;
    [[nodiscard]] auto fourth_thursday() const -> boost::gregorian::date;
    [[nodiscard]] auto fourth_friday() const -> boost::gregorian::date;
    [[nodiscard]] auto fourth_saturday() const -> boost::gregorian::date;
    [[nodiscard]] auto fourth_sunday() const -> boost::gregorian::date;

    [[nodiscard]] auto last_monday() const -> boost::gregorian::date;
    [[nodiscard]] auto last_tuesday() const -> boost::gregorian::date;
    [[nodiscard]] auto last_wednesday() const -> boost::gregorian::date;
    [[nodiscard]] auto last_thursday() const -> boost::gregorian::date;
    [[nodiscard]] auto last_friday() const -> boost::gregorian::date;
    [[nodiscard]] auto last_saturday() const -> boost::gregorian::date;
    [[nodiscard]] auto last_sunday() const -> boost::gregorian::date;

private:
    boost::gregorian::greg_month m_month;
    std::int32_t                 m_year;

    [[nodiscard]] auto compute(schedule const sched,
                               boost::date_time::weekdays const wd) const
        -> boost::gregorian::date;
};

}  // namespace meetup

#endif // MEETUP_H
