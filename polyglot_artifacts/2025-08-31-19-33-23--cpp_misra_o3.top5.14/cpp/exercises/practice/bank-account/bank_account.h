#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {
class Bankaccount
{
public:
    Bankaccount() noexcept;

    void open();
    void close();

    void deposit(std::int32_t amount);
    void withdraw(std::int32_t amount);

    [[nodiscard]] std::int32_t balance() const;

private:
    mutable std::mutex m_mutex;
    bool m_is_open;
    std::int32_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount


#endif  // BANK_ACCOUNT_H
