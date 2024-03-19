from typing import Dict
from ex00 import add_ingot, get_ingot, empty, check_right_dict

def split_booty(*purse: Dict[str, int]) -> tuple[Dict[str, int], ...]:
    try:
        sum_ingot = 0
        for p in purse:
            if check_right_dict(p):
                while p.get('gold_ingots'):
                    sum_ingot += 1
                    p = get_ingot(p)
            else:
                raise TypeError("Кошелек - это словарь! Ключ - строка, значение - число!")
    except Exception as e:
        print(e)
        return Exception
        
    if sum_ingot % 3 == 0:
        first, second, third = sum_ingot // 3, sum_ingot // 3, sum_ingot // 3
    elif sum_ingot % 3 == 1:
        first, second, third = sum_ingot // 3 + 1, sum_ingot // 3, sum_ingot // 3
    else:
        first, second, third = sum_ingot // 3 + 1, sum_ingot // 3 + 1, sum_ingot // 3
    return (dict(gold_ingots=first), 
           dict(gold_ingots=second), 
           dict(gold_ingots=third))


if __name__ == '__main__':
    print(split_booty(dict(gold_ingots=0), dict(gold_ingots=6), dict()))