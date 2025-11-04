#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

using money_t = std::int64_t;

class Bankaccount {  // class Bankaccount
public:
    Bankaccount() noexcept;
    ~Bankaccount() = default;

    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&) = delete;
    Bankaccount& operator=(Bankaccount&&) = delete;

    void open();
    void close();

    void deposit(money_t amount);
    void withdraw(money_t amount);
    money_t balance() const;

private:
    mutable std::mutex m_mutex;
    bool m_open;
    money_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
