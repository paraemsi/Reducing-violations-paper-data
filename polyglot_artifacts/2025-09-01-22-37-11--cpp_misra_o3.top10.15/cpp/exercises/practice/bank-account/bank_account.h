#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount final
{
public:
    Bankaccount() noexcept;

    void open();
    void close();

    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);

    std::uint64_t balance() const;

private:
    mutable std::mutex m_mutex;
    bool m_open;
    std::uint64_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
