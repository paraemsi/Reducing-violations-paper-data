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
    void deposit(amount_t amount);
    void withdraw(amount_t amount);
    [[nodiscard]] amount_t balance() const;

private:
    mutable std::mutex m_mutex_{};
    bool m_is_open_{false};
    amount_t m_balance_{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
