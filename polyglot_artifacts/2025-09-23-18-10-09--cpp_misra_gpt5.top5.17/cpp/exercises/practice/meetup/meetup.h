#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

class scheduler final {
public:
    using date_type = boost::gregorian::date;

    explicit scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept;

    // Teenth occurrences
    auto monteenth() const -> date_type;
    auto tuesteenth() const -> date_type;
    auto wednesteenth() const -> date_type;
    auto thursteenth() const -> date_type;
    auto friteenth() const -> date_type;
    auto saturteenth() const -> date_type;
    auto sunteenth() const -> date_type;

    // First occurrences
    auto first_monday() const -> date_type;
    auto first_tuesday() const -> date_type;
    auto first_wednesday() const -> date_type;
    auto first_thursday() const -> date_type;
    auto first_friday() const -> date_type;
    auto first_saturday() const -> date_type;
    auto first_sunday() const -> date_type;

    // Second occurrences
    auto second_monday() const -> date_type;
    auto second_tuesday() const -> date_type;
    auto second_wednesday() const -> date_type;
    auto second_thursday() const -> date_type;
    auto second_friday() const -> date_type;
    auto second_saturday() const -> date_type;
    auto second_sunday() const -> date_type;

    // Third occurrences
    auto third_monday() const -> date_type;
    auto third_tuesday() const -> date_type;
    auto third_wednesday() const -> date_type;
    auto third_thursday() const -> date_type;
    auto third_friday() const -> date_type;
    auto third_saturday() const -> date_type;
    auto third_sunday() const -> date_type;

    // Fourth occurrences
    auto fourth_monday() const -> date_type;
    auto fourth_tuesday() const -> date_type;
    auto fourth_wednesday() const -> date_type;
    auto fourth_thursday() const -> date_type;
    auto fourth_friday() const -> date_type;
    auto fourth_saturday() const -> date_type;
    auto fourth_sunday() const -> date_type;

    // Last occurrences
    auto last_monday() const -> date_type;
    auto last_tuesday() const -> date_type;
    auto last_wednesday() const -> date_type;
    auto last_thursday() const -> date_type;
    auto last_friday() const -> date_type;
    auto last_saturday() const -> date_type;
    auto last_sunday() const -> date_type;

private:
    auto first_of_month() const -> date_type;
    auto teenth_weekday(boost::date_time::weekdays w) const -> date_type;
    auto nth_weekday(boost::date_time::weekdays w, std::uint32_t n) const -> date_type;
    auto last_weekday(boost::date_time::weekdays w) const -> date_type;

    boost::gregorian::months_of_year month_;
    std::int32_t year_;
};

}  // namespace meetup

#endif // MEETUP_H
