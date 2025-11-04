#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

typedef std::int64_t money_t;

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    void open();
    void close();

    void deposit(money_t amount);
    void withdraw(money_t amount);

    money_t balance() const;

private:
    mutable std::mutex mtx_;
    bool is_open_;
    money_t balance_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
