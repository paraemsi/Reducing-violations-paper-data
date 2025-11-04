#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {
class Bankaccount {
public:
    void open();
    void close();
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);
    std::int64_t balance() const;
    
private:
    mutable std::mutex mtx;
    std::int64_t account_balance{0};
    bool is_open{false};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
