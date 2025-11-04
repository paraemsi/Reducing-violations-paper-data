#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount();
    void open();
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);
    std::int64_t balance() const;
    void close();
private:
    mutable std::mutex mtx;
    std::int64_t m_balance;
    bool m_is_open;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
