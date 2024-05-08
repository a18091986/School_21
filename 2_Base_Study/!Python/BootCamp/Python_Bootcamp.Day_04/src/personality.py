from random import randint
def generate_traits(idx):
    n = randint(0, 100)
    o = randint(0 , 100 - n)
    c = randint(0 , 100 - n - o)
    e = randint(0 , 100 - n - o - c)
    a = 100 - n - o - c - e
    return {
        'neuroticism': n,
        'openness': o,
        'conscientiousness': c,
        'extraversion': e,
        'agreeableness': a,
        'idx': idx,
        'shoot': lambda self: print('Shooting'),
        'search': lambda self: print('Searching'),
        'talk': lambda self: print('Talking'),


    }


def turrets_generator():
    count = 0
    while True:
        a = type('Turret', (), generate_traits(idx = count))()
        yield a
        count += 1
        

for i in turrets_generator():
    print(f"{i.idx} "
          f"turret: {i}\n"
          f"traits_sum: {i.neuroticism + i.openness + i.conscientiousness + i.agreeableness + i.extraversion}")
    i.shoot()
    i.search()
    i.talk()
    print()
    if i.idx >= 10:
        break


