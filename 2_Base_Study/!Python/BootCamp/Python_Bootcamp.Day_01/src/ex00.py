from typing import Dict, Optional
import copy

def check_right_dict(purse: Dict[str, int]) -> bool:
    return (isinstance(purse, dict) and 
        all([isinstance(x, str) for x in purse.keys()]) and
        all([isinstance(purse.get(x), int) for x in purse.keys()]))


def add_ingot(purse: Dict[str, int]):
    try:
        if check_right_dict(purse):
            new_purse = copy.deepcopy(purse)
            if new_purse.get('gold_ingots'):
                if new_purse.get('gold_ingots') < 0:
                    raise ValueError("Не надо мне подпихивать фейковый кошелек!")
                else: 
                    new_purse['gold_ingots'] += 1    
            else: 
                new_purse['gold_ingots'] = 1
            return new_purse
        else:
            raise TypeError("Кошелек - это словарь! Ключ - строка, значение - число!")
    except Exception as e:
        print(e)
        return Exception

def get_ingot(purse: Dict[str, int]):
    try:
        if check_right_dict(purse):
            new_purse = copy.deepcopy(purse)
            if new_purse.get('gold_ingots'):
                if new_purse.get('gold_ingots') < 0:
                    raise ValueError("Не надо мне подпихивать фейковый кошелек!")
                else:
                    new_purse['gold_ingots'] -= 1
            return new_purse    
        else:
            raise TypeError("Кошелек - это словарь!")
    except Exception as e:
        print(e)
        return Exception


def empty(purse: Optional[Dict[str, int]] = dict()):
    try:
        if check_right_dict(purse):
            new_purse = copy.deepcopy(purse)
            if new_purse.get('gold_ingots'):
                if new_purse.get('gold_ingots') < 0:
                    raise ValueError("Не надо мне подпихивать фейковый кошелек!")
            return dict()
        else:
            raise TypeError("Кошелек - это словарь!")
    except Exception as e:
        print(e)
        return Exception

if __name__ == "__main__":
    print(add_ingot(dict(gold_ingots="1")))
    print(add_ingot(get_ingot(empty())))
    print(empty(dict(gold_ingots=-1)))

