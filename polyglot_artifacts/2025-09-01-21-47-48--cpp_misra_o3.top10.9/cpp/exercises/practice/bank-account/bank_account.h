#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

class Bankaccount final
{
public:
    Bankaccount() = default;
    Bankaccount(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount& operator=(Bankaccount&&) = delete;

    void open();
    void close();
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);
    [[nodiscard]] std::int64_t balance() const;

private:
    mutable std::mutex m_mutex{};
    std::int64_t       m_balance{static_cast<std::int64_t>(0)};
    bool               m_is_open{false};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
