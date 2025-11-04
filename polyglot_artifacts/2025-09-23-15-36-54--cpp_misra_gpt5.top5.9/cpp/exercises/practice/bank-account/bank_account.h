#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

using Amount = std::int64_t;

class Bankaccount {
public:
    Bankaccount() noexcept;
    ~Bankaccount() = default;

    void open();
    void close();

    void deposit(Amount amount);
    void withdraw(Amount amount);

    Amount balance() const;

    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;

private:
    mutable std::mutex m_mutex;
    bool m_is_open;
    Amount m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
