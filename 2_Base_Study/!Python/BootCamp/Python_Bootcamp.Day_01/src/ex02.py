from ex00 import add_ingot as ai, get_ingot as gi, empty as em
from typing import Dict, Optional
import copy

def print_squeak(f):
    def wrapper(*args):
        print('SQUEAK')
        return f(*args)
    return wrapper

@print_squeak
def add_ingot(purse: Dict[str, int]):
    return ai(purse)
    
@print_squeak
def get_ingot(purse: Dict[str, int]):
    return gi(purse)

@print_squeak
def empty(purse: Optional[Dict[str, int]] = dict()):
    return em(purse)

if __name__ == "__main__":
    print(add_ingot(dict(gold_ingots=1)))
    print(add_ingot(get_ingot(empty())))
    print(empty(dict(gold_ingots=1)))

