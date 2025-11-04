#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount
{
public:
    Bankaccount() = default;

    void open();
    void close();
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);
    [[nodiscard]] std::int64_t balance() const;

private:
    mutable std::mutex m_mutex{};
    bool               m_open{false};
    std::int64_t       m_balance{std::int64_t{0}};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
