#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount() noexcept;

    void open();
    void close();
    std::int64_t balance() const;
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);

private:
    mutable std::mutex m_mutex;
    bool m_is_open;
    std::int64_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
