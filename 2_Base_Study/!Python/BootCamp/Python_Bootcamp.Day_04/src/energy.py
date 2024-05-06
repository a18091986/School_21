from itertools import zip_longest


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
    
                


plugs = ['plugZ', None, 'plugY', 'plugX']
sockets = [1, 'socket1', 'socket2', 'socket3', 'socket4']
cables = ['cable2', 'cable1', False]

for c in fix_wiring(cables, sockets, plugs):
    print(c)