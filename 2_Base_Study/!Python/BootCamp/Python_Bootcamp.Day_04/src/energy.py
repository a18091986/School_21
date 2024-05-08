from typing import Any, List


def fix_wiring(cables: list, sockets: list, plugs: list):
    return [
        f"{'plug' if x[2] else 'weld'} {x[0]} into {x[1]} {f'using {x[2]}' if x[2] else 'without plug'}" 
        for x in 
                    zip(
                        filter(lambda x: isinstance(x, str), cables),
                        filter(lambda x: isinstance(x, str), sockets),
                        list(filter(lambda x: isinstance(x, str), plugs)) + [None] * (min(len(list(filter(lambda x: isinstance(x, str), cables))), 
                                                                                     len(list(filter(lambda x: isinstance(x, str), cables)))) - 
                                                                                     len(list(filter(lambda x: isinstance(x, str), plugs))))
                        )
                    ]
    
                


# plugs = ['plugZ', None, 'plugY', 'plugX']
# sockets = [1, 'socket1', 'socket2', 'socket3', 'socket4']
# cables = ['cable2', 'cable1', False]

# for c in fix_wiring(cables, sockets, plugs):
#     print(c)

def tests() -> None:
    assert list(fix_wiring(
        plugs=['plug1', 'plug2', 'plug3'],
        sockets=['socket1', 'socket2', 'socket3', 'socket4'],
        cables=['cable1', 'cable2', 'cable3', 'cable4'],
    )) == ['plug cable1 into socket1 using plug1', 'plug cable2 into socket2 using plug2', 'plug cable3 into socket3 using plug3', 'weld cable4 to socket4 without plug'], 'test 1 failed'
    # assert list(fix_wiring(
    #     plugs=['plugZ', None, 'plugY', 'plugX'],
    #     sockets=[1, 'socket1', 'socket2', 'socket3', 'socket4'],
    #     cables=['cable2', 'cable1', False],
    # )) == [
    #     'plug cable2 into socket1 using plugZ',
    #     'plug cable1 into socket2 using plugY',
    # ]
    # assert list(fix_wiring(
    #     plugs=['plugZ', None],
    #     sockets=[1, 'socket1'],
    #     cables=['cable2', 'cable1', False],
    # )) == [
    #     'plug cable2 into socket1 using plugZ',
    # ]
    print('Tests passed!!!')


if __name__ == '__main__':
    plugs: List[str | Any] = ['plug1', 'plug2', 'plug3']
    sockets: List[str | Any] = ['socket1', 'socket2', 'socket3', 'socket4']
    cables: List[str | Any] = ['cable1', 'cable2', 'cable3', 'cable4']
    print(fix_wiring(cables, sockets, plugs))
    for c in fix_wiring(cables, sockets, plugs):
        print(c)
    print()
    plugs = ['plugZ', None, 'plugY', 'plugX']
    sockets = [1, 'socket1', 'socket2', 'socket3', 'socket4']
    cables = ['cable2', 'cable1', False]
    for c in fix_wiring(cables, sockets, plugs):
        print(c)
    tests()