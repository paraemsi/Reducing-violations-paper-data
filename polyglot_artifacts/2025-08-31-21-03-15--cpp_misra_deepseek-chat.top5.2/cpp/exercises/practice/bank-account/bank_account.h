#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

class Bankaccount {
public:
    using amount_t = std::int64_t;
    
    Bankaccount();
    void open();
    void close();
    void deposit(amount_t amount);
    void withdraw(amount_t amount);
    amount_t balance() const;
    
private:
    mutable std::mutex mtx;
    amount_t current_balance;
    bool is_open;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
