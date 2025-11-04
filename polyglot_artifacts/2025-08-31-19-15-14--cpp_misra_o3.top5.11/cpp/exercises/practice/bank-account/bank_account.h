#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H
#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {
class Bankaccount
{
public:
    Bankaccount() = default;
    void open();
    void close();
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);
    std::int64_t balance() const;

private:
    mutable std::mutex m_mutex {};
    bool m_is_open {false};
    std::int64_t m_balance {static_cast<std::int64_t>(0)};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
