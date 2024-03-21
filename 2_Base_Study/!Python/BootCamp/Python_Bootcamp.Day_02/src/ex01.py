from dataclasses import dataclass
from collections import Counter
from itertools import combinations

@dataclass
class Player():
    start = 'cooperate'
    was_cheat = False
    other_player_last_step: str = None

@dataclass
class Cheater(Player):
    __name__ = 'Cheater'
    start = 'cheat'
    def play(self, step):
        return 'cheat'
    

@dataclass
class Cooperator(Player):
    __name__ = 'Cooperator'
    def play(self, step):
        return 'cooperate'

@dataclass
class Copycat(Player):
    __name__ = 'Copycat'
    def play(self, step):
        return self.other_player_last_step

@dataclass
class Grudjer(Player):
    __name__ = 'Grudjer'
    def play(self, step):
        if not self.was_cheat:
            return 'cooperate'
        else:
            return 'cheat'

@dataclass
class Detective(Player):
    __name__ = 'Detective'
    play_model = ['cooperate', 'cheat', 'cooperate', 'cooperate']
    def play(self, step):
        if step < 4:
            return self.play_model[step]
        else:
            if self.was_cheat:
                return self.other_player_last_step
            else:
                return 'cheat'
            
@dataclass
class My(Player):
    __name__ = 'My'
    start = 'cheat'
    def play(self, step):
        if step == 1:
            return 'cooperate'
        return 'cheat'







class Game(object):

    def __init__(self, matches=10):
        players = [Cheater(), Cooperator(), Copycat(), Detective(), Grudjer(), My()]
        self.matches = matches
        self.registry = Counter()
        self.top = Counter({p.__name__: 0 for p in players})

    def play(self, player1, player2):
        # print(f"{player1.__name__} vs {player2.__name__}")
        for i in range(self.matches):
            if i == 0:
                current_player1 = player1.start
                current_player2 = player2.start
            else:
                current_player1 = player1.play(step=i)
                current_player2 = player2.play(step=i)
            
            player2.other_player_last_step = current_player1
            player1.other_player_last_step = current_player2

            if current_player1 == 'cheat':
                player2.was_cheat = True
            if current_player2 == 'cheat':
                player1.was_cheat = True

            if current_player1 == 'cooperate' and current_player2 == 'cooperate':
                self.registry[player1.__name__] += 1
                self.registry[player2.__name__] += 1
            elif current_player1 == 'cooperate' and current_player2 == 'cheat':
                self.registry[player2.__name__] += 3
                self.registry[player1.__name__] -= 1
            elif current_player2 == 'cooperate' and current_player1 == 'cheat':
                self.registry[player1.__name__] += 3
                self.registry[player2.__name__] -= 1
        
        if self.registry[player1.__name__] > self.registry[player2.__name__]:
            self.top[player1.__name__] += 1
        elif self.registry[player2.__name__] > self.registry[player1.__name__]:
            self.top[player2.__name__] += 1

    def top3(self):
        for x in [f"{x} {n}".strip() for x, n in self.top.most_common()[:3]]:
            print(x)

    def result(self):
        for x in [f"{x} {n}".strip() for x, n in self.top.most_common()]:
            print(x)


if __name__ == '__main__':
    g = Game()
    for p1, p2 in list(combinations([Cheater(), Cooperator(), Copycat(), Detective(), Grudjer(), My()], 2)):
        g.play(p1, p2)
    g.top3()


