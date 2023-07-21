import os
from random import choice, sample, seed
from itertools import permutations

test_file_name_1 = "test.txt"
test_file_name_2 = "test.txt"
# test_file_name_2 = "tset.txt"

def test_all_combinations_of_flags():
    fails_counter = 0
    test_counter = 0
    long_flags = ["number-nonblank", "number", "squeeze-blank"]
    short_flags = ["b", "e", "n", "s", "t"]#, "E", "T"]
    for i in range(1, 6):
        for flag_combination in list(permutations(short_flags, i)):
            flag_combination = "".join(flag_combination)
            fails_counter += difference_calculation(f"-{flag_combination}")
            test_counter += 1
            # long_flag = '--' + choice(long_flags)
            # flags = short_flags + ' ' + long_flag
            # difference_calculation(f"{long_flag}")
            # difference_calculation(f"-{flags}") 
    print(f"Проведено {test_counter} тестов.\n\
PASSED: {test_counter - fails_counter}, FAIL: {fails_counter}")


def difference_calculation(flags: str):
    # query_cat = f'cat {flags} {test_file_name_1}'
    # query_s21_cat = f'./s21_cat {flags} {test_file_name_1}'
    query_cat = f'cat {flags} {test_file_name_1} {test_file_name_2}'
    query_s21_cat = f'./s21_cat {flags} {test_file_name_1} {test_file_name_2}'
    os.system(f'{query_cat} > system_cat')
    os.system(f'{query_s21_cat} > my_cat')
    with open("system_cat", "r") as f:
                sys_cat = f.read()
    with open("my_cat", "r") as f:
                my_cat = f.read()
    if sys_cat == my_cat:
        print(f'{flags}: PASSED')
        return 0
    else:
        print(f'{flags}: FAIL')
        print(query_s21_cat)
        print(query_cat)
        return 1


if __name__ == '__main__':
    test_all_combinations_of_flags()
