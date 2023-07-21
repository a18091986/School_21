import os
from random import choice, sample, seed
from itertools import permutations

test_file_name_1 = "test_1.txt"
test_file_name_2 = "test_2.txt"

def test_all_combinations_of_flags():
    fails_counter = 0
    test_counter = 0
    short_flags = ["e", "i", "v", "c", "l", "n", "h", "s", "f", "o"]
    short_flags_without_e = ["i",  "c", "l", "n",  "h", "s",   "f",  "o"]
    short_flags_without_f = ["e", "i",  "c",  "l", "n",  "h",  "s",  "o"]

    for flag in short_flags:
        fails_counter += difference_calculation(f"{flag}")
        test_counter += 1
    for i in range(2, 3):
        for flag_combination in list(permutations(short_flags_without_e, i)):
            flag_combination = "".join(flag_combination)
            fails_counter += difference_calculation(f"{flag_combination}")  
            test_counter += 1
    for i in range(2, 3):
        for flag_combination in list(permutations(short_flags_without_f, i)):
            flag_combination = "".join(flag_combination)
            fails_counter += difference_calculation(f"{flag_combination}")
            test_counter += 1
    print(f"Проведено {test_counter} тестов.\n\
PASSED: {test_counter - fails_counter}, FAIL: {fails_counter}")


def difference_calculation(flags: str):
    template = 'yet' if 'f' not in flags else ''
    file_name_with_templates = "templates.txt" if "f" in flags else ''
    if len(flags) == 1:    
        query_grep = f'grep -{flags} {template} {file_name_with_templates} {test_file_name_1} {test_file_name_2} > system_grep'
        query_system = f'./s21_grep -{flags} {template} {file_name_with_templates} {test_file_name_1} {test_file_name_2} > my_grep'    
    else:
        if ('e' in flags or 'f' in flags):
            f = '-f' if 'f' in flags else ''
            e = '-e' if 'e' in flags else ''
            flags_ = flags.replace('f', '').replace('e', '')
            flags_ = ('-' + flags_)
            query_grep = f'grep {f}{e} {template} {file_name_with_templates} {flags_} {test_file_name_1} {test_file_name_2} > system_grep'
            query_system = f'./s21_grep {f}{e} {template} {file_name_with_templates} {flags_} {test_file_name_1} {test_file_name_2} > my_grep'
        else:
            query_grep = f'grep -{flags} {template} {file_name_with_templates} {test_file_name_1} {test_file_name_2} > system_grep'
            query_system = f'./s21_grep -{flags} {template} {file_name_with_templates} {test_file_name_1} {test_file_name_2} > my_grep'
    os.system(query_grep)
    os.system(query_system)
    with open("system_grep", "r") as f:
                sys_grep = f.read()
    with open("my_grep", "r") as f:
                my_grep = f.read()
    if sys_grep == my_grep:
        print(f'{flags}: PASSED')
        return 0
    else:
        print(f'{flags}: FAIL')
        print(query_grep)
        print(query_system)
        return 1


if __name__ == '__main__':
    test_all_combinations_of_flags()
