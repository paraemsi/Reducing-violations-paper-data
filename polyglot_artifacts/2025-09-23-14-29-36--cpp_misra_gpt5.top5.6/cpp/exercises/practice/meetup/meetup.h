#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

class scheduler {
public:
    scheduler(boost::gregorian::months_of_year month, std::int32_t year);

    // teenth
    auto monteenth() const -> boost::gregorian::date;
    auto tuesteenth() const -> boost::gregorian::date;
    auto wednesteenth() const -> boost::gregorian::date;
    auto thursteenth() const -> boost::gregorian::date;
    auto friteenth() const -> boost::gregorian::date;
    auto saturteenth() const -> boost::gregorian::date;
    auto sunteenth() const -> boost::gregorian::date;

    // first
    auto first_monday() const -> boost::gregorian::date;
    auto first_tuesday() const -> boost::gregorian::date;
    auto first_wednesday() const -> boost::gregorian::date;
    auto first_thursday() const -> boost::gregorian::date;
    auto first_friday() const -> boost::gregorian::date;
    auto first_saturday() const -> boost::gregorian::date;
    auto first_sunday() const -> boost::gregorian::date;

    // second
    auto second_monday() const -> boost::gregorian::date;
    auto second_tuesday() const -> boost::gregorian::date;
    auto second_wednesday() const -> boost::gregorian::date;
    auto second_thursday() const -> boost::gregorian::date;
    auto second_friday() const -> boost::gregorian::date;
    auto second_saturday() const -> boost::gregorian::date;
    auto second_sunday() const -> boost::gregorian::date;

    // third
    auto third_monday() const -> boost::gregorian::date;
    auto third_tuesday() const -> boost::gregorian::date;
    auto third_wednesday() const -> boost::gregorian::date;
    auto third_thursday() const -> boost::gregorian::date;
    auto third_friday() const -> boost::gregorian::date;
    auto third_saturday() const -> boost::gregorian::date;
    auto third_sunday() const -> boost::gregorian::date;

    // fourth
    auto fourth_monday() const -> boost::gregorian::date;
    auto fourth_tuesday() const -> boost::gregorian::date;
    auto fourth_wednesday() const -> boost::gregorian::date;
    auto fourth_thursday() const -> boost::gregorian::date;
    auto fourth_friday() const -> boost::gregorian::date;
    auto fourth_saturday() const -> boost::gregorian::date;
    auto fourth_sunday() const -> boost::gregorian::date;

    // last
    auto last_monday() const -> boost::gregorian::date;
    auto last_tuesday() const -> boost::gregorian::date;
    auto last_wednesday() const -> boost::gregorian::date;
    auto last_thursday() const -> boost::gregorian::date;
    auto last_friday() const -> boost::gregorian::date;
    auto last_saturday() const -> boost::gregorian::date;
    auto last_sunday() const -> boost::gregorian::date;

private:
    auto teenth(boost::date_time::weekdays wd) const -> boost::gregorian::date;
    auto nth(std::uint32_t n, boost::date_time::weekdays wd) const -> boost::gregorian::date;
    auto last(boost::date_time::weekdays wd) const -> boost::gregorian::date;

    boost::gregorian::months_of_year month_;
    std::int32_t year_;
};

}  // namespace meetup

#endif // MEETUP_H
