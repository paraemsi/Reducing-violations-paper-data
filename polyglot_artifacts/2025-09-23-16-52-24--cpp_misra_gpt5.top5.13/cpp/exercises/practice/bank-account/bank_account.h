#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount {  // class Bankaccount
public:
    Bankaccount() = default;
    ~Bankaccount() = default;

    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&& other) noexcept;
    Bankaccount& operator=(Bankaccount&& other) noexcept;

    void open();
    void close();
    void deposit(std::int64_t amount);
    void withdraw(std::int64_t amount);
    std::int64_t balance() const;

private:
    mutable std::mutex m_mutex {};
    bool m_is_open { false };
    std::int64_t m_balance { 0 };
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
