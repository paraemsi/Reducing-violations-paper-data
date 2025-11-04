#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount {  // class Bankaccount
public:
    using amount_type = std::int64_t;

    Bankaccount() noexcept;
    ~Bankaccount() noexcept = default;
    Bankaccount(Bankaccount const&) = delete;
    Bankaccount& operator=(Bankaccount const&) = delete;
    Bankaccount(Bankaccount&&) = delete;
    Bankaccount& operator=(Bankaccount&&) = delete;

    void open();
    void close();

    void deposit(amount_type amount);
    void withdraw(amount_type amount);

    amount_type balance() const;

private:
    mutable std::mutex m_mutex;
    amount_type m_balance;
    bool m_open;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
