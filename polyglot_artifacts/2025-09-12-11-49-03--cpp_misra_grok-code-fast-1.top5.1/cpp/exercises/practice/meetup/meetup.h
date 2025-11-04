#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

enum class weekday : std::uint32_t { sunday, monday, tuesday, wednesday, thursday, friday, saturday };

enum class week : std::uint32_t { first, second, third, fourth, last, teenth };

class scheduler {
private:
    boost::gregorian::greg_month month_;
    int year_;

public:
    scheduler(boost::gregorian::greg_month month, int year);
    boost::gregorian::date day(weekday wd, week wk);
    boost::gregorian::date monteenth();
    boost::gregorian::date tuesteenth();
    boost::gregorian::date wednesteenth();
    boost::gregorian::date thursteenth();
    boost::gregorian::date friteenth();
    boost::gregorian::date saturteenth();
    boost::gregorian::date sunteenth();
    boost::gregorian::date first_monday();
    boost::gregorian::date first_tuesday();
    boost::gregorian::date first_wednesday();
    boost::gregorian::date first_thursday();
    boost::gregorian::date first_friday();
    boost::gregorian::date first_saturday();
    boost::gregorian::date first_sunday();
    boost::gregorian::date second_monday();
    boost::gregorian::date second_tuesday();
    boost::gregorian::date second_wednesday();
    boost::gregorian::date second_thursday();
    boost::gregorian::date second_friday();
    boost::gregorian::date second_saturday();
    boost::gregorian::date second_sunday();
    boost::gregorian::date third_monday();
    boost::gregorian::date third_tuesday();
    boost::gregorian::date third_wednesday();
    boost::gregorian::date third_thursday();
    boost::gregorian::date third_friday();
    boost::gregorian::date third_saturday();
    boost::gregorian::date third_sunday();
    boost::gregorian::date fourth_monday();
    boost::gregorian::date fourth_tuesday();
    boost::gregorian::date fourth_wednesday();
    boost::gregorian::date fourth_thursday();
    boost::gregorian::date fourth_friday();
    boost::gregorian::date fourth_saturday();
    boost::gregorian::date fourth_sunday();
    boost::gregorian::date last_monday();
    boost::gregorian::date last_tuesday();
    boost::gregorian::date last_wednesday();
    boost::gregorian::date last_thursday();
    boost::gregorian::date last_friday();
    boost::gregorian::date last_saturday();
    boost::gregorian::date last_sunday();
};

}  // namespace meetup
