#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount final {
public:
    Bankaccount() noexcept = default;
    ~Bankaccount() = default;

    void open();
    void close();

    void deposit(std::int64_t const amount);
    void withdraw(std::int64_t const amount);

    [[nodiscard]] std::int64_t balance() const;

    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&) = delete;
    Bankaccount& operator=(Bankaccount&&) = delete;

private:
    mutable std::mutex m_mutex {};
    bool m_is_open {false};
    std::int64_t m_balance {static_cast<std::int64_t>(0)};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
