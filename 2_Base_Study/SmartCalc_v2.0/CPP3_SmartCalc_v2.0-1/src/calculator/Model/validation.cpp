#include "model.h"

int Model::validation(const char *str)
{
  int error = 0;
  int n = strlen(str);
  if (!strlen(str))
  {
    error = 1;
  }
  else
  {
    int brocket = 0;
    for (int i = 0; i < n; i++)
    {
      if (error == 0)
      {
        operator_check_str(str, &error, i);
      }
      if (error == 0)
      {
        func_check_str(str, &error, &i);
      }
      if (str[i] == '(')
      {
        brocket++;
      }
      if (str[i] == ')')
      {
        brocket--;
      }
    }
    if (brocket)
    {
      error = 1;
    }
  }
  return error;
}

void Model::operator_check_str(const char *str, int *error, int i)
{
  if (str[0] == '/' || str[0] == '*' || str[0] == '^' || str[0] == 'm' ||
      str[0] == '.')
  {
    *error = 1;
  }
  else if ((str[i] == '+' || str[i] == '-' || str[i] == '/' ||
            str[i] == '*' || str[i] == '^') &&
           (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '/' ||
            str[i + 1] == '*' || str[i + 1] == '^'))
  {
    *error = 1;
  }
  else if (*error == 0)
  {
    int z = strlen(str) - 1;
    if (*error == 0 && (str[z] == '+' || str[z] == '-' || str[z] == '*' ||
                        str[z] == '/' || str[z] == '^' || str[z] == '.'))
    {
      *error = 1;
    }
  }
  else if ((str[i] == '(') && (str[i + 1] == ')'))
  {
    *error = 1;
  }
  else if ((*error == 0) &&
           (str[i] == '+' || str[i] == '-' || str[i] == '*' ||
            str[i] == '/' || str[i] == '^') &&
           (str[i + 1] == ')'))
  {
    *error = 1;
  }
  if ((number_check(str[i]) && str[i + 1] == '.' && number_check(str[i + 2]) &&
       str[i + 3] == '.') ||
      (str[i] == '.' && str[i + 1] == '.'))
  {
    *error = 1;
  }
  else if ((number_check(str[i]) && str[i + 1] == '.' && str[i + 2] == 'x') ||
           (str[i] == 'x' && str[i + 1] == '.' && number_check(str[i + 2])))
  {
    *error = 1;
  }
}

void Model::func_check_str(const char *str, int *error, int *i)
{
  if (str[*i] == '.')
  {
    *i = *i;
  }
  else if (str[*i] == 'x')
  {
    *i = *i;
    if (str[*i] == 'x' && ((str[*i - 1] >= '0' && str[*i - 1] <= '9') || (str[*i + 1] >= '0' && str[*i + 1] <= '9')))
    {
      *error = 1;
    }
  }
  else if (str[*i] >= '0' && str[*i] <= '9')
  {
    *i = *i;
  }
  else if (str[*i] == '+' || str[*i] == '-' || str[*i] == '*' ||
           str[*i] == '/' || str[*i] == '^')
  {
    *i = *i;
  }
  else if (str[*i] == '(')
  {
    *error = 0;
  }
  else if (str[*i] == ')')
  {
    *error = 0;
  }
  else if ((str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd') &&
           ((str[*i + 3] >= '0' && str[*i + 3] <= '9') || (str[*i + 3] == '(')))
  {
    *i = *i + 2;
  }
  else if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's' &&
           str[*i + 3] == '(')
  {
    *i = *i + 2;
  }
  else if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n' &&
           str[*i + 3] == '(')
  {
    *i = *i + 2;
  }
  else if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n' &&
           str[*i + 3] == '(')
  {
    *i = *i + 2;
  }
  else if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
           str[*i + 3] == 's' && str[*i + 4] == '(')
  {
    *i = *i + 3;
  }
  else if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'i' &&
           str[*i + 3] == 'n' && str[*i + 4] == '(')
  {
    *i = *i + 3;
  }
  else if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
           str[*i + 3] == 'n' && str[*i + 4] == '(')
  {
    *i = *i + 3;
  }
  else if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
           str[*i + 3] == 't' && str[*i + 4] == '(')
  {
    *i = *i + 3;
  }
  else if (str[*i] == 'l' && str[*i + 1] == 'n' && str[*i + 2] == '(')
  {
    *i = *i + 1;
  }
  else if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g' &&
           str[*i + 3] == '(')
  {
    *i = *i + 2;
  }
  else
  {
    *error = 1;
  }
}

int Model::number_check(char sym)
{
  int res = 0;
  if (sym >= '0' && sym <= '9')
  {
    res = 1;
  }
  return res;
}
