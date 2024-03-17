import argparse


def check_string(s: str, count: int):
    if len(s) != 5:
        return False
    if count == 0 and s[0] == s[4] == '*' and '*' not in s[1:4]:
        return True
    if count == 1 and s[0] == s[1] == s[3] == s[4] == '*' and s[2] != '*':
        return True
    if count == 2 and s[0] == s[2] == s[4] == '*' and s[1] != '*' and s[3] != '*':
        return True
    else:
        return False


def check_input():
    result = True
    for i in range(3):
        try:
            if not check_string(input().strip(), i):
                result = False
        except Exception as e:
            result = False
            break
    try:
        input()
        result = False
    except Exception as e:
        pass
    print(result)


if __name__ == '__main__':
    check_input()
