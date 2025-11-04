#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {
class Bankaccount final {
public:
    Bankaccount() noexcept;

    void open();
    void close();

    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);

    [[nodiscard]] std::int64_t balance() const;

private:
    mutable std::mutex mtx_{};
    bool is_open_{false};
    std::int64_t balance_{static_cast<std::int64_t>(0)};
};  // class Bankaccount
}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
