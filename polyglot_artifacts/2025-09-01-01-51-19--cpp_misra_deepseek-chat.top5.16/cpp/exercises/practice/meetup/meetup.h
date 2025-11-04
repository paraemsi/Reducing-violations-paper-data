#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <cstdint>

namespace meetup {

class scheduler {
public:
    scheduler(std::int32_t year, std::int32_t month);
    
    // Teenth days
    boost::gregorian::date monteenth() const;
    boost::gregorian::date tuesteenth() const;
    boost::gregorian::date wednesteenth() const;
    boost::gregorian::date thursteenth() const;
    boost::gregorian::date friteenth() const;
    boost::gregorian::date saturteenth() const;
    boost::gregorian::date sunteenth() const;
    
    // First week days
    boost::gregorian::date first_monday() const;
    boost::gregorian::date first_tuesday() const;
    boost::gregorian::date first_wednesday() const;
    boost::gregorian::date first_thursday() const;
    boost::gregorian::date first_friday() const;
    boost::gregorian::date first_saturday() const;
    boost::gregorian::date first_sunday() const;
    
    // Second week days
    boost::gregorian::date second_monday() const;
    boost::gregorian::date second_tuesday() const;
    boost::gregorian::date second_wednesday() const;
    boost::gregorian::date second_thursday() const;
    boost::gregorian::date second_friday() const;
    boost::gregorian::date second_saturday() const;
    boost::gregorian::date second_sunday() const;
    
    // Third week days
    boost::gregorian::date third_monday() const;
    boost::gregorian::date third_tuesday() const;
    boost::gregorian::date third_wednesday() const;
    boost::gregorian::date third_thursday() const;
    boost::gregorian::date third_friday() const;
    boost::gregorian::date third_saturday() const;
    boost::gregorian::date third_sunday() const;
    
    // Fourth week days
    boost::gregorian::date fourth_monday() const;
    boost::gregorian::date fourth_tuesday() const;
    boost::gregorian::date fourth_wednesday() const;
    boost::gregorian::date fourth_thursday() const;
    boost::gregorian::date fourth_friday() const;
    boost::gregorian::date fourth_saturday() const;
    boost::gregorian::date fourth_sunday() const;
    
    // Last week days
    boost::gregorian::date last_monday() const;
    boost::gregorian::date last_tuesday() const;
    boost::gregorian::date last_wednesday() const;
    boost::gregorian::date last_thursday() const;
    boost::gregorian::date last_friday() const;
    boost::gregorian::date last_saturday() const;
    boost::gregorian::date last_sunday() const;
    
private:
    std::int32_t year_;
    std::int32_t month_;
    boost::gregorian::date find_nth_weekday(std::int32_t n, boost::gregorian::greg_weekday weekday) const;
    boost::gregorian::date find_teenth(boost::gregorian::greg_weekday weekday) const;
    boost::gregorian::date find_last(boost::gregorian::greg_weekday weekday) const;
};

}  // namespace meetup

#endif // MEETUP_H
