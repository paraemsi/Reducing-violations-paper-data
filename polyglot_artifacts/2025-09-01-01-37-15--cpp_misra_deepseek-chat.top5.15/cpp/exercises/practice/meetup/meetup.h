#if !defined(MEETUP_H)
#define MEETUP_H

#include <chrono>
#include <string>

namespace meetup {

class scheduler {
public:
    scheduler(int year, int month);
    
    // Teenth functions
    std::chrono::year_month_day monteenth() const;
    std::chrono::year_month_day tuesteenth() const;
    std::chrono::year_month_day wednesteenth() const;
    std::chrono::year_month_day thursteenth() const;
    std::chrono::year_month_day friteenth() const;
    std::chrono::year_month_day saturteenth() const;
    std::chrono::year_month_day sunteenth() const;
    
    // First week functions
    std::chrono::year_month_day first_monday() const;
    std::chrono::year_month_day first_tuesday() const;
    std::chrono::year_month_day first_wednesday() const;
    std::chrono::year_month_day first_thursday() const;
    std::chrono::year_month_day first_friday() const;
    std::chrono::year_month_day first_saturday() const;
    std::chrono::year_month_day first_sunday() const;
    
    // Second week functions
    std::chrono::year_month_day second_monday() const;
    std::chrono::year_month_day second_tuesday() const;
    std::chrono::year_month_day second_wednesday() const;
    std::chrono::year_month_day second_thursday() const;
    std::chrono::year_month_day second_friday() const;
    std::chrono::year_month_day second_saturday() const;
    std::chrono::year_month_day second_sunday() const;
    
    // Third week functions
    std::chrono::year_month_day third_monday() const;
    std::chrono::year_month_day third_tuesday() const;
    std::chrono::year_month_day third_wednesday() const;
    std::chrono::year_month_day third_thursday() const;
    std::chrono::year_month_day third_friday() const;
    std::chrono::year_month_day third_saturday() const;
    std::chrono::year_month_day third_sunday() const;
    
    // Fourth week functions
    std::chrono::year_month_day fourth_monday() const;
    std::chrono::year_month_day fourth_tuesday() const;
    std::chrono::year_month_day fourth_wednesday() const;
    std::chrono::year_month_day fourth_thursday() const;
    std::chrono::year_month_day fourth_friday() const;
    std::chrono::year_month_day fourth_saturday() const;
    std::chrono::year_month_day fourth_sunday() const;
    
    // Last week functions
    std::chrono::year_month_day last_monday() const;
    std::chrono::year_month_day last_tuesday() const;
    std::chrono::year_month_day last_wednesday() const;
    std::chrono::year_month_day last_thursday() const;
    std::chrono::year_month_day last_friday() const;
    std::chrono::year_month_day last_saturday() const;
    std::chrono::year_month_day last_sunday() const;
    
private:
    int year_;
    int month_;
    std::chrono::year_month_day find_date(const std::string& week, const std::string& weekday) const;
};

}  // namespace meetup

#endif // MEETUP_H
