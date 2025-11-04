#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

using amount_t = std::int64_t;

class Bankaccount {
public:
    Bankaccount() = default;

    void open();
    void close();
    amount_t balance() const;
    void deposit(amount_t amount);
    void withdraw(amount_t amount);

private:
    mutable std::mutex m_mutex {};
    amount_t           m_balance { static_cast<amount_t>(0) };
    bool               m_open    { false };
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
