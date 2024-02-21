#include <stack>
#include <queue>
#include <iostream>
#include <math.h>
#include <cstring>

class Model
{
    struct Data;

public:
    double MainCalculate(const std::string &InputExpression, const double &x = 0) noexcept;
    int validation(const char *str);

private:
    int assign(const char *tmp_value, std::string &nameFunction, int *i) noexcept;
    double Calc(std::queue<Data> &mainQueue, std::stack<Data> &supportingStack) noexcept;

    void operator_check_str(const char *str, int *error, int i);
    void func_check_str(const char *str, int *error, int *i);
    int number_check(char sym);

    struct Data
    {
        Data(const int priority, const std::string nameFunction = std::string())
            : priority_(priority), nameFunction_(std::move(nameFunction)) {}

        explicit Data(const double number) : number_(number) {}

        const int priority_ = 0;
        const std::string nameFunction_;
        const double number_ = 0;
    };
};
