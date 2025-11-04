#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount {
public:
    using amount_type = std::int64_t;

    Bankaccount();
    ~Bankaccount() = default;

    void open();
    void close();
    void deposit(amount_type amount);
    void withdraw(amount_type amount);
    amount_type balance() const;

private:
    mutable std::mutex m_mutex;
    bool m_open{false};
    amount_type m_balance{static_cast<amount_type>(0)};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
