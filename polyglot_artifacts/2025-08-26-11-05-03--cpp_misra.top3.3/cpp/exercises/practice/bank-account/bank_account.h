#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

using money_t = std::int64_t;

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    void open();
    void close();
    bool is_open() const;

    // Returns true on success, false if account is closed
    bool deposit(money_t amount);
    bool withdraw(money_t amount);

    // Returns the current balance, or throws std::runtime_error if closed
    money_t balance() const;

private:
    mutable std::mutex mtx_;
    money_t balance_;
    bool open_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
