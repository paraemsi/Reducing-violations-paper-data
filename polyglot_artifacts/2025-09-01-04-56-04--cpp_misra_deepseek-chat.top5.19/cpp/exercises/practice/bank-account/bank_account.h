#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {
class Bankaccount {
public:
    void open();
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);
    void close();
    std::int64_t balance() const;
    
private:
    mutable std::mutex mtx;
    std::int64_t balance_{0};
    bool is_open_{false};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
