#include "../Model/model.h"

namespace s21
{
    class Controller
    {
    public:
        Controller() : ex() {}

        inline double Validation(const std::string &InputExpression) noexcept { return ex.validation(InputExpression.c_str()); }
        inline double Calculate(const std::string &InputExpression, const double &x = 0) noexcept { return ex.MainCalculate(InputExpression, x); }

    private:
        Model ex;
    };
}