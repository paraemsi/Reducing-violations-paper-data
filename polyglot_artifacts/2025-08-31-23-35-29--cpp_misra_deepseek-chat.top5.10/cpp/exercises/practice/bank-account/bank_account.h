#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {

using amount_t = std::int64_t;

class Bankaccount {
public:
    void open();
    void deposit(amount_t amount);
    void withdraw(amount_t amount);
    void close();
    amount_t balance() const;
    
private:
    mutable std::mutex mtx;
    amount_t current_balance{0};
    bool is_open{false};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
