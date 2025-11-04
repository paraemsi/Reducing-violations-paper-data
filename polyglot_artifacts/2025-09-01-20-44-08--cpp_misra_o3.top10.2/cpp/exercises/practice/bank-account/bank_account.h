#ifndef BANK_ACCOUNT_BANK_ACCOUNT_H
#define BANK_ACCOUNT_BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

using amount_t = std::int32_t;

class Bankaccount {
public:
    Bankaccount() = default;
    ~Bankaccount() = default;

    void open();
    void close();
    void deposit(amount_t amount);
    void withdraw(amount_t amount);
    amount_t balance() const;

private:
    mutable std::mutex m_mutex {};
    bool m_is_open {false};
    amount_t m_balance {static_cast<amount_t>(0)};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_BANK_ACCOUNT_H
