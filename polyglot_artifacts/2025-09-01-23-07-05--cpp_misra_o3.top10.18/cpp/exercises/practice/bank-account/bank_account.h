#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

/* Fixed-width integral type for all monetary values */
using Amount = std::int64_t;

/* Thread-safe bank account that supports concurrent access.            */
/* All public member functions provide the strong exception guarantee.  */
class Bankaccount {
public:
    Bankaccount() noexcept;

    /* (Re)-open the account; resets balance to 0.                       */
    void open();

    /* Close the account; further operations (besides open()) throw.     */
    void close();

    /* Deposit a non-negative amount of money.                           */
    void deposit(Amount amount);

    /* Withdraw a non-negative amount; throws if funds are insufficient. */
    void withdraw(Amount amount);

    /* Obtain the current balance.                                       */
    Amount balance() const;

    /* Query whether the account is currently open.                      */
    bool is_open() const noexcept;

private:
    mutable std::mutex m_mutex;  /* protects the members below                         */
    Amount             m_balance{0}; /* current balance, valid only when m_open == true */
    bool               m_open{false}; /* account state                                  */
};  /* class Bankaccount */

}  /* namespace Bankaccount */

#endif  /* BANK_ACCOUNT_H */
