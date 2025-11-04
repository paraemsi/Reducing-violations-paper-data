#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H
#include <cstdint>
#include <mutex>

namespace Bankaccount
{

class Bankaccount final
{
public:
    using balance_t = std::int64_t;

    Bankaccount() noexcept;

    void open();
    void close();

    void deposit(balance_t amount);
    void withdraw(balance_t amount);

    balance_t balance() const;

private:
    mutable std::mutex m_mutex{};
    bool m_is_open{false};
    balance_t m_balance{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
