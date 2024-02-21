#include "model.h"

double Model::MainCalculate(const std::string &InputExpression, const double &x) noexcept
{
    std::queue<Data> mainQueue;       // основная очередь - распарсенная польская строка, постфиксная запись называется вроде:)
    std::stack<Data> supportingStack; // вспомогательный стек для мат. функций (приоритет функций, в каком порядке закидывать их в очередь)

    long double total = 0; // результат
    int flag_digit = 0;    // проверка на конец строки, если идет одно лишь число, вывести его в ответ

    int i = 0;       // основной итератор
    int bracket = 0; // если очередь пуста или скобка и идет + или - то ставим 0 перед знаком
    while (InputExpression[i] != '\0')
    {
        if ((InputExpression[i] >= 48 && InputExpression[i] <= 57)) // парсинг чисел
        {
            std::string tmp;
            double tmp_number = 0;
            for (int q = 0; ((InputExpression[i] >= 48 && InputExpression[i] <= 57) || InputExpression[i] == 46); q++)
            {
                tmp += InputExpression[i];
                ++i;
            }
            bracket = 0;
            std::sscanf(tmp.c_str(), "%lf", &tmp_number); // записываем число в дабл

            if (InputExpression[i] == '\0' && mainQueue.empty())
            {
                total = tmp_number;
                flag_digit = 1;
            }
            else
                mainQueue.push(Data(tmp_number)); // закидваем в очередь
        }
        else if (InputExpression[i] == ' ' && !flag_digit) // на си должен работать с пробелами, в граф. не работает, валидатор не пропускает
        {
            ++i;
            continue;
        }
        else if (InputExpression[i] == 'x' && !flag_digit) // обработка X
        {
            if (InputExpression[i + 1] == '\0' && mainQueue.empty())
            {
                total = x;
                flag_digit = 1;
            }
            else
                mainQueue.push(Data(x));

            ++i;
            bracket = 0;
        }
        else
        {
            std::string nameFunction;
            int priority = 0;
            priority = assign(&InputExpression[i], nameFunction, &i); // вытаскиваем функцию и приоритет

            if ((mainQueue.empty() || bracket) && (nameFunction == "-" || nameFunction == "+")) // если очередь пуста или скобка и идет + или - то ставим 0 перед знаком
            {
                mainQueue.push(Data(double(0)));
                supportingStack.push(Data(priority, nameFunction));
                ++i;
            }
            else if (supportingStack.empty())
            {
                supportingStack.push(Data(priority, nameFunction));
                ++i;
                if (nameFunction == "(")
                    bracket = 1;
            }
            else if (priority > supportingStack.top().priority_ && nameFunction != ")") // проверка на приоритет - основная логика польской нотации
            {
                supportingStack.push(Data(priority, nameFunction));
                ++i;
                if (nameFunction == "(")
                    bracket = 1;
            }
            else if (priority <= supportingStack.top().priority_ && nameFunction != ")") // проверка на приоритет - основная логика польской нотации
            {
                while (!supportingStack.empty() && priority <= supportingStack.top().priority_) // пока не дойдем до скобки, выкидываем в основную очередь
                {
                    if (supportingStack.top().nameFunction_ == "(")
                    {
                        break;
                    }
                    else
                    {
                        mainQueue.push(Data(supportingStack.top().priority_, supportingStack.top().nameFunction_));
                        supportingStack.pop();
                    }
                }
                supportingStack.push(Data(priority, nameFunction));
                ++i;
            }
            else if (nameFunction == ")") // если поймали обратную скобку, выкидывем все оставшееся
            {
                while (supportingStack.top().nameFunction_ != "(")
                {
                    mainQueue.push(Data(supportingStack.top().priority_, supportingStack.top().nameFunction_));
                    supportingStack.pop();
                }
                if (supportingStack.top().nameFunction_ == "(")
                {
                    supportingStack.pop();
                    ++i;
                }
                bracket = 0;
            }
        }
        if (InputExpression[i] == '\0') // конец парсинга мат. функций
            while (!supportingStack.empty())
            {
                mainQueue.push(Data(supportingStack.top().priority_, supportingStack.top().nameFunction_));
                supportingStack.pop();
            }
    }
    if (!flag_digit)
        total = Calc(mainQueue, supportingStack); // итого

    return total;
}

int Model::assign(const char *tmp_value, std::string &nameFunction, int *i) noexcept
{
    int priority = 0;

    if (*tmp_value == '+')
    {
        priority = 1;
        nameFunction = "+";
    }
    if (*tmp_value == '-')
    {
        priority = 1;
        nameFunction = "-";
    }
    else if (*tmp_value == '*' || *tmp_value == '/' || *tmp_value == 'm')
    {
        priority = 2;
        if (*tmp_value == 'm')
        {
            nameFunction = "mod";
            *i += 2;
        }
        else if (*tmp_value == '*')
        {
            nameFunction = "*";
        }
        else
        {
            nameFunction = "/";
        }
    }
    else if (*tmp_value == '^')
    {
        priority = 3;
        nameFunction = "^";
    }
    else if (*tmp_value == 's')
    {
        priority = 4;
        if (*(tmp_value + 1) == 'i')
        {
            nameFunction = "sin";
            *i += 2;
        }
        else if (*(tmp_value + 1) == 'q')
        {
            nameFunction = "sqrt";
            *i += 3;
        }
    }
    else if (*tmp_value == 'c')
    {
        priority = 4;
        nameFunction = "cos";
        *i += 2;
    }
    else if (*tmp_value == 't')
    {
        priority = 4;
        nameFunction = "tan";
        *i += 2;
    }
    else if (*tmp_value == 'a')
    {
        priority = 4;
        if (*(tmp_value + 1) == 'c')
        {
            nameFunction = "acos";
            *i += 3;
        }
        if (*(tmp_value + 1) == 's')
        {
            nameFunction = "asin";
            *i += 3;
        }
        if (*(tmp_value + 1) == 't')
        {
            nameFunction = "atan";
            *i += 3;
        }
    }
    else if (*tmp_value == 'l')
    {
        priority = 4;
        if (*(tmp_value + 1) == 'o')
        {
            nameFunction = "log";
            *i += 2;
        }
        else
        {
            nameFunction = "ln";
            *i += 1;
        }
    }

    else if (*tmp_value == '(')
    {
        priority = 5;
        nameFunction = "(";
    }
    else if (*tmp_value == ')')
    {
        priority = 5;
        nameFunction = ")";
    }

    return priority;
}

double Model::Calc(std::queue<Data> &mainQueue, std::stack<Data> &supportingStack) noexcept
{
    while (!mainQueue.empty()) // пока в очереди есть элементы
    {
        if (mainQueue.front().number_ || !mainQueue.front().priority_) // закидываем в стек
        {
            supportingStack.push(Data((double)mainQueue.front().number_));
            mainQueue.pop();
        }
        else
        {
            if (mainQueue.front().nameFunction_ == "+")
            {
                double B = supportingStack.top().number_;
                supportingStack.pop();
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(A + B));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "-")
            {
                double B = supportingStack.top().number_;
                supportingStack.pop();
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(A - B));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "*")
            {
                double B = supportingStack.top().number_;
                supportingStack.pop();
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(A * B));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "/")
            {
                double B = supportingStack.top().number_;
                supportingStack.pop();
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(A / B));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "^")
            {
                double B = supportingStack.top().number_;
                supportingStack.pop();
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(pow(A, B)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "sin")
            {
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(sin(A)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "cos")
            {
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(cos(A)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "tan")
            {
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(tan(A)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "asin")
            {
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(asin(A)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "acos")
            {
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(acos(A)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "atan")
            {
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(atan(A)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "log")
            {
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(log10(A)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "ln")
            {
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(log(A)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "sqrt")
            {
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(sqrt(A)));
                mainQueue.pop();
            }
            else if (mainQueue.front().nameFunction_ == "mod")
            {
                double B = supportingStack.top().number_;
                supportingStack.pop();
                double A = supportingStack.top().number_;
                supportingStack.pop();
                supportingStack.push(Data(fmod(A, B)));
                mainQueue.pop();
            }
        }
    }

    return supportingStack.top().number_;
}
