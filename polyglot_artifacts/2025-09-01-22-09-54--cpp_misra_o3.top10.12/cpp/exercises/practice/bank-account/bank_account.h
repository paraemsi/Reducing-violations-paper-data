#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

/*
 * Thread-safe bank account supporting open/close,
 * deposits, withdrawals and balance inquiries.
 * All monetary values are represented with std::int64_t
 * to avoid implicit integral promotions.
 */
class Bankaccount {
public:
    Bankaccount() noexcept;

    /* Mark the account as open; throws if already open */
    void open();

    /* Mark the account as closed; throws if already closed */
    void close();

    /* Deposit a positive amount; throws on error or if closed */
    void deposit(std::int64_t amount);

    /* Withdraw a positive amount; throws on error or if closed/insufficient funds */
    void withdraw(std::int64_t amount);

    /* Obtain current balance; throws if account is closed */
    [[nodiscard]] std::int64_t balance() const;

private:
    mutable std::mutex m_mutex;
    bool               m_open;          /* true while the account is open   */
    std::int64_t       m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
