import sys


def get_right_strings(count: int):
    for c in range(count):
        try:
            cur = input().strip()
            if cur.startswith('00000') and cur[5] != '0' and len(cur) == 32:
                print(cur)
        except EOFError:
            print(f"В поданном на вход файле меньше строк, чем было указано, завершение программы")
            break
        except Exception as e:
            print(f"Во время выполнения программы произошла ошибка:\n{e}")


if __name__ == '__main__':
    arg = sys.argv[-1]
    if arg.isdigit():
        get_right_strings(int(arg))
    else:
        print('Incorrect command line arg')
