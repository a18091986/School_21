from typing import Iterator, Callable
from random import randint, uniform
import time


# def emit_gel(step: int) -> Iterator[int]:
def emit_gel(step: int = randint(10, 21)) -> Iterator[int]:
    sign = 1
    pressure: int = randint(20, 80)
    print(f"Start pressure: {pressure}")
    while True:
        if pressure > 0 and pressure < 100:
            step_ = randint(0, step)
            pressure += sign * step_
            print(f"Current step: {step_}")
            print(f"Current pressure: {pressure}")
            if pressure > 100:
                print('Stop because preasure > 100')
                break
            change = (yield pressure)
            sign = -sign if change is not None else sign
        else:
            print('break')
            break
        


def valve(gen: Iterator[int]) -> None:
    for pressure in gen:
        # print(f"Current pressure: {pressure}")
        if pressure < 10 or pressure > 90:
            print("Stop! Pressure:", pressure)
            break
        if pressure < 20 or pressure > 80:
            print(f"Change step sign")
            gen.send(-1)
        

def tests() -> None:
    print('\nTEST1\n')
    valve(emit_gel, 50, True, True)
    print('\nTEST2\n')
    valve(emit_gel, 22, True, False)


if __name__ == '__main__':
    # print('test')
    # eg = emit_gel()
    # print(eg.__next__())
    # print(eg.__next__())
    # print(eg.__next__())
    # print(eg.__next__())
    # print(eg.__next__())
    # step = randint(10, 20)
    # valve(emit_gel(step))
    # valve(emit_gel(2))
    valve(emit_gel())
    # print(emit_gel(2).__next__())
    # tests()