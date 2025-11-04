#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H
#include <cstdint>
#include <mutex>

namespace Bankaccount {
using money_t = std::int64_t;  // fixed-width integral type for monetary values
class Bankaccount {
public:
    Bankaccount() noexcept;
    ~Bankaccount() noexcept = default;

    void open();
    void close();

    void deposit(money_t amount);
    void withdraw(money_t amount);

    money_t balance() const;

private:
    mutable std::mutex m_mutex;
    bool m_is_open;
    money_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
