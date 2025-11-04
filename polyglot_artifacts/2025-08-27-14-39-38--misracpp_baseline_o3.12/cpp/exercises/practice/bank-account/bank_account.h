#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount() noexcept;

    // Open the account. Throws if already open.
    void open();

    // Close the account. Throws if already closed.
    void close();

    // Return current balance. Throws if account is closed.
    int64_t balance() const;

    // Deposit a positive amount. Throws if amount is negative or account closed.
    void deposit(int64_t amount);

    // Withdraw a positive amount. Throws if amount is negative, overdraft, or account closed.
    void withdraw(int64_t amount);

private:
    mutable std::mutex m_mutex{};
    bool m_open{false};
    int64_t m_balance{0};
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
