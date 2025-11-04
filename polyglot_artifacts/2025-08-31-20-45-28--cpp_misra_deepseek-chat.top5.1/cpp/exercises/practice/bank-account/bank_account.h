#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {
class Bankaccount {
private:
    std::int64_t m_balance;
    bool m_is_open;
    mutable std::mutex m_mtx;
    
public:
    Bankaccount();
    void open();
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);
    void close();
    std::int64_t balance() const;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
