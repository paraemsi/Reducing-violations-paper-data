#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount {  // class Bankaccount
public:
    Bankaccount() noexcept;
    ~Bankaccount() noexcept = default;

    using amount_type = std::int64_t;

    Bankaccount(const Bankaccount&) = delete;
    Bankaccount& operator=(const Bankaccount&) = delete;
    Bankaccount(Bankaccount&&) = delete;
    Bankaccount& operator=(Bankaccount&&) = delete;

    void open();
    void close();

    void deposit(amount_type amount);
    void withdraw(amount_type amount);

    amount_type balance() const;

private:
    bool m_is_open;
    amount_type m_balance;
    mutable std::mutex m_mutex;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
