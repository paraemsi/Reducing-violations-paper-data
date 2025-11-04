#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount() noexcept;
    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&) = delete;
    Bankaccount& operator=(Bankaccount&&) = delete;

    void open();
    void close();

    void deposit(int64_t amount);
    void withdraw(int64_t amount);

    int64_t balance() const;

private:
    mutable std::mutex m_mutex;
    bool m_open;
    int64_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
