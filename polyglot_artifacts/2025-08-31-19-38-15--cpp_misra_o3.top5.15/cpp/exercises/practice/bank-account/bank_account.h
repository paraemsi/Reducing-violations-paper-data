#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {


/*
 * Thread-safe bank account supporting open / close, deposit, withdraw, and
 * balance query.  All monetary amounts are maintained as signed 64-bit
 * integers (std::int64_t) to prevent any loss of precision while still
 * allowing negative intermediate values when checking overdraft conditions.
 */
class Bankaccount {
public:
    Bankaccount() noexcept;
    ~Bankaccount() = default;

    /* Non-copyable and non-movable to prevent mutex copying */
    Bankaccount(const Bankaccount&)            = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&)                 = delete;
    Bankaccount& operator=(Bankaccount&&)      = delete;

    void open();
    void close();

    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);

    [[nodiscard]] std::int64_t balance() const;

private:
    mutable std::mutex m_mutex; /* protects all data below */
    bool               m_open;
    std::int64_t       m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
