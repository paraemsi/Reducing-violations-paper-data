#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount final {
public:
    using Money = std::int64_t;

    Bankaccount() noexcept;

    void open();
    void close();

    void deposit(Money amount);
    void withdraw(Money amount);

    [[nodiscard]] Money balance() const;

private:
    mutable std::mutex m_mutex;
    bool m_is_open;
    Money m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
