#if !defined(BANK_ACCOUNT_H)
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

    void deposit(const std::int64_t amount);
    void withdraw(const std::int64_t amount);

    [[nodiscard]] std::int64_t balance() const;

private:
    mutable std::mutex m_mutex {};
    std::int64_t       m_balance { static_cast<std::int64_t>(0) };
    bool               m_open { false };
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
