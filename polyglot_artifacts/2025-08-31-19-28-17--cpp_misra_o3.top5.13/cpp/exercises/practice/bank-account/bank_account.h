#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {
class Bankaccount {
 public:
    Bankaccount() noexcept;

    void open();
    void close();

    void deposit(std::int32_t amount);
    void withdraw(std::int32_t amount);

    [[nodiscard]] std::int32_t balance() const;

 private:
    mutable std::mutex m_mutex_{};
    std::int32_t m_balance_{static_cast<std::int32_t>(0)};
    bool m_is_open_{false};

    void ensure_open() const;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
